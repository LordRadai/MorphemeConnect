#include "NMBReader.h"

NMBReader::NMBReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	ifstream nmb;

	nmb.open(this->m_filePath, ios::binary | ios::ate);
	this->m_fileSize = nmb.tellg();
	nmb.close();

	nmb.open(this->m_filePath, ios::binary);

	int iBundleType = 0;
	while ((nmb.eof() == false) && (iBundleType < Bundle_FileNameLookupTable))
	{
		this->m_bundles.push_back(MorphemeBundle(&nmb));
		iBundleType = this->m_bundles.back().m_bundleType;
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
		case Bundle_UnkParameters:
			this->m_unkParameters.push_back(this->m_bundles[i]);
			break;
		case Bundle_Network:
			this->m_network = MorphemeBundle_Network(&this->m_bundles[i]);
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

	nmb.close();
}

NMBReader::~NMBReader()
{
}

bool NMBReader::SaveToFile(PWSTR pszOutFilePath)
{
	bool state = true;
	this->m_outFilePath = pszOutFilePath;

	ofstream nmb_out;

	nmb_out.open(this->m_outFilePath, ios::binary);

	try
	{
		this->m_header.GenerateBundle(&nmb_out);

		for (int i = 0; i < this->m_skeletonMap.size(); i++)
		{
			this->m_skeletonMap[i].GenerateBundle(&nmb_out);

			byte pad_array[4] = { 0xCD, 0xCD, 0xCD, 0xCD };
			MemHelper::WriteByteArray(&nmb_out, (LPVOID*)pad_array, 4);
		}

		for (int i = 0; i < this->m_unkParameters.size(); i++)
			this->m_unkParameters[i].GenerateBundle(&nmb_out);

		for (int i = 0; i < this->m_eventTracks.size(); i++)
			this->m_eventTracks[i].GenerateBundle(&nmb_out);

		for (int i = 0; i < this->m_messageIndices.size(); i++)
			this->m_messageIndices[i].GenerateBundle(&nmb_out);

		this->m_fileNameLookupTable.GenerateBundle(&nmb_out);
	}
	catch (const std::exception&)
	{
		state = false;
	}
	
	nmb_out.close();

	ifstream nmb_size;
	nmb_size.open(this->m_outFilePath, ios::binary | ios::ate);

	this->m_outFileSize = nmb_size.tellg();

	nmb_size.close();

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

	NodeData104* node_data = (NodeData104*)m_node->node_data;

	if (node_data->m_attribSourceAnim->m_animIdx > this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount)
		return "";

	return this->GetAnimFileName(node_data->m_attribSourceAnim->m_animIdx);
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
			NodeData104* data = (NodeData104*)node->node_data;

			for (int j = 0; j < data->m_attribEventTrack->m_eventTracks[0].m_trackCount; j++)
			{
				if (data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures[j] == signature)
					track_lists.push_back(&data->m_attribEventTrack->m_eventTracks[0]);
			}

			for (int j = 0; j < data->m_attribEventTrack->m_eventTracks[1].m_trackCount; j++)
			{
				if (data->m_attribEventTrack->m_eventTracks[1].m_trackSignatures[j] == signature)
					track_lists.push_back(&data->m_attribEventTrack->m_eventTracks[1]);
			}

			for (int j = 0; j < data->m_attribEventTrack->m_eventTracks[2].m_trackCount; j++)
			{
				if (data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures[j] == signature)
					track_lists.push_back(&data->m_attribEventTrack->m_eventTracks[2]);
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
			NodeData104* data = (NodeData104*)node->node_data;

			if (data->m_attribSourceAnim->m_animIdx == anim_idx)
				nodes.push_back(node);
		}
	}

	return nodes;
}