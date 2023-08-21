#include "TimeActEvent.h"

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