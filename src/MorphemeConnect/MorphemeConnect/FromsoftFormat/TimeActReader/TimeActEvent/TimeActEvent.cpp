#include "TimeActEvent.h"

TimeActEventData* getArguments(int id)
{
	switch (id)
	{
	case 100:
		return new TimeActEventData_NoArgs;
	case 201:
		return new TimeActEventData_Sound201;
	case 202:
		return new TimeActEventData_Sound202;
	case 300:
		return new TimeActEventData_Ai300;
	case 301:
		return new TimeActEventData_Ai300;
	case 1220:
		return new TimeActEventData_NoArgs;
	case 1230:
		return new TimeActEventData_NoArgs;
	case 1500:
		return new TimeActEventData_Camera1500;
	case 1501:
		return new TimeActEventData_Camera1501;
	case 1502:
		return new TimeActEventData_Camera1502;
	case 1503:
		return new TimeActEventData_Camera1503;
	case 1504:
		return new TimeActEventData_Camera1504;
	case 2100:
		return new TimeActEventData_NoArgs;
	case 2101:
		return new TimeActEventData_NoArgs;
	case 2102:
		return new TimeActEventData_NoArgs;
	case 2103:
		return new TimeActEventData_Sfx2103;
	case 2104:
		return new TimeActEventData_Sfx2104;
	case 2105:
		return new TimeActEventData_NoArgs;
	case 2106:
		return new TimeActEventData_Sfx2106;
	case 2200:
		return new TimeActEventData_Damage2200;
	case 2201:
		return new TimeActEventData_Damage2201;
	case 2202:
		return new TimeActEventData_Damage2202;
	case 2203:
		return new TimeActEventData_Damage2203;
	case 2300:
		return new TimeActEventData_Bullet2300;
	case 2301:
		return new TimeActEventData_Bullet2301;
	case 2400:
		return new TimeActEventData_NoArgs;
	case 2401:
		return new TimeActEventData_NoArgs;
	case 2402:
		return new TimeActEventData_FootEffect2402;
	case 2403:
		return new TimeActEventData_NoArgs;
	case 2500:
		return new TimeActEventData_Weapon2500;
	case 2501:
		return new TimeActEventData_Weapon2501;
	case 2502:
		return new TimeActEventData_NoArgs;
	case 2600:
		return new TimeActEventData_NoArgs;
	case 101100:
		return new TimeActEventData_NoArgs;
	case 110000:
		return new TimeActEventData_NoArgs;
	case 110100:
		return new TimeActEventData_NoArgs;
	case 110200:
		return new TimeActEventData_NoArgs;
	case 110210:
		return new TimeActEventData_NoArgs;
	case 110300:
		return new TimeActEventData_NoArgs;
	case 110400:
		return new TimeActEventData_NoArgs;
	case 110500:
		return new TimeActEventData_NoArgs;
	case 110600:
		return new TimeActEventData_NoArgs;
	case 110700:
		return new TimeActEventData_NoArgs;
	case 110800:
		return new TimeActEventData_NoArgs;
	case 110900:
		return new TimeActEventData_NoArgs;
	case 111000:
		return new TimeActEventData_DamageAction111000;
	case 111100:
		return new TimeActEventData_NoArgs;
	case 111200:
		return new TimeActEventData_NoArgs;
	case 111300:
		return new TimeActEventData_NoArgs;
	case 111400:
		return new TimeActEventData_NoArgs;
	case 111500:
		return new TimeActEventData_NoArgs;
	case 111600:
		return new TimeActEventData_NoArgs;
	case 111700:
		return new TimeActEventData_NoArgs;
	case 111800:
		return new TimeActEventData_NoArgs;
	case 111900:
		return new TimeActEventData_NoArgs;
	case 120100:
		return new TimeActEventData_NoArgs;
	case 120200:
		return new TimeActEventData_NoArgs;
	case 120300:
		return new TimeActEventData_NoArgs;
	case 210000:
		return new TimeActEventData_NoArgs;
	case 210099:
		return new TimeActEventData_NoArgs;
	case 210100:
		return new TimeActEventData_NoArgs;
	case 210200:
		return new TimeActEventData_NoArgs;
	case 220000:
		return new TimeActEventData_NoArgs;
	case 220100:
		return new TimeActEventData_NoArgs;
	case 220200:
		return new TimeActEventData_Item220200;
	case 220300:
		return new TimeActEventData_NoArgs;
	case 230000:
		return new TimeActEventData_NoArgs;
	case 230001:
		return new TimeActEventData_NoArgs;
	case 240000:
		return new TimeActEventData_NoArgs;
	case 250000:
		return new TimeActEventData_NoArgs;
	case 260000:
		return new TimeActEventData_NoArgs;
	case 260001:
		return new TimeActEventData_Model260001;
	case 260002:
		return new TimeActEventData_Model260002;
	case 260003:
		return new TimeActEventData_NoArgs;
	case 260004:
		return new TimeActEventData_Model260004;
	case 260005:
		return new TimeActEventData_Model260005;
	case 260006:
		return new TimeActEventData_Model260006;
	case 270000:
		return new TimeActEventData_Model270000;
	case 270001:
		return new TimeActEventData_NoArgs;
	case 270002:
		return new TimeActEventData_NoArgs;
	case 280000:
		return new TimeActEventData_NoArgs;
	case 280100:
		return new TimeActEventData_Move280100;
	case 290000:
		return new TimeActEventData_NoArgs;
	case 290001:
		return new TimeActEventData_NoArgs;
	case 290002:
		return new TimeActEventData_NoArgs;
	case 300000:
		return new TimeActEventData_Event300000;
	case 300100:
		return new TimeActEventData_Event300100;
	case 300200:
		return new TimeActEventData_Event300200;
	case 300300:
		return new TimeActEventData_Event300300;
	case 310000:
		return new TimeActEventData_SpEffect310000;
	default:
		return new TimeActEventData_NoArgs;
	}
}

TimeActEvent::EventData::EventData() 
{
	this->m_id = 0;
	this->m_pad = 0;
	this->m_args = getArguments(-1);
}

TimeActEvent::EventData::EventData(int id)
{
	this->m_id = id;

	this->m_args = getArguments(id);
}

TimeActEvent::EventData::EventData(ifstream* tae)
{
	MemReader::ReadDWord(tae, (DWORD*)&this->m_id);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_pad);
	MemReader::ReadQWord(tae, &this->m_argsOffset);

	tae->seekg(m_argsOffset);

	this->m_args = getArguments(this->m_id);

	this->m_args->GetData(tae);
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

	this->m_eventData->m_args->SaveData(tae);

	tae->seekp(bak);
}

int TimeActEvent::GetArgumentsSize()
{
	int size = 64;

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

		if (m_groupDataOffset)
		{
			tae->seekg(m_groupDataOffset);

			this->m_groupData = new EventGroupData(tae);
		}
	}

	bak += 0x20;
	tae->seekg(bak);
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