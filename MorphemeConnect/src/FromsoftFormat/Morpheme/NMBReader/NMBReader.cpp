#include "../../../framework.h"
#include "../../../extern.h"
#include "NMBReader.h"
#include "../ME/ME.h"

NMBReader::NMBReader(PWSTR pszFilePath)
{
	this->m_init = false;

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
		while ((nmb.eof() == false) && (iBundleType < kAsset_SimpleAnimruntimeIDtoFilenameLookup))
		{
			this->m_bundles.push_back(MorphemeBundle(&nmb));
			iBundleType = this->m_bundles.back().m_assetType;
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
		switch (this->m_bundles[i].m_assetType)
		{
		default:
			break;
		case kAsset_Rig:
			this->m_rig.push_back(&this->m_bundles[i]);
			this->m_rigRaw.push_back(this->m_bundles[i]);
			break;
		case kAsset_RigToAnimMap:
			this->m_rigToAnimMap.push_back(this->m_bundles[i]);
			break;
		case kAsset_EventTrackDiscrete:
		case kAsset_EventTrackDuration:
			this->m_eventTracks.push_back(&this->m_bundles[i]);
			break;
		case kAsset_CharacterControllerDef:
			this->m_characterControllerDef.push_back(this->m_bundles[i]);
			break;
		case kAsset_NetworkDef:
			this->m_networkDef = MorphemeBundle_NetworkDef(&this->m_bundles[i]);
			this->m_networkRaw = MorphemeBundle(this->m_bundles[i]);
			break;
		case kAsset_Header:
			this->m_header = MorphemeBundle_Header(&this->m_bundles[i]);
			break;
		case kAsset_SimpleAnimruntimeIDtoFilenameLookup:
			this->m_fileNameLookupTable = MorphemeBundle_FileNameLookupTable(&this->m_bundles[i]);
			break;
		}
	}

	this->m_init = true;

	nmb.close();

	this->SortAnimList();
}

NMBReader::~NMBReader()
{
}

bool NMBReader::IsInitialised()
{
	return this->m_init;
}

std::wstring NMBReader::GetFileName()
{
	return this->m_fileName;
}

int NMBReader::GetFileSize()
{
	return this->m_fileSize;
}

PWSTR NMBReader::GetFilePath()
{
	return this->m_filePath;
}

int NMBReader::GetBundleCount()
{
	return this->m_bundles.size();
}

int NMBReader::GetRigCount()
{
	return this->m_rig.size();
}

int NMBReader::GetAnimationCount()
{
	return this->m_animations.size();
}

//Returns the animation interface object at index idx
AnimInterface* NMBReader::GetAnimationInterface(int idx)
{
	if (idx > this->m_animations.size())
	{
		RDebug::SystemPanic("NMBReader.cpp", "Animation at index %d exceeds the animation count %d (%s.nmb)\n", idx, this->GetAnimationCount(), this->GetFileName());

		return nullptr;
	}

	return &this->m_animations[idx];
}

//Returns a generic bundle by index
MorphemeBundle* NMBReader::GetBundle(int idx)
{
	if (idx > this->m_bundles.size())
	{
		RDebug::SystemPanic("NMBReader.cpp", "Bundle at index %d exceeds the bundle count %d (%s.nmb)\n", idx, this->GetBundleCount(), this->GetFileName());

		return nullptr;
	}

	return &this->m_bundles[idx];
}

PWSTR NMBReader::GetOutFilePath()
{
	return this->m_outFilePath;
}

int NMBReader::GetOutFileSize()
{
	return this->m_outFileSize;
}

//Returns the NetworkDef bundle
MorphemeBundle_NetworkDef* NMBReader::GetNetworkDef()
{
	return &this->m_networkDef;
}

//Returns the FilenameLookupTable bundle
MorphemeBundle_FileNameLookupTable* NMBReader::GetFilenameLookupTable()
{
	return &this->m_fileNameLookupTable;
}

//Returns the rig bundle at the given index
MorphemeBundle_Rig* NMBReader::GetRig(int idx)
{
	if (idx > this->m_rig.size() - 1)
		return nullptr;

	return &this->m_rig[idx];
}

MorphemeBundle_EventTrack* NMBReader::AddEventTrack(NodeDef* node_source, int event_id, char* name, bool duration)
{
	/*
	int signature = rand();
	bool valid = true;

	do
	{
		signature = rand();

		for (int i = 0; i < this->m_bundles.size(); i++)
		{
			if (this->m_bundles[i].m_signature == signature)
			{
				valid = false;
			}
		}

	} while (valid == false);

	MorphemeBundle_EventTrack new_bundle;

	new_bundle.m_magic[0] = 24;
	new_bundle.m_magic[1] = 10;

	if (!duration)
		new_bundle.m_assetType = kAsset_EventTrackDiscrete;
	else
		new_bundle.m_assetType = kAsset_EventTrackDuration;

	new_bundle.m_signature = signature;

	for (size_t i = 0; i < 16; i++)
		new_bundle.m_guid[i] = 0;

	new_bundle.m_dataSize = 0;
	new_bundle.m_dataAlignment = 16;
	new_bundle.m_iVar2C = 0;

	new_bundle.m_data = new MorphemeBundle_EventTrack::BundleData_EventTrack;

	new_bundle.m_data->m_numEvents = 0;
	new_bundle.m_data->GetChannelID() = 0;

	new_bundle.m_data->m_trackName = new char[50];
	strcpy(new_bundle.m_data->m_trackName, name);

	new_bundle.m_data->GetUserData() = event_id;
	new_bundle.m_data->m_index = 0;

	new_bundle.CalculateBundleSize();

	this->m_eventTracks.push_back(new_bundle);

	NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)node_source->m_nodeData[1].m_attrib;
	MR::AttribDataSourceEventTrack* event_tracks = (MR::AttribDataSourceEventTrack*)node_source->m_nodeData[2].m_attrib;

	if (!duration)
	{
		event_tracks->GetDiscreteEventTrackSet().m_trackCount++;
		event_tracks->GetDiscreteEventTrackSet().m_trackSignatures.push_back(new_bundle.m_signature);
	}
	else
	{
		event_tracks->GetDurationEventTrackSet().m_trackCount++;
		event_tracks->GetDurationEventTrackSet().m_trackSignatures.push_back(new_bundle.m_signature);
	}

	std::vector<NodeDef*> nodes = this->GetNodesByAnimReference(source_anim->m_animIdx);

	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] != node_source)
		{
			MR::AttribDataSourceEventTrack* event_tracks_new = (MR::AttribDataSourceEventTrack*)nodes[i]->m_nodeData[2].m_attrib;

			event_tracks_new->GetDiscreteEventTrackSet() = event_tracks->GetDiscreteEventTrackSet();
			event_tracks_new->GetCurveEventTrackSet() = event_tracks->GetCurveEventTrackSet();
			event_tracks_new->GetDurationEventTrackSet() = event_tracks->GetDurationEventTrackSet();
		}
	}

	return &this->m_eventTracks.back();
	*/

	return nullptr;
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
		this->m_header.WriteBinary(&nmb_out, this->m_header.m_dataAlignment);

		if (this->m_characterControllerDef.size() == this->m_rig.size())
		{
			for (size_t i = 0; i < this->m_characterControllerDef.size(); i++)
			{
				this->m_characterControllerDef[i].WriteBinary(&nmb_out, this->m_characterControllerDef[i].m_dataAlignment);

				//this->m_rig[i].WriteBinary(&nmb_out, 0);
				this->m_rigRaw[i].WriteBinary(&nmb_out, 16);
			}
		}
		else
		{
			RDebug::SystemAlert(g_logLevel, MsgLevel_Warn, "NMBReader.cpp", "Incompatible array size (m_characterControllerDef.size() != m_rig.size()\n");
			return false;
		}

		for (int i = 0; i < this->m_eventTracks.size(); i++)
			this->m_eventTracks[i].WriteBinary(&nmb_out, this->m_eventTracks[i].m_dataAlignment);

		for (int i = 0; i < this->m_rigToAnimMap.size(); i++)
			this->m_rigToAnimMap[i].WriteBinary(&nmb_out, this->m_rigToAnimMap[i].m_dataAlignment);

		//this->m_network.WriteBinary(&nmb_out);
		this->m_networkRaw.WriteBinary(&nmb_out, this->m_networkRaw.m_dataAlignment);
		this->m_fileNameLookupTable.WriteBinary(&nmb_out, this->m_fileNameLookupTable.m_dataAlignment);
	}
	catch (const std::exception&)
	{
		state = false;
	}

	this->m_outFileSize = nmb_out.tellp();

	nmb_out.close();

	return state;
}

//Returns the XMD source anim name without the relative path
std::string NMBReader::GetSourceAnimName(int idx)
{
	std::filesystem::path filepath = this->m_fileNameLookupTable.GetXmdSourceAnimFileName(idx);
	std::filesystem::path filename = filepath.filename();

	return RString::ToNarrow(filename.c_str());
}

//Returns the anim name inside an AnimSyncEvent node
std::string NMBReader::GetAnimNameFromAnimNode(NodeDef* m_node)
{
	if (this->m_init == false)
		return "";

	if (m_node->m_typeID != NodeType_NodeAnimSyncEvents)
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Node is not of the correct type\n");
		return "";
	}

	MR::AttribDataSourceAnim* source_anim = (MR::AttribDataSourceAnim*)m_node->m_attributes[1]->GetAttribData();

	if (source_anim->GetAnimID() > this->m_fileNameLookupTable.m_data->m_sourceXmdTable->GetNumEntries())
		return "";

	return this->GetSourceAnimName(source_anim->GetAnimID());

	return "";
}

//Returns the event track bundle with the matching m_signature parameter
MorphemeBundle_EventTrack* NMBReader::GetEventTrackBundle(int signature)
{
	if (this->m_init == false)
		return nullptr;

	for (int i = 0; i < this->m_eventTracks.size(); i++)
	{
		if (this->m_eventTracks[i].m_signature == signature)
			return &this->m_eventTracks[i];
	}

	RDebug::DebuggerOut(g_logLevel, MsgLevel_Warn, "There is no EventTrack bundle with the matching signature (signature=%d)\n", signature);

	return nullptr;
}

std::vector<NodeDef*> NMBReader::GetNodesByAnimReference(int anim_idx)
{
	std::vector<NodeDef*> nodes;

	for (int i = 0; i < this->m_networkDef.m_data->m_numNodes; i++)
	{
		NodeDef* node = this->m_networkDef.m_data->m_nodes[i];

		if (node->m_typeID == NodeType_NodeAnimSyncEvents)
		{
			MR::AttribDataSourceAnim* source_anim = (MR::AttribDataSourceAnim*)node->m_attributes[1]->GetAttribData();

			if (source_anim->GetAnimID() == anim_idx)
				nodes.push_back(node);
		}
	}

	return nodes;
}

bool compareAnimInterface(AnimInterface a, AnimInterface b)
{
	return a.m_name < b.m_name;
}

//Sorts the animation list from the filename lookup table and stores them into a vector of AnimationInterface objects
void NMBReader::SortAnimList()
{
	this->m_animations.reserve(this->m_fileNameLookupTable.m_data->m_animTable->GetNumEntries());

	for (int i = 0; i < this->m_fileNameLookupTable.m_data->m_animTable->GetNumEntries(); i++)
		this->m_animations.push_back(AnimInterface{ this->GetFilenameLookupTable()->GetAnimName(i), this->GetSourceAnimName(i), i });

	std::sort(this->m_animations.begin(), this->m_animations.end(), compareAnimInterface);
}

//Exports EventTrack to XML morphemeMarkup format for morphemeConnect 3.6.2
bool NMBReader::ExportEventTrackToXML(PWSTR pszOutFilePath, int anim_id)
{
	std::vector<NodeDef*> nodes = this->GetNodesByAnimReference(anim_id);

	if (nodes.size() < 1)
		return false;

	NodeDef* node = nodes[0];

	if (node->m_typeID == NodeType_NodeAnimSyncEvents)
	{
		if (node->m_attributes[1] != nullptr)
		{
			tinyxml2::XMLDocument out;

			MR::AttribDataBool* is_loop = (MR::AttribDataBool*)node->m_attributes[0]->GetAttribData();
			MR::AttribDataSourceAnim* source_anim = (MR::AttribDataSourceAnim*)node->m_attributes[1]->GetAttribData();
			MR::AttribDataSourceEventTrack* event_track = (MR::AttribDataSourceEventTrack*)node->m_attributes[2]->GetAttribData();

			XMLElement* pTakeList = ME::TakeListXML((XMLElement*)&out, this->m_fileNameLookupTable.GetXmdSourceAnimFileName(anim_id).c_str(), 1);
			XMLElement* pTake = ME::TakeExportXML(pTakeList, this->m_fileNameLookupTable.GetAnimTake(anim_id).c_str(), is_loop->Get(), source_anim->GetAnimLen(), 30.f, source_anim->GetClipStart(), source_anim->GetClipEnd());

			for (int i = 0; i < event_track->GetDiscreteEventTrackSet().m_trackCount; i++)
			{
				MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->GetDiscreteEventTrackSet().m_trackSignatures[i]);

				XMLElement* pEventTrack = ME::DiscreteEventTrackExportXML(pTake, event_tracks->m_data->GetTrackName(), event_tracks->GetGUID(), event_tracks->m_data->GetChannelID(), event_tracks->m_data->GetUserData());

				for (size_t i = 0; i < event_tracks->m_data->GetNumEvents(); i++)
					ME::DiscreteEventExportXML(pEventTrack, i, event_tracks->m_data->GetEvent(i)->m_userData, event_tracks->m_data->GetEvent(i)->m_start);
			}

			for (int i = 0; i < event_track->GetCurveEventTrackSet().m_trackCount; i++)
			{
				MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->GetCurveEventTrackSet().m_trackSignatures[i]);

				XMLElement* pEventTrack = ME::CurveEventTrackExportXML(pTake, event_tracks->m_data->GetTrackName(), event_tracks->GetGUID(), event_tracks->m_data->GetChannelID(), event_tracks->m_data->GetUserData());

				for (size_t i = 0; i < event_tracks->m_data->GetNumEvents(); i++)
					ME::CurveEventExportXML(pEventTrack, i, event_tracks->m_data->GetEvent(i)->m_userData, event_tracks->m_data->GetEvent(i)->m_start, event_tracks->m_data->GetEvent(i)->m_duration);
			}

			for (int i = 0; i < event_track->GetDurationEventTrackSet().m_trackCount; i++)
			{
				MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->GetDurationEventTrackSet().m_trackSignatures[i]);

				XMLElement* pEventTrack = ME::DurationEventTrackExportXML(pTake, event_tracks->m_data->GetTrackName(), event_tracks->GetGUID(), event_tracks->m_data->GetChannelID(), event_tracks->m_data->GetUserData());

				for (size_t i = 0; i < event_tracks->m_data->GetNumEvents(); i++)
					ME::DurationEventExportXML(pEventTrack, i, event_tracks->m_data->GetEvent(i)->m_userData, event_tracks->m_data->GetEvent(i)->m_start, event_tracks->m_data->GetEvent(i)->m_duration);
			}

			ME::SaveFile(&out, RString::ToNarrow((std::wstring(pszOutFilePath) + L"\\morphemeMarkup\\").c_str()), this->GetSourceAnimName(anim_id), false);

			return true;
		}
	}

	return false;
}

bool NMBReader::ExportNetworkDefToXML(PWSTR pszOutFilePath)
{
	return false;
}