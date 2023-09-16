#include <filesystem>
#include "NMBReader.h"

NMBReader::NMBReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	std::filesystem::path path(pszFilePath);

	this->m_fileName = path.filename().c_str();

	ifstream nmb;

	nmb.open(this->m_filePath, ios::binary | ios::ate);
	this->m_fileSize = nmb.tellg();
	nmb.close();

	nmb.open(this->m_filePath, ios::binary);

	int iBundleType = 0;
	try
	{
		while ((nmb.eof() == false) && (iBundleType < Bundle_FileNameLookupTable))
		{
			this->m_bundles.push_back(MorphemeBundle(&nmb));
			iBundleType = this->m_bundles.back().m_bundleType;
		}
	}
	catch (const char* error)
	{
		ShowCursor(true);
		MessageBoxA(NULL, error, "NMBReader.cpp", MB_ICONERROR);

		this->m_init = false;
		return;
	}

	for (int i = 0; i < this->m_bundles.size(); i++)
	{
		switch (this->m_bundles[i].m_bundleType)
		{
		default:
			break;
		case Bundle_SkeletonMap:
			this->m_skeletonMap.push_back(this->m_bundles[i]);
			break;
		case Bundle_MessageIndices:
			this->m_messageIndices.push_back(this->m_bundles[i]);
			break;
		case Bundle_DiscreteEventTrack:
		case Bundle_DurationEventTrack:
			this->m_eventTracks.push_back(&this->m_bundles[i]);
			break;
		case Bundle_CharacterControllerDef:
			this->m_characterControllerDef.push_back(this->m_bundles[i]);
			break;
		case Bundle_Network:
			this->m_network = MorphemeBundle_Network(&this->m_bundles[i]);
			this->m_networkRaw = MorphemeBundle(this->m_bundles[i]);
			break;
		case Bundle_FileHeader:
			this->m_header = MorphemeBundle_Header(&this->m_bundles[i]);
			break;
		case Bundle_FileNameLookupTable:
			this->m_fileNameLookupTable = MorphemeBundle_FileNameLookupTable(&this->m_bundles[i]);
			break;
		}
	}

	this->m_init = true;

	this->SortAnimList();

	nmb.close();
}

NMBReader::~NMBReader()
{
}

bool NMBReader::SaveToFile(PWSTR pszOutFilePath)
{
	if (this->m_init == false)
		return false;

	std::filesystem::path path = pszOutFilePath;

	if (std::filesystem::exists(path))
	{
		std::filesystem::path bak_path = path;
		bak_path.replace_extension(L".nmb.bak");

		std::filesystem::copy_file(path, bak_path, std::filesystem::copy_options::overwrite_existing);
	}

	bool state = true;
	this->m_outFilePath = pszOutFilePath;

	ofstream nmb_out;

	nmb_out.open(this->m_outFilePath, ios::binary);

	try
	{
		this->m_header.WriteBinary(&nmb_out);

		if (this->m_characterControllerDef.size() == this->m_skeletonMap.size())
		{
			for (size_t i = 0; i < this->m_characterControllerDef.size(); i++)
			{
				this->m_characterControllerDef[i].WriteBinary(&nmb_out);

				this->m_skeletonMap[i].WriteBinary(&nmb_out);

				BYTE pad_array[4] = { 0xCD, 0xCD, 0xCD, 0xCD };
				MemReader::WriteByteArray(&nmb_out, pad_array, 4);
			}
		}

		for (int i = 0; i < this->m_eventTracks.size(); i++)
			this->m_eventTracks[i].WriteBinary(&nmb_out);

		for (int i = 0; i < this->m_messageIndices.size(); i++)
			this->m_messageIndices[i].WriteBinary(&nmb_out);

		//this->m_network.WriteBinary(&nmb_out);
		this->m_networkRaw.WriteBinary(&nmb_out);
		this->m_fileNameLookupTable.WriteBinary(&nmb_out);
	}
	catch (const std::exception&)
	{
		state = false;
	}

	this->m_outFileSize = nmb_out.tellp();

	nmb_out.close();

	return state;
}

std::string NMBReader::GetAnimFileName(int idx)
{
	if (this->m_init == false)
		return "";

	if (idx > this->m_fileNameLookupTable.m_data->m_animList.m_elemCount)
		return "";

	return std::string(&this->m_fileNameLookupTable.m_data->m_animList.m_strings[this->m_fileNameLookupTable.m_data->m_animList.m_localOffsets[idx]]);
}

std::string NMBReader::GetXmdSourceAnimFileName(int idx)
{
	if (this->m_init == false)
		return "";

	if (idx > this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount)
		return "";

	return std::string(&this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_strings[this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_localOffsets[idx]]);
}

std::string NMBReader::GetAnimNameFromAnimNode(NodeDef* m_node)
{
	if (this->m_init == false)
		return "";

	if (m_node->m_nodeTypeID != NodeType_NodeAnimSyncEvents)
	{
		MessageBoxA(NULL, "Node is not of the correct type", "NMBReader.cpp", MB_ICONERROR);
		return "";
	}

	NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)m_node->m_nodeData[1].m_attrib;

	if (source_anim->m_animIdx > this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount)
		return "";

	return this->GetAnimFileName(source_anim->m_animIdx);
}

MorphemeBundle_EventTrack* NMBReader::GetEventTrackBundle(int signature)
{
	if (this->m_init == false)
		return NULL;

	for (int i = 0; i < this->m_eventTracks.size(); i++)
	{
		if (this->m_eventTracks[i].m_signature == signature)
			return &this->m_eventTracks[i];
	}

	return NULL;
}

std::vector<EventTrackList*> NMBReader::GetEventTrackListBySignature(int signature)
{
	std::vector<EventTrackList*> track_lists;

	for (int i = 0; i < this->m_network.m_data->m_numNodes; i++)
	{
		NodeDef* node = this->m_network.m_data->m_nodes[i];

		if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
		{
			NodeAttribSourceEventTrack* source_event_track = (NodeAttribSourceEventTrack*)node->m_nodeData[2].m_attrib;

			for (int j = 0; j < source_event_track->m_eventTracks[0].m_trackCount; j++)
			{
				if (source_event_track->m_eventTracks[0].m_trackSignatures[j] == signature)
					track_lists.push_back(&source_event_track->m_eventTracks[0]);
			}

			for (int j = 0; j < source_event_track->m_eventTracks[1].m_trackCount; j++)
			{
				if (source_event_track->m_eventTracks[1].m_trackSignatures[j] == signature)
					track_lists.push_back(&source_event_track->m_eventTracks[1]);
			}

			for (int j = 0; j < source_event_track->m_eventTracks[2].m_trackCount; j++)
			{
				if (source_event_track->m_eventTracks[2].m_trackSignatures[j] == signature)
					track_lists.push_back(&source_event_track->m_eventTracks[2]);
			}
		}
	}

	return track_lists;
}

std::vector<NodeDef*> NMBReader::GetNodesByAnimReference(int anim_idx)
{
	std::vector<NodeDef*> nodes;

	for (int i = 0; i < this->m_network.m_data->m_numNodes; i++)
	{
		NodeDef* node = this->m_network.m_data->m_nodes[i];

		if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
		{
			NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)node->m_nodeData[1].m_attrib;

			if (source_anim->m_animIdx == anim_idx)
				nodes.push_back(node);
		}
	}

	return nodes;
}

bool compareAnimFileInterface(AnimFileInterface a, AnimFileInterface b)
{
	return a.m_name < b.m_name;
}

void NMBReader::SortAnimList()
{
	this->m_compressedNsa.reserve(this->m_fileNameLookupTable.m_data->m_animList.m_elemCount);
	this->m_sourceXmd.reserve(this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount);

	for (int i = 0; i < this->m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
		this->m_compressedNsa.push_back(AnimFileInterface{ this->GetAnimFileName(i), i });

	for (int i = 0; i < this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount; i++)
		this->m_sourceXmd.push_back(AnimFileInterface{ this->GetXmdSourceAnimFileName(i), i });

	std::sort(this->m_compressedNsa.begin(), this->m_compressedNsa.end(), compareAnimFileInterface);
	std::sort(this->m_sourceXmd.begin(), this->m_sourceXmd.end(), compareAnimFileInterface);
}