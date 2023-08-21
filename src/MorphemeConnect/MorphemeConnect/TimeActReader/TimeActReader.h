#pragma once
#include "../MemReader/MemReader.h"
class TimeActEvent
{
public:
	struct EventData
	{
		UINT64 m_id;
		BYTE m_args[8];

		EventData();
		EventData(ifstream* tae);
	};

	float m_start;
	float m_end;
	EventData* m_eventData;

	TimeActEvent();
	TimeActEvent(ifstream* tae);
};

class EventGroup
{
public:
	struct EventGroupData
	{
		UINT64 m_eventType;
		std::vector<int> m_eventOffsets;

		EventGroupData();
		EventGroupData(ifstream* tae, int count);
	};

	UINT64 m_count;
	std::vector<TimeActEvent> m_event;
	EventGroupData* m_groupData;
	UINT64 m_pad;

	EventGroup();
	EventGroup(ifstream* tae);
};

class TimeActData
{
public:
	std::vector<TimeActEvent> m_events;
	std::vector<EventGroup> m_groups;
	std::vector<float> m_times;
	BYTE m_unkData[32];
	int m_eventCount;
	int m_eventGroupCount;
	int m_timeCount;

	TimeActData();

	TimeActData(ifstream* tae);

	~TimeActData();
};

class TimeAct
{
public:
	UINT64 m_id;
	TimeActData* m_taeData;

	TimeAct();
	TimeAct(ifstream* tae);
};

class TimeActGroup
{
public:
	int m_taeStart;
	int m_taeEnd;
	std::vector< TimeAct> m_tae;

	TimeActGroup();
	TimeActGroup(ifstream* tae);
};

class TimeActLookupTable
{
public:
	int m_groupCount;
	std::vector<TimeActGroup> m_groups;

	TimeActLookupTable();
	TimeActLookupTable(ifstream* tae);
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
	BYTE m_unkData[56];

	Header();
	Header(ifstream* tae);
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

	TimeAct* TimeActLookup(int id);
};