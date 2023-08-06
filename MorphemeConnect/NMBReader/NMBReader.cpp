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
			this->m_network = this->m_bundles[i];
			break;
		case Bundle_FileHeader:
			this->m_header = MorphemeBundle_Header(this->m_bundles[i]);
			break;
		case Bundle_FileNameLookupTable:
			this->m_fileNameLookupTable = this->m_bundles[i];
			break;
		}
	}
}

NMBReader::~NMBReader()
{
}