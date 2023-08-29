#pragma once
#include "TimeActEvent/TimeActEvent.h"

class AnimData
{
public:
	UINT64 m_reference;
	UINT64 m_nextOffsetOffset;
	UINT64 m_nextOffset;
	int m_readable;
	int m_iVar1C;
	UINT64 m_pad[2];

	AnimData();
	AnimData(ifstream* tae);
	~AnimData();

	void GenerateBinary(ofstream* tae);
};

class TimeActData
{
public:
	int m_eventCount;
	int m_eventGroupCount;
	int m_timeCount;

	UINT64 m_eventOffset;
	UINT64 m_eventGroupOffset;
	UINT64 m_timesOffset;
	UINT64 m_unkDataOffset;

	std::vector<TimeActEvent> m_events;
	std::vector<EventGroup> m_groups;
	std::vector<float> m_times;
	AnimData* m_unkData;

	TimeActData();
	TimeActData(ifstream* tae);
	~TimeActData();

	void GenerateBinary(ofstream* tae);
};

class TimeAct
{
public:
	UINT64 m_id;
	UINT64 m_taeOffset;

	TimeActData* m_taeData;

	TimeAct();
	TimeAct(ifstream* tae);

	void GenerateBinary(ofstream* tae);
};

class TimeActGroup
{
public:
	int m_taeStart = 0;
	int m_taeEnd = 0;
	std::vector< TimeAct> m_tae;

	TimeActGroup();
	TimeActGroup(int startTae, int endTae);
	TimeActGroup(ifstream* tae);
};

class TimeActLookupTable
{
public:
	int m_groupCount = 0;
	UINT64 m_groupOffset = 0;

	std::vector<TimeActGroup> m_groups;

	TimeActLookupTable();
	TimeActLookupTable(ifstream* tae);

	void AddGroup(int tae_id);
	void GenerateBinary(ofstream* tae);
};

class Header
{
public:
	char m_magic[4];
	BYTE m_bigEndian;
	BYTE m_bVar5;
	BYTE m_bVar6;
	BYTE m_is64Bit;
	int m_version;
	int m_fileSize;
	UINT64 m_flagsOffset;
	UINT64 m_isReadable;
	UINT64 m_fileDataOffset;
	UINT64 m_unkFileDataOffset;
	UINT64 m_iVar30;
	UINT64 m_iVar38;
	BYTE m_flags[16];
	int m_fileID;
	int m_taeCount;
	UINT64 m_taeOffset;
	UINT64 m_taeLookupTableOffset;
	UINT64 m_iVar68;
	UINT64 m_taeCount2;
	UINT64 m_taeDataOffset;
	BYTE m_unkData[64];

	Header();
	Header(ifstream* tae);

	void GenerateBinary(ofstream* tae);
};

class TimeActReader
{
public:
	PWSTR m_filePath;
	UINT64 m_fileSize;
	PWSTR m_outFilePath;
	UINT64 m_outFileSize;
	bool m_init = false;

	Header m_header;
	std::vector<TimeAct> m_tae;
	TimeActLookupTable m_lookupTable;

	TimeActReader();
	TimeActReader(PWSTR filePath);
	~TimeActReader();

	void AdjustOffsets();
	bool SaveFile(PWSTR pszOutFilePath);
	void CreateTaeGroups();
	TimeAct* TimeActLookup(int id);
};