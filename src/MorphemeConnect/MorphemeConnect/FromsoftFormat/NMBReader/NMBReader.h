#pragma once
#include "MorphemeBundle/MorphemeBundle.h"
#include "MorphemeBundle/MorphemeBundle_Header.h"
#include "MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "MorphemeBundle/MorphemeBundle_Network.h"
#include "MorphemeBundle/MorphemeBundle_FileNameLookupTable.h"

class NMBReader
{
public:
	std::wstring m_fileName;

	PWSTR m_filePath;
	UINT64 m_fileSize;
	PWSTR m_outFilePath;
	UINT64 m_outFileSize;
	bool m_init = false;

	std::vector<MorphemeBundle> m_bundles;

	std::vector<MorphemeBundle> m_skeletonMap;
	std::vector<MorphemeBundle> m_messageIndices;
	std::vector<MorphemeBundle_EventTrack> m_eventTracks;
	std::vector<MorphemeBundle> m_characterControllerDef;
	MorphemeBundle_Network m_network;
	MorphemeBundle_Header m_header;
	MorphemeBundle_FileNameLookupTable m_fileNameLookupTable;

	MorphemeBundle m_networkRaw;

	NMBReader() {}
	NMBReader(PWSTR pszFilePath);
	~NMBReader();

	bool SaveToFile(PWSTR pszOutFilePath);
	std::string GetAnimFileName(int idx);										//Returns the anim name from its index from the string table 
	std::string GetXmdSourceAnimFileName(int idx);								//Returns the XMD source anim name from its index from the string table 
	std::string GetAnimNameFromAnimNode(NodeDef* m_node);						//Returns the anim name inside an AnimSyncEvent node
	MorphemeBundle_EventTrack* GetEventTrackBundle(int signature);				//Returns the event track bundle with the matching m_signature parameter. Returns NULL if not found
	std::vector<EventTrackList*> GetEventTrackListBySignature(int signature);	//Returns all the EventTrackList objects with references to the specified signature
	std::vector<NodeDef*> GetNodesByAnimReference(int anim_idx);				//Returns all node that reference the same animation
};