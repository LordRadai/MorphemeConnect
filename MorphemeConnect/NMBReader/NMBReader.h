#pragma once
#include "MorphemeBundle/MorphemeBundle.h"
#include "MorphemeBundle/MorphemeBundle_Header.h"
#include "MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "MorphemeBundle/MorphemeBundle_Network.h"
#include "MorphemeBundle/MorphemeBundle_FileNameLookupTable.h"

class NMBReader
{
public:
	PWSTR m_filePath;
	UINT64 m_fileSize;
	bool m_init = false;

	std::vector<MorphemeBundle> m_bundles;

	std::vector<MorphemeBundle> m_skeletonMapBundle;
	std::vector<MorphemeBundle> m_messageIndices;
	std::vector<MorphemeBundle_EventTrack> m_eventTracks;
	std::vector<MorphemeBundle> m_unkParameters;
	MorphemeBundle_Network m_network;
	MorphemeBundle_Header m_header;
	MorphemeBundle_FileNameLookupTable m_fileNameLookupTable;

	NMBReader() {}
	NMBReader(PWSTR pszFilePath);
	~NMBReader();

	std::string GetAnimFileName(int idx);							//Returns the anim name from its index from the string table 
	std::string GetXmdSourceAnimFileName(int idx);					//Returns the XMD source anim name from its index from the string table 
	std::string GetAnimNameFromAnimNode(NodeDef* m_node);			//Returns the anim name inside an AnimSyncEvent node
	MorphemeBundle_EventTrack* GetEventTrackBundle(int signature);	//Returns the event track bundle with the matching m_signature parameter. Returns NULL if not found
};