#pragma once
#include "../NMBReader/MemHelper/MemHelper.h"

class TimeActEvent
{
public:
	struct EventData
	{
		UINT64 m_id;
		byte m_args[8];

		EventData() {}

		EventData(ifstream* tae)
		{
			MemHelper::ReadQWord(tae, (LPVOID*)&this->m_id);

			UINT64 unk_data_offset;
			MemHelper::ReadQWord(tae, (LPVOID*)&unk_data_offset);

			tae->seekg(unk_data_offset);
			MemHelper::ReadByteArray(tae, (LPVOID*)&this->m_args, 8);
		}
	};

	float m_start;
	float m_end;
	EventData* m_eventData;

	TimeActEvent() {}
	TimeActEvent(ifstream* tae)
	{
		streampos start = tae->tellg();

		UINT64 start_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&start_offset);

		UINT64 end_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&end_offset);

		UINT64 event_data_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&event_data_offset);

		if (start_offset)
		{
			tae->seekg(start_offset);
			
			MemHelper::ReadDWord(tae, (LPVOID*)&this->m_start);
		}

		if (end_offset)
		{
			tae->seekg(end_offset);

			MemHelper::ReadDWord(tae, (LPVOID*)&this->m_end);
		}

		if (event_data_offset)
		{
			tae->seekg(event_data_offset);

			this->m_eventData = new EventData(tae);
		}

		tae->seekg(start + (streampos)0x18);
	}
};

class EventGroup
{
public:
	struct EventGroupData
	{
		UINT64 m_eventType;
		std::vector<int> m_eventOffsets;

		EventGroupData() {}
		EventGroupData(ifstream* tae, int count)
		{
			streampos bak = tae->tellg();

			MemHelper::ReadQWord(tae, (LPVOID*)&this->m_eventType);

			UINT64 offset;
			MemHelper::ReadQWord(tae, (LPVOID*)&offset);

			tae->seekg(offset);

			for (size_t i = 0; i < count; i++)
			{
				UINT64 offset;
				MemHelper::ReadQWord(tae, (LPVOID*)&offset);

				this->m_eventOffsets.push_back(offset);
			}
			tae->seekg(bak + (streampos)0x20);
		}
	};

	UINT64 m_count;
	std::vector<TimeActEvent> m_event;
	EventGroupData* m_groupData;
	UINT64 m_pad;

	EventGroup() {}
	EventGroup(ifstream* tae)
	{
		streampos bak = tae->tellg();

		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_count);

		UINT64 offsetsOffset;
		MemHelper::ReadQWord(tae, (LPVOID*)&offsetsOffset);

		UINT64 groupOffset;
		MemHelper::ReadQWord(tae, (LPVOID*)&groupOffset);

		if (this->m_count > 0)
		{
			if (offsetsOffset)
			{
				for (size_t i = 0; i < this->m_count; i++)
				{
					tae->seekg(offsetsOffset);

					UINT64 event_offset;
					MemHelper::ReadQWord(tae, (LPVOID*)&event_offset);

					tae->seekg(event_offset);

					this->m_event.push_back(tae);

					offsetsOffset += 0x8;
				}
			}

			if (groupOffset)
			{
				tae->seekg(groupOffset);

				this->m_groupData = new EventGroupData(tae, this->m_count);
			}
		}

		bak += 0x20;
		tae->seekg(bak);
	}
};

class TimeActData
{
public:
	std::vector<TimeActEvent> m_events;
	std::vector<EventGroup> m_groups;
	std::vector<float> m_times;
	byte m_unkData[32];
	int m_eventCount;
	int m_eventGroupCount;
	int m_timeCount;

	TimeActData() {}

	TimeActData(ifstream* tae)
	{
		UINT64 header_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&header_offset);

		UINT64 group_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&group_offset);

		UINT64 times_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&times_offset);

		UINT64 unk_data_offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&unk_data_offset);

		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_eventCount);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_eventGroupCount);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_timeCount);

		if (header_offset)
		{
			tae->seekg(header_offset);

			for (size_t i = 0; i < this->m_eventCount; i++)
				this->m_events.push_back(TimeActEvent(tae));
		}

		if (group_offset)
		{
			streampos bak = tae->tellg();

			tae->seekg(group_offset);

			for (size_t i = 0; i < this->m_eventGroupCount; i++)
				this->m_groups.push_back(EventGroup(tae));
		}

		if (unk_data_offset)
		{
			streampos bak = tae->tellg();

			tae->seekg(unk_data_offset);

			MemHelper::ReadByteArray(tae, (LPVOID*)this->m_unkData, 32);
		}
	}

	~TimeActData();
};

class TimeAct
{
public:
	UINT64 m_id;
	TimeActData* m_taeData;

	TimeAct() {}
	TimeAct(ifstream* tae)
	{
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_id);

		UINT64 offset;
		MemHelper::ReadQWord(tae, (LPVOID*)&offset);

		streampos bak = tae->tellg();
		tae->seekg(offset);
		this->m_taeData = new TimeActData(tae);
		tae->seekg(bak);
	}
};

class TimeActGroup
{
public:
	int m_taeStart;
	int m_taeEnd;
	std::vector< TimeAct> m_tae;

	TimeActGroup() {}
	TimeActGroup(ifstream* tae);
};

class TimeActLookupTable
{
public:
	int m_groupCount;
	std::vector<TimeActGroup> m_groups;

	TimeActLookupTable() {}
	TimeActLookupTable(ifstream* tae);
};

class Header
{
public:
	char m_magic[4];
	byte m_bigEndian;
	byte m_bVar5;
	byte m_bVar6;
	byte m_is64Bit;
	int m_version;
	int m_fileSize;
	UINT64 m_flagsOffset;
	UINT64 m_isReadable;
	UINT64 m_fileDataOffset;
	UINT64 m_unkFileDataOffset;
	UINT64 m_iVar30;
	UINT64 m_iVar38;
	byte m_flags[16];
	int m_fileID;
	int m_taeCount;
	UINT64 m_taeOffset;
	UINT64 m_taeLookupTableOffset;
	UINT64 m_iVar68;
	UINT64 m_taeCount2;
	UINT64 m_taeDataOffset;
	byte m_unkData[56];

	Header() {}
	Header(ifstream* tae)
	{
		MemHelper::ReadByteArray(tae, (LPVOID*)this->m_magic, 4);
		MemHelper::ReadByte(tae, (LPVOID*)&this->m_bigEndian);
		MemHelper::ReadByte(tae, (LPVOID*)&this->m_bVar5);
		MemHelper::ReadByte(tae, (LPVOID*)&this->m_bVar6);
		MemHelper::ReadByte(tae, (LPVOID*)&this->m_is64Bit);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_version);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_fileSize);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_flagsOffset);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_isReadable);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_fileDataOffset);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_unkFileDataOffset);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_iVar30);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_iVar38);
		MemHelper::ReadByteArray(tae, (LPVOID*)this->m_flags, 16);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_fileID);
		MemHelper::ReadDWord(tae, (LPVOID*)&this->m_taeCount);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_taeOffset);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_taeLookupTableOffset);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_iVar68);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_taeCount2);
		MemHelper::ReadQWord(tae, (LPVOID*)&this->m_taeDataOffset);
		MemHelper::ReadByteArray(tae, (LPVOID*)this->m_unkData, 0x40);
	}
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
};