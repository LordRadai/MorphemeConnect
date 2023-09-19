#include "TimeActEvent.h"

TimeActEvent::EventData::EventData() 
{
	this->m_id = 0;
	this->m_pad = 0;
	this->m_args = new TimeActEventData;
}

TimeActEvent::EventData::EventData(int event_id)
{
	this->m_id = event_id;

	this->m_args = new TimeActEventData;
	this->m_args->CreateArguments(event_id);
}

TimeActEvent::EventData::EventData(ifstream* tae)
{
	MemReader::ReadDWord(tae, (DWORD*)&this->m_id);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_pad);
	MemReader::ReadQWord(tae, &this->m_argsOffset);

	this->m_args = new TimeActEventData;
}

TimeActEvent::EventData::~EventData()
{
}

TimeActEvent::TimeActEvent()
{
	this->m_start = 0;
	this->m_end = 0;
	this->m_eventData = new EventData();
}

TimeActEvent::TimeActEvent(float start, float end, int id)
{
	this->m_start = start;
	this->m_end = end;
	this->m_eventData = new EventData(id);
}

TimeActEvent::TimeActEvent(ifstream* tae)
{
	streampos start = tae->tellg();

	MemReader::ReadQWord(tae, &this->m_startOffset);
	MemReader::ReadQWord(tae, &this->m_endOffset);
	MemReader::ReadQWord(tae, &this->m_eventDataOffset);

	if (m_startOffset)
	{
		tae->seekg(m_startOffset);

		MemReader::ReadDWord(tae, (DWORD*)&this->m_start);
	}

	if (m_endOffset)
	{
		tae->seekg(m_endOffset);

		MemReader::ReadDWord(tae, (DWORD*)&this->m_end);
	}

	if (m_eventDataOffset)
	{
		tae->seekg(m_eventDataOffset);

		this->m_eventData = new EventData(tae);
	}

	tae->seekg(start + (streampos)0x18);
}

TimeActEvent::~TimeActEvent()
{
}

void TimeActEvent::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, &this->m_startOffset);
	MemReader::WriteQWord(tae, &this->m_endOffset);
	MemReader::WriteQWord(tae, &this->m_eventDataOffset);

	UINT64 bak = tae->tellp();
	tae->seekp(m_eventDataOffset);

	MemReader::WriteDWord(tae, (DWORD*)&this->m_eventData->m_id);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_eventData->m_pad);

	MemReader::WriteQWord(tae, &this->m_eventData->m_argsOffset);

	tae->seekp(this->m_eventData->m_argsOffset);

	this->m_eventData->m_args->GenerateBinary(tae);

	tae->seekp(bak);
}

int TimeActEvent::GetArgumentsSize()
{
	int size = this->m_eventData->m_args->m_size;

	int remainder = size % 16;

	if (remainder != 0)
		size += 16 - remainder;

	return size + 0x18;
}

EventGroup::EventGroupData::EventGroupData() {}

EventGroup::EventGroupData::EventGroupData(ifstream* tae)
{
	streampos bak = tae->tellg();

	MemReader::ReadQWord(tae, &this->m_eventType);
	MemReader::ReadQWord(tae, &this->m_offset);
}

EventGroup::EventGroup() 
{
	this->m_count = 0;
	this->m_pad = 0;
}

EventGroup::EventGroup(int id)
{
	this->m_count = 0;
	this->m_pad = 0;

	this->m_groupData = new EventGroupData;

	this->m_groupData->m_eventType = id;
}

EventGroup::EventGroup(ifstream* tae, UINT64 eventStartOffset)
{
	streampos bak = tae->tellg();

	MemReader::ReadQWord(tae, &this->m_count);
	MemReader::ReadQWord(tae, &this->m_eventsOffset);
	MemReader::ReadQWord(tae, &this->m_groupDataOffset);
	MemReader::ReadQWord(tae, &this->m_pad);

	if (this->m_count > 0)
	{
		if (m_eventsOffset)
		{
			UINT64 offset = m_eventsOffset;

			for (size_t i = 0; i < this->m_count; i++)
			{
				tae->seekg(offset);

				UINT64 event_offset;
				MemReader::ReadQWord(tae, &event_offset);
				this->m_eventOffset.push_back(event_offset);

				int idx = (event_offset - eventStartOffset) / 0x18;

				this->m_eventIndex.push_back(idx);

				tae->seekg(event_offset);

				offset += 0x8;
			}
		}
	}

	if (m_groupDataOffset)
	{
		tae->seekg(m_groupDataOffset);

		this->m_groupData = new EventGroupData(tae);
	}

	bak += 0x20;
	tae->seekg(bak);
}

EventGroup::~EventGroup()
{
}

void EventGroup::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, &this->m_count);
	MemReader::WriteQWord(tae, &this->m_eventsOffset);
	MemReader::WriteQWord(tae, &this->m_groupDataOffset);

	UINT64 pad0 = 0;
	MemReader::WriteQWord(tae, &pad0);

	UINT64 bak = tae->tellp();

	if (this->m_count)
	{
		tae->seekp(m_groupDataOffset);

		MemReader::WriteQWord(tae, &this->m_groupData->m_eventType);
		MemReader::WriteQWord(tae, &this->m_groupData->m_offset);

		UINT64 pad0[2] = { 0, 0 };
		MemReader::WriteQWordArray(tae, pad0, 2);

		tae->seekp(m_eventsOffset);

		for (size_t i = 0; i < this->m_count; i++)
			MemReader::WriteQWord(tae, &this->m_eventOffset[i]);
	}

	tae->seekp(bak);
}