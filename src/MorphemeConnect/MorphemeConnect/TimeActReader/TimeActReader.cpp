#include "TimeActReader.h"

TimeActEvent::EventData::EventData() {}

TimeActEvent::EventData::EventData(ifstream* tae)
{
	MemReader::ReadQWord(tae, &this->m_id);

	UINT64 unk_data_offset;
	MemReader::ReadQWord(tae, &unk_data_offset);

	tae->seekg(unk_data_offset);
	MemReader::ReadByteArray(tae, this->m_args, 8);
}

TimeActEvent::TimeActEvent() {}

TimeActEvent::TimeActEvent(ifstream* tae)
{
	streampos start = tae->tellg();

	UINT64 start_offset;
	MemReader::ReadQWord(tae, &start_offset);

	UINT64 end_offset;
	MemReader::ReadQWord(tae, &end_offset);

	UINT64 event_data_offset;
	MemReader::ReadQWord(tae, &event_data_offset);

	if (start_offset)
	{
		tae->seekg(start_offset);

		MemReader::ReadDWord(tae, (DWORD*)&this->m_start);
	}

	if (end_offset)
	{
		tae->seekg(end_offset);

		MemReader::ReadDWord(tae, (DWORD*)&this->m_end);
	}

	if (event_data_offset)
	{
		tae->seekg(event_data_offset);

		this->m_eventData = new EventData(tae);
	}

	tae->seekg(start + (streampos)0x18);
}


EventGroup::EventGroupData::EventGroupData() {}

EventGroup::EventGroupData::EventGroupData(ifstream* tae, int count)
{
	streampos bak = tae->tellg();

	MemReader::ReadQWord(tae, &this->m_eventType);

	UINT64 offset;
	MemReader::ReadQWord(tae, &offset);

	tae->seekg(offset);

	for (size_t i = 0; i < count; i++)
	{
		UINT64 offset;
		MemReader::ReadQWord(tae, &offset);

		this->m_eventOffsets.push_back(offset);
	}
	tae->seekg(bak + (streampos)0x20);
}

EventGroup::EventGroup() {}

EventGroup::EventGroup(ifstream* tae)
{
	streampos bak = tae->tellg();

	MemReader::ReadQWord(tae, &this->m_count);

	UINT64 offsetsOffset;
	MemReader::ReadQWord(tae, &offsetsOffset);

	UINT64 groupOffset;
	MemReader::ReadQWord(tae, &groupOffset);

	if (this->m_count > 0)
	{
		if (offsetsOffset)
		{
			for (size_t i = 0; i < this->m_count; i++)
			{
				tae->seekg(offsetsOffset);

				UINT64 event_offset;
				MemReader::ReadQWord(tae, &event_offset);

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

TimeActData::TimeActData() {}

TimeActData::TimeActData(ifstream* tae)
{
	UINT64 header_offset;
	MemReader::ReadQWord(tae, &header_offset);

	UINT64 group_offset;
	MemReader::ReadQWord(tae, &group_offset);

	UINT64 times_offset;
	MemReader::ReadQWord(tae, &times_offset);

	UINT64 unk_data_offset;
	MemReader::ReadQWord(tae, &unk_data_offset);

	MemReader::ReadDWord(tae, (DWORD*)&this->m_eventCount);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_eventGroupCount);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_timeCount);

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

		MemReader::ReadByteArray(tae, this->m_unkData, 32);
	}
}

TimeActData::~TimeActData()
{

}

TimeAct::TimeAct() {}

TimeAct::TimeAct(ifstream* tae)
{
	MemReader::ReadQWord(tae, &this->m_id);

	UINT64 offset;
	MemReader::ReadQWord(tae, &offset);

	streampos bak = tae->tellg();
	tae->seekg(offset);
	this->m_taeData = new TimeActData(tae);
	tae->seekg(bak);
}

TimeActGroup::TimeActGroup() {}

TimeActGroup::TimeActGroup(ifstream* tae) {}

TimeActLookupTable::TimeActLookupTable() {}

TimeActLookupTable::TimeActLookupTable(ifstream* tae) {}

Header::Header() {}

Header::Header(ifstream* tae)
{
	MemReader::ReadByteArray(tae, (BYTE*)this->m_magic, 4);
	MemReader::ReadByte(tae, &this->m_bigEndian);
	MemReader::ReadByte(tae, &this->m_bVar5);
	MemReader::ReadByte(tae, &this->m_bVar6);
	MemReader::ReadByte(tae, &this->m_is64Bit);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_version);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_fileSize);
	MemReader::ReadQWord(tae, &this->m_flagsOffset);
	MemReader::ReadQWord(tae, &this->m_isReadable);
	MemReader::ReadQWord(tae, &this->m_fileDataOffset);
	MemReader::ReadQWord(tae, &this->m_unkFileDataOffset);
	MemReader::ReadQWord(tae, &this->m_iVar30);
	MemReader::ReadQWord(tae, &this->m_iVar38);
	MemReader::ReadByteArray(tae, this->m_flags, 16);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_fileID);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_taeCount);
	MemReader::ReadQWord(tae, &this->m_taeOffset);
	MemReader::ReadQWord(tae, &this->m_taeLookupTableOffset);
	MemReader::ReadQWord(tae, &this->m_iVar68);
	MemReader::ReadQWord(tae, &this->m_taeCount2);
	MemReader::ReadQWord(tae, &this->m_taeDataOffset);
	MemReader::ReadByteArray(tae, this->m_unkData, 0x40);
}

TimeActReader::TimeActReader()
{
}

TimeActReader::TimeActReader(PWSTR filePath)
{

	this->m_init = false;
	this->m_filePath = filePath;

	ifstream tae;

	tae.open(this->m_filePath, ios::binary);
	this->m_header = Header(&tae);

	this->m_fileSize = this->m_header.m_fileSize;

	this->m_tae.reserve(this->m_header.m_taeCount);

	for (int i = 0; i < this->m_header.m_taeCount; i++)
		this->m_tae.push_back(TimeAct(&tae));

	tae.close();

	this->m_init = true;
}

TimeActReader::~TimeActReader()
{
}

TimeAct* TimeActReader::TimeActLookup(int id)
{
	for (size_t i = 0; i < this->m_tae.size(); i++)
	{
		if (this->m_tae[i].m_id == id)
			return &this->m_tae[i];
	}

	return NULL;
}