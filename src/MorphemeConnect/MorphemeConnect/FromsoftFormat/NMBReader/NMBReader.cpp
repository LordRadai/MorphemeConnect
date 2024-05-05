#include <filesystem>
#include "NMBReader.h"
#include "../../StringHelper/StringHelper.h"
#include "ME/ME.h"

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
		Debug::Panic("NMBReader.cpp", "Animation at index %d exceeds the animation count %d (%s.nmb)\n", idx, this->GetAnimationCount(), this->GetFileName());

		return nullptr;
	}

	return &this->m_animations[idx];
}

//Returns a generic bundle by index
MorphemeBundle* NMBReader::GetBundle(int idx)
{
	if (idx > this->m_bundles.size())
	{
		Debug::Panic("NMBReader.cpp", "Bundle at index %d exceeds the bundle count %d (%s.nmb)\n", idx, this->GetBundleCount(), this->GetFileName());

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
	new_bundle.m_data->m_channelId = 0;

	new_bundle.m_data->m_trackName = new char[50];
	strcpy(new_bundle.m_data->m_trackName, name);

	new_bundle.m_data->m_eventId = event_id;
	new_bundle.m_data->m_index = 0;

	new_bundle.CalculateBundleSize();

	this->m_eventTracks.push_back(new_bundle);

	NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)node_source->m_nodeData[1].m_attrib;
	NodeAttribSourceEventTrack* event_tracks = (NodeAttribSourceEventTrack*)node_source->m_nodeData[2].m_attrib;

	if (!duration)
	{
		event_tracks->m_eventTracks[0].m_trackCount++;
		event_tracks->m_eventTracks[0].m_trackSignatures.push_back(new_bundle.m_signature);
	}
	else
	{
		event_tracks->m_eventTracks[2].m_trackCount++;
		event_tracks->m_eventTracks[2].m_trackSignatures.push_back(new_bundle.m_signature);
	}

	std::vector<NodeDef*> nodes = this->GetNodesByAnimReference(source_anim->m_animIdx);

	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] != node_source)
		{
			NodeAttribSourceEventTrack* event_tracks_new = (NodeAttribSourceEventTrack*)nodes[i]->m_nodeData[2].m_attrib;

			event_tracks_new->m_eventTracks[0] = event_tracks->m_eventTracks[0];
			event_tracks_new->m_eventTracks[1] = event_tracks->m_eventTracks[1];
			event_tracks_new->m_eventTracks[2] = event_tracks->m_eventTracks[2];
		}
	}

	return &this->m_eventTracks.back();
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
		this->m_header.WriteBinary(&nmb_out, 0);

		if (this->m_characterControllerDef.size() == this->m_rig.size())
		{
			for (size_t i = 0; i < this->m_characterControllerDef.size(); i++)
			{
				this->m_characterControllerDef[i].WriteBinary(&nmb_out, 0);

				//this->m_rig[i].WriteBinary(&nmb_out, 0);
				this->m_rigRaw[i].WriteBinary(&nmb_out, 16);
			}
		}
		else
		{
			Debug::Alert(Debug::LVL_ERROR, "NMBReader.cpp", "Incompatible array size (m_characterControllerDef.size() != m_rig.size()\n");
			return false;
		}

		for (int i = 0; i < this->m_eventTracks.size(); i++)
			this->m_eventTracks[i].WriteBinary(&nmb_out, 0);

		for (int i = 0; i < this->m_rigToAnimMap.size(); i++)
			this->m_rigToAnimMap[i].WriteBinary(&nmb_out, 0);

		//this->m_network.WriteBinary(&nmb_out);
		this->m_networkRaw.WriteBinary(&nmb_out, 0);
		this->m_fileNameLookupTable.WriteBinary(&nmb_out, 0);
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

	return StringHelper::ToNarrow(filename.c_str());
}

//Returns the anim name inside an AnimSyncEvent node
std::string NMBReader::GetAnimNameFromAnimNode(NodeDef* m_node)
{
	if (this->m_init == false)
		return "";

	if (m_node->m_nodeTypeID != NodeType_NodeAnimSyncEvents)
	{
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Node is not of the correct type\n");
		return "";
	}

	NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)m_node->m_nodeData[1].m_attrib;

	if (source_anim->m_animIdx > this->m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount)
		return "";

	return this->GetSourceAnimName(source_anim->m_animIdx);
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

	Debug::DebuggerMessage(Debug::LVL_WARN, "There is no EventTrack bundle with the matching signature (signature=%d)\n", signature);

	return nullptr;
}

//Returns all the EventTrackList objects with references to the specified signature
std::vector<EventTrackList*> NMBReader::GetEventTrackListBySignature(int signature)
{
	std::vector<EventTrackList*> track_lists;

	for (int i = 0; i < this->m_networkDef.m_data->m_numNodes; i++)
	{
		NodeDef* node = this->m_networkDef.m_data->m_nodes[i];

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

	for (int i = 0; i < this->m_networkDef.m_data->m_numNodes; i++)
	{
		NodeDef* node = this->m_networkDef.m_data->m_nodes[i];

		if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
		{
			NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)node->m_nodeData[1].m_attrib;

			if (source_anim->m_animIdx == anim_idx)
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
	this->m_animations.reserve(this->m_fileNameLookupTable.m_data->m_animList.m_elemCount);

	for (int i = 0; i < this->m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
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

	if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
	{
		if (node->m_nodeData[1].m_attrib != NULL)
		{
			tinyxml2::XMLDocument out;

			NodeAttribBool* is_loop = (NodeAttribBool*)node->m_nodeData[0].m_attrib;
			NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)node->m_nodeData[1].m_attrib;
			NodeAttribSourceEventTrack* event_track = (NodeAttribSourceEventTrack*)node->m_nodeData[2].m_attrib;

			ME::TakeListXML(&out, this->m_fileNameLookupTable.GetXmdSourceAnimFileName(anim_id).c_str());

			/*
			tinyxml2::XMLElement* pRoot = out.NewElement("TakeList");
			pRoot->SetAttribute("sourceAnimFile", this->m_fileNameLookupTable.GetXmdSourceAnimFileName(anim_id).c_str());
			pRoot->SetAttribute("version", 1);

			tinyxml2::XMLElement* take = out.NewElement("Take");
			take->SetAttribute("name", this->m_fileNameLookupTable.GetAnimTake(anim_id).c_str());

			tinyxml2::XMLElement* attributes = out.NewElement("Attributes");
			take->InsertEndChild(attributes);

			tinyxml2::XMLElement* duration = out.NewElement("secondDuration");
			duration->SetAttribute("type", "double");
			duration->SetText(source_anim->m_animLen);

			attributes->InsertEndChild(duration);

			tinyxml2::XMLElement* fps = out.NewElement("fps");
			fps->SetAttribute("type", "double");
			fps->SetText(30);

			attributes->InsertEndChild(fps);

			tinyxml2::XMLElement* clipStart = out.NewElement("clipStart");
			clipStart->SetAttribute("type", "double");
			clipStart->SetText(source_anim->m_clipStart);

			attributes->InsertEndChild(clipStart);

			tinyxml2::XMLElement* clipEnd = out.NewElement("clipEnd");
			clipEnd->SetAttribute("type", "double");
			clipEnd->SetText(source_anim->m_clipEnd);

			attributes->InsertEndChild(clipEnd);

			tinyxml2::XMLElement* loop = out.NewElement("loop");
			loop->SetAttribute("type", "bool");

			if (is_loop->m_bool)
				loop->SetText("true");
			else
				loop->SetText("false");

			attributes->InsertEndChild(loop);

			take->InsertEndChild(attributes);

			int track_count = 0;
			for (size_t i = 0; i < 3; i++)
				track_count += event_track->m_eventTracks[i].m_trackCount;

			if (track_count > 0)
			{
				for (int i = 0; i < event_track->m_eventTracks[0].m_trackCount; i++)
				{
					MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->m_eventTracks[0].m_trackSignatures[i]);

					if (event_tracks)
					{
						tinyxml2::XMLElement* DiscreteEventTrack = out.NewElement("DiscreteEventTrack");

						DiscreteEventTrack->SetAttribute("name", event_tracks->m_data->m_trackName);
						DiscreteEventTrack->SetAttribute("guid", event_tracks->GetGUID().c_str());
						DiscreteEventTrack->SetAttribute("channelID", event_tracks->m_data->m_channelId);

						tinyxml2::XMLElement* attributeET = out.NewElement("Attributes");

						DiscreteEventTrack->InsertEndChild(attributeET);

						tinyxml2::XMLElement* userDataET = out.NewElement("userData");
						userDataET->SetAttribute("type", "uint");
						userDataET->SetText(event_tracks->m_data->m_eventId);

						attributeET->InsertEndChild(userDataET);

						for (size_t eventIdx = 0; eventIdx < event_tracks->m_data->m_numEvents; eventIdx++)
						{
							tinyxml2::XMLElement* discreteEvent = out.NewElement("DiscreteEvent");
							discreteEvent->SetAttribute("index", eventIdx);

							DiscreteEventTrack->InsertEndChild(discreteEvent);

							tinyxml2::XMLElement* attributesEvent = out.NewElement("Attributes");

							tinyxml2::XMLElement* userData = out.NewElement("userData");
							userData->SetAttribute("type", "uint");
							userData->SetText(event_tracks->m_data->m_events[eventIdx].m_value);

							attributesEvent->InsertEndChild(userData);

							tinyxml2::XMLElement* startTime = out.NewElement("startTime");
							startTime->SetAttribute("type", "double");
							startTime->SetText(event_tracks->m_data->m_events[eventIdx].m_start);

							attributesEvent->InsertEndChild(startTime);

							discreteEvent->InsertEndChild(attributesEvent);
						}

						take->InsertEndChild(DiscreteEventTrack);
					}
				}

				for (int i = 0; i < event_track->m_eventTracks[1].m_trackCount; i++)
				{
					MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->m_eventTracks[1].m_trackSignatures[i]);

					if (event_tracks)
					{
						tinyxml2::XMLElement* CurveEventTrack = out.NewElement("CurveEventTrack");

						CurveEventTrack->SetAttribute("name", event_tracks->m_data->m_trackName);
						CurveEventTrack->SetAttribute("guid", event_tracks->GetGUID().c_str());
						CurveEventTrack->SetAttribute("channelID", event_tracks->m_data->m_channelId);

						tinyxml2::XMLElement* attributeET = out.NewElement("Attributes");

						CurveEventTrack->InsertEndChild(attributeET);

						tinyxml2::XMLElement* userDataET = out.NewElement("userData");
						userDataET->SetAttribute("type", "uint");
						userDataET->SetText(event_tracks->m_data->m_eventId);

						attributeET->InsertEndChild(userDataET);

						for (size_t eventIdx = 0; eventIdx < event_tracks->m_data->m_numEvents; eventIdx++)
						{
							tinyxml2::XMLElement* curveEvent = out.NewElement("CurveEvent");
							curveEvent->SetAttribute("index", eventIdx);

							CurveEventTrack->InsertEndChild(curveEvent);

							tinyxml2::XMLElement* attributesEvent = out.NewElement("Attributes");

							tinyxml2::XMLElement* userData = out.NewElement("userData");
							userData->SetAttribute("type", "uint");
							userData->SetText(event_tracks->m_data->m_events[eventIdx].m_value);

							attributesEvent->InsertEndChild(userData);

							tinyxml2::XMLElement* startTime = out.NewElement("startTime");
							startTime->SetAttribute("type", "double");
							startTime->SetText(event_tracks->m_data->m_events[eventIdx].m_start);

							attributesEvent->InsertEndChild(startTime);

							tinyxml2::XMLElement* duration = out.NewElement("duration");
							duration->SetAttribute("type", "double");
							duration->SetText(event_tracks->m_data->m_events[eventIdx].m_duration);

							attributesEvent->InsertEndChild(duration);

							curveEvent->InsertEndChild(attributesEvent);
						}

						take->InsertEndChild(CurveEventTrack);
					}
				}

				for (int i = 0; i < event_track->m_eventTracks[2].m_trackCount; i++)
				{
					MorphemeBundle_EventTrack* event_tracks = GetEventTrackBundle(event_track->m_eventTracks[2].m_trackSignatures[i]);

					if (event_tracks)
					{
						tinyxml2::XMLElement* DurationEventTrack = out.NewElement("DurationEventTrack");

						DurationEventTrack->SetAttribute("name", event_tracks->m_data->m_trackName);
						DurationEventTrack->SetAttribute("guid", event_tracks->GetGUID().c_str());
						DurationEventTrack->SetAttribute("channelID", event_tracks->m_data->m_channelId);

						tinyxml2::XMLElement* attributeET = out.NewElement("Attributes");

						DurationEventTrack->InsertEndChild(attributeET);

						tinyxml2::XMLElement* userDataET = out.NewElement("userData");
						userDataET->SetAttribute("type", "uint");
						userDataET->SetText(event_tracks->m_data->m_eventId);

						attributeET->InsertEndChild(userDataET);

						for (size_t eventIdx = 0; eventIdx < event_tracks->m_data->m_numEvents; eventIdx++)
						{
							tinyxml2::XMLElement* durationEvent = out.NewElement("DurationEvent");
							durationEvent->SetAttribute("index", eventIdx);

							DurationEventTrack->InsertEndChild(durationEvent);

							tinyxml2::XMLElement* attributesEvent = out.NewElement("Attributes");

							tinyxml2::XMLElement* userData = out.NewElement("userData");
							userData->SetAttribute("type", "uint");
							userData->SetText(event_tracks->m_data->m_events[eventIdx].m_value);

							attributesEvent->InsertEndChild(userData);

							tinyxml2::XMLElement* startTime = out.NewElement("startTime");
							startTime->SetAttribute("type", "double");
							startTime->SetText(event_tracks->m_data->m_events[eventIdx].m_start);

							attributesEvent->InsertEndChild(startTime);

							tinyxml2::XMLElement* duration = out.NewElement("duration");
							duration->SetAttribute("type", "double");
							duration->SetText(event_tracks->m_data->m_events[eventIdx].m_duration);

							attributesEvent->InsertEndChild(duration);

							durationEvent->InsertEndChild(attributesEvent);
						}

						take->InsertEndChild(DurationEventTrack);
					}
				}
			}
			else
			{
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "Animation %d has no event tracks associated to it\n", source_anim->m_animIdx);
			}

			pRoot->InsertEndChild(take);
			out.InsertEndChild(pRoot);
			*/

			std::wstring filename = std::wstring(pszOutFilePath) + L"\\morphemeMarkup\\";

			std::filesystem::create_directories(filename);

			filename += StringHelper::ToWide(this->GetSourceAnimName(anim_id)) + L".xml";

			out.SaveFile(StringHelper::ToNarrow(filename.c_str()).c_str(), false);

			return true;
		}
	}

	return false;
}

bool NMBReader::NetworkExportXML(PWSTR pszOutFilePath)
{

}