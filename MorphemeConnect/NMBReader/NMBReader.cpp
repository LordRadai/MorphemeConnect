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
			this->m_skeletonMapBundle.push_back(this->m_bundles[i]);
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
}

NMBReader::~NMBReader()
{
}

std::string NMBReader::GetAnimFileName(int idx)
{
	if (this->m_init == false)
		return "";

	return std::string(&this->m_fileNameLookupTable.m_data->m_animList.m_strings[this->m_fileNameLookupTable.m_data->m_animList.m_localOffsets[idx]]);
}

std::string NMBReader::GetXmdSourceAnimFileName(int idx)
{
	if (this->m_init == false)
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