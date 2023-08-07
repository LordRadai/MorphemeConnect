#pragma once
#include "MorphemeBundle/MorphemeBundle.h"
#include "MorphemeBundle/MorphemeBundle_Header.h"
#include "MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "MorphemeBundle/MorphemeBundle_Network.h"

class NMBReader
{
public:
	PWSTR m_filePath;
	UINT64 m_fileSize;

	std::vector<MorphemeBundle> m_bundles;

	std::vector<MorphemeBundle> m_skeletonMapBundle;
	std::vector<MorphemeBundle> m_messageIndices;
	std::vector<MorphemeBundle_EventTrack> m_eventTracks;
	std::vector<MorphemeBundle> m_unkParameters;
	MorphemeBundle_Network m_network;
	MorphemeBundle_Header m_header;
	MorphemeBundle m_fileNameLookupTable;

	NMBReader(PWSTR pszFilePath);
	~NMBReader();
};