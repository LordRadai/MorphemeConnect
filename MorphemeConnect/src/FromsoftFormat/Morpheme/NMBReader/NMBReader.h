#pragma once
#include "MorphemeBundle/MorphemeBundle.h"
#include "MorphemeBundle/MorphemeBundle_Header.h"
#include "MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "MorphemeBundle/MorphemeBundle_NetworkDef.h"
#include "MorphemeBundle/MorphemeBundle_FileNameLookupTable.h"
#include "MorphemeBundle/MorphemeBundle_Rig.h"

struct AnimInterface
{
	std::string m_name;
	std::string m_sourceName;
	int m_id;
};

class NMBReader
{
private:
	std::wstring m_fileName;

	PWSTR m_filePath;
	UINT64 m_fileSize;
	PWSTR m_outFilePath;
	UINT64 m_outFileSize;
	bool m_init = false;

	std::vector<AnimInterface> m_animations;

	std::vector<MorphemeBundle> m_bundles;

	std::vector<MorphemeBundle> m_rigRaw;
	std::vector<MorphemeBundle_Rig> m_rig;
	std::vector<MorphemeBundle> m_rigToAnimMap;
	std::vector<MorphemeBundle_EventTrack> m_eventTracks;
	std::vector<MorphemeBundle> m_characterControllerDef;
	MorphemeBundle_NetworkDef m_networkDef;
	MorphemeBundle_Header m_header;
	MorphemeBundle_FileNameLookupTable m_fileNameLookupTable;

	MorphemeBundle m_networkRaw;

public:
	NMBReader() {}
	NMBReader(PWSTR pszFilePath);
	~NMBReader();

	bool IsInitialised();
	std::wstring GetFileName();
	int GetFileSize();
	PWSTR GetFilePath();
	PWSTR GetOutFilePath();
	int GetOutFileSize();
	int GetBundleCount();
	int GetRigCount();
	int GetAnimationCount();

	AnimInterface* GetAnimationInterface(int idx);								
	MorphemeBundle* GetBundle(int idx);											
	MorphemeBundle_NetworkDef* GetNetworkDef();									
	MorphemeBundle_FileNameLookupTable* GetFilenameLookupTable();				
	MorphemeBundle_Rig* GetRig(int idx);								
	MorphemeBundle_EventTrack* GetEventTrackBundle(int signature);				

	MorphemeBundle_EventTrack* AddEventTrack(NodeDef* node_source, int event_id, char* name, bool duration);

	std::string GetSourceAnimName(int idx);										
	std::string GetAnimNameFromAnimNode(NodeDef* m_node);						
	std::vector<EventTrackSet*> GetEventTrackListBySignature(int signature);
	std::vector<NodeDef*> GetNodesByAnimReference(int anim_idx);				
	bool ExportEventTrackToXML(PWSTR pszOutFilePath, int anim_id);
	bool ExportNetworkDefToXML(PWSTR pszOutFilePath);

	void SortAnimList();
	bool SaveToFile(PWSTR pszOutFilePath);
};