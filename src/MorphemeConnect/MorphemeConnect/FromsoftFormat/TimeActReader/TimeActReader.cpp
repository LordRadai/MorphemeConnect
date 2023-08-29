#include "TimeActReader.h"

AnimData::AnimData()
{
}

AnimData::AnimData(ifstream* tae)
{
	MemReader::ReadQWord(tae, &this->m_reference);
	MemReader::ReadQWord(tae, &this->m_nextOffsetOffset);
	MemReader::ReadQWord(tae, &this->m_nextOffset);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_readable);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar1C);
	MemReader::ReadQWordArray(tae, this->m_pad, 2);
}

AnimData::~AnimData()
{
}

void AnimData::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, &this->m_reference);
	MemReader::WriteQWord(tae, &this->m_nextOffsetOffset);
	MemReader::WriteQWord(tae, &this->m_nextOffset);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_readable);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar1C);
	MemReader::WriteQWordArray(tae, this->m_pad, 2);
}

TimeActData::TimeActData() {}

TimeActData::TimeActData(ifstream* tae)
{
	MemReader::ReadQWord(tae, &this->m_eventOffset);
	MemReader::ReadQWord(tae, &this->m_eventGroupOffset);
	MemReader::ReadQWord(tae, &this->m_timesOffset);
	MemReader::ReadQWord(tae, &this->m_unkDataOffset);

	MemReader::ReadDWord(tae, (DWORD*)&this->m_eventCount);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_eventGroupCount);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_timeCount);

	if (m_eventOffset)
	{
		tae->seekg(m_eventOffset);

		for (size_t i = 0; i < this->m_eventCount; i++)
			this->m_events.push_back(TimeActEvent(tae));
	}

	if (m_eventGroupOffset)
	{
		streampos bak = tae->tellg();

		tae->seekg(m_eventGroupOffset);

		for (size_t i = 0; i < this->m_eventGroupCount; i++)
			this->m_groups.push_back(EventGroup(tae));
	}

	if (m_unkDataOffset)
	{
		streampos bak = tae->tellg();

		tae->seekg(m_unkDataOffset);

		this->m_unkData = new AnimData(tae);
	}
}

TimeActData::~TimeActData()
{

}

void TimeActData::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, &this->m_eventOffset);
	MemReader::WriteQWord(tae, &this->m_eventGroupOffset);
	MemReader::WriteQWord(tae, &this->m_timesOffset);
	MemReader::WriteQWord(tae, &this->m_unkDataOffset);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_eventCount);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_eventGroupCount);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_timeCount);

	DWORD pad = 0;
	MemReader::WriteDWord(tae, &pad);

	UINT64 bak = tae->tellp();

	tae->seekp(m_unkDataOffset);
	this->m_unkData->GenerateBinary(tae);

	tae->seekp(m_timesOffset);

	for (size_t i = 0; i < this->m_eventCount; i++)
	{
		MemReader::WriteDWord(tae, (DWORD*)&this->m_events[i].m_start);
		MemReader::WriteDWord(tae, (DWORD*)&this->m_events[i].m_end);
	}

	tae->seekp(m_eventOffset);

	for (size_t i = 0; i < this->m_eventCount; i++)
		this->m_events[i].GenerateBinary(tae);

	tae->seekp(m_eventGroupOffset);

	for (size_t i = 0; i < this->m_eventGroupCount; i++)
		this->m_groups[i].GenerateBinary(tae);

	tae->seekp(bak);
}

TimeAct::TimeAct() {}

TimeAct::TimeAct(ifstream* tae)
{
	MemReader::ReadQWord(tae, &this->m_id);
	MemReader::ReadQWord(tae, &this->m_taeOffset);

	streampos bak = tae->tellg();
	tae->seekg(this->m_taeOffset);
	this->m_taeData = new TimeActData(tae);
	tae->seekg(bak);
}

void TimeAct::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, &this->m_id);
	MemReader::WriteQWord(tae, &this->m_taeOffset);

	UINT64 bak = tae->tellp();

	tae->seekp(m_taeOffset);
	this->m_taeData->GenerateBinary(tae);

	tae->seekp(bak);
}

TimeActGroup::TimeActGroup() {}

TimeActGroup::TimeActGroup(int startTae, int endTae)
{
	this->m_taeStart = startTae;
	this->m_taeEnd = endTae;
}

TimeActGroup::TimeActGroup(ifstream* tae) {}

TimeActLookupTable::TimeActLookupTable() {}

TimeActLookupTable::TimeActLookupTable(ifstream* tae) {}

void TimeActLookupTable::AddGroup(int tae_id)
{
	bool found = false;

	if (this->m_groups.size() == 0)
	{
		this->m_groupCount++;
		this->m_groups.push_back(TimeActGroup(tae_id, tae_id));

		return;
	}

	//Look at the last inserted TAE
	if ((tae_id - this->m_groups.back().m_taeStart) < 10)
	{
		this->m_groups.back().m_taeEnd = tae_id;
		found = true;
	}

	//If it's not the last, go look at the previous TAE groups created. This should never get executed, TAE list should be ordered by increasing TAE ID
	if (!found)
	{
		for (size_t i = 0; i < this->m_groupCount; i++)
		{
			if ((tae_id - this->m_groups[i].m_taeStart) < 10)
			{
				this->m_groups[i].m_taeEnd = tae_id;
				found = true;
				break;
			}
		}

		if (!found)
		{
			this->m_groupCount++;
			this->m_groups.push_back(TimeActGroup(tae_id, tae_id));
		}
	}
}

void TimeActLookupTable::GenerateBinary(ofstream* tae)
{
	MemReader::WriteQWord(tae, (UINT64*)&this->m_groupCount);

	UINT64 offset = tae->tellp();
	offset += 0x8;

	MemReader::WriteQWord(tae, &offset);

	int group_count = 1;
	for (int i = 0; i < this->m_groupCount; i++)
	{
		MemReader::WriteDWord(tae, (DWORD*)&this->m_groups[i].m_taeStart);
		MemReader::WriteDWord(tae, (DWORD*)&this->m_groups[i].m_taeEnd);

		UINT64 tae_offset = 0xC0 + (BYTE)group_count * 0x10;
		MemReader::WriteQWord(tae, &tae_offset);

		group_count = this->m_groups[i].m_taeEnd - this->m_groups[i].m_taeStart;
	}
}

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

void Header::GenerateBinary(ofstream* tae)
{
	BYTE magic[4] = {0x54, 0x41, 0x45, 0x20};
	MemReader::WriteByteArray(tae, magic, 4);
	MemReader::WriteByte(tae, &this->m_bigEndian);
	MemReader::WriteByte(tae, &this->m_bVar5);
	MemReader::WriteByte(tae, &this->m_bVar6);
	MemReader::WriteByte(tae, &this->m_is64Bit);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_version);

	MemReader::WriteDWord(tae, (DWORD*)&this->m_fileSize);

	MemReader::WriteQWord(tae, &this->m_flagsOffset);
	MemReader::WriteQWord(tae, &this->m_isReadable);
	MemReader::WriteQWord(tae, &this->m_fileDataOffset);
	MemReader::WriteQWord(tae, &this->m_unkFileDataOffset);
	MemReader::WriteQWord(tae, &this->m_iVar30);
	MemReader::WriteQWord(tae, &this->m_iVar38);

	MemReader::WriteByteArray(tae, this->m_flags, 16);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fileID);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_taeCount);
	MemReader::WriteQWord(tae, &this->m_taeOffset);
	MemReader::WriteQWord(tae, &this->m_taeLookupTableOffset);
	MemReader::WriteQWord(tae, &this->m_iVar68);
	MemReader::WriteQWord(tae, &this->m_taeCount2);
	MemReader::WriteQWord(tae, &this->m_taeDataOffset);

	MemReader::WriteByteArray(tae, this->m_unkData, 64);
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

	this->m_lookupTable.m_groupCount = 0;
	this->m_lookupTable.m_groups.clear();

	tae.close();

	this->m_init = true;
}

TimeActReader::~TimeActReader()
{
}

void TimeActReader::AdjustOffsets()
{
	this->CreateTaeGroups();

	this->m_header.m_taeLookupTableOffset = 0xC0 + 0x10 * this->m_header.m_taeCount;

	this->m_lookupTable.m_groupOffset = this->m_header.m_taeLookupTableOffset + 0x10;

	this->m_header.m_taeDataOffset = this->m_lookupTable.m_groupOffset + this->m_lookupTable.m_groupCount * 0x10;

	for (int i = 0; i < this->m_tae.size(); i++)
		this->m_tae[i].m_taeOffset = this->m_header.m_taeDataOffset + 0x30 * i;

	UINT64 dataBase = this->m_header.m_taeDataOffset + this->m_tae.size() * 0x30;

	UINT64 nextUnkDataOffset = dataBase;
	for (int i = 0; i < this->m_tae.size(); i++)
	{
		this->m_tae[i].m_taeData->m_unkDataOffset = nextUnkDataOffset;

		this->m_tae[i].m_taeData->m_unkData->m_nextOffsetOffset = this->m_tae[i].m_taeData->m_unkDataOffset + 0x10;
		this->m_tae[i].m_taeData->m_unkData->m_nextOffset = this->m_tae[i].m_taeData->m_unkData->m_nextOffsetOffset + 0x20;

		UINT64 biggestOffset = this->m_tae[i].m_taeData->m_unkDataOffset + 0x30;

		if (this->m_tae[i].m_taeData->m_timeCount > 0)
		{
			this->m_tae[i].m_taeData->m_timesOffset = this->m_tae[i].m_taeData->m_unkDataOffset + 0x30;
			biggestOffset = this->m_tae[i].m_taeData->m_timesOffset;
		}

		if (this->m_tae[i].m_taeData->m_eventCount > 0)
		{
			this->m_tae[i].m_taeData->m_timeCount = 2 * this->m_tae[i].m_taeData->m_eventCount;
			this->m_tae[i].m_taeData->m_eventOffset = this->m_tae[i].m_taeData->m_timesOffset + this->m_tae[i].m_taeData->m_timeCount * 0x4;

			biggestOffset = this->m_tae[i].m_taeData->m_eventOffset;
		}
	
		if (this->m_tae[i].m_taeData->m_eventGroupCount > 0)
		{
			UINT64 totalEventsSize = 0;
			for (int j = 0; j < this->m_tae[i].m_taeData->m_eventCount; j++)
			{
				totalEventsSize += this->m_tae[i].m_taeData->m_events[j].GetArgumentsSize();
			}

			this->m_tae[i].m_taeData->m_eventGroupOffset = this->m_tae[i].m_taeData->m_eventOffset + totalEventsSize;
		}
		else
			this->m_tae[i].m_taeData->m_eventGroupOffset = 0;

		for (int j = 0; j < this->m_tae[i].m_taeData->m_eventCount; j++)
		{
			this->m_tae[i].m_taeData->m_events[j].m_startOffset = this->m_tae[i].m_taeData->m_timesOffset + j * 0x8;
			this->m_tae[i].m_taeData->m_events[j].m_endOffset = this->m_tae[i].m_taeData->m_timesOffset + j * 0x8 + 0x4;
			this->m_tae[i].m_taeData->m_events[j].m_eventDataOffset = this->m_tae[i].m_taeData->m_eventOffset + this->m_tae[i].m_taeData->m_eventCount * 0x18 + j * 0x20;
		
			this->m_tae[i].m_taeData->m_events[j].m_eventData->m_argsOffset = this->m_tae[i].m_taeData->m_events[j].m_eventDataOffset + 0x10;

			//TODO adjust pointers to events
		}

		UINT64 groupTotalSize = 0;
		for (int j = 0; j < this->m_tae[i].m_taeData->m_eventGroupCount; j++)
			groupTotalSize += this->m_tae[i].m_taeData->m_groups[j].m_count * 0x8;

		int remainder = groupTotalSize % 16;
		if (remainder != 0)
			groupTotalSize += 16 - remainder;

		UINT64 groupDataBase = this->m_tae[i].m_taeData->m_eventGroupOffset + this->m_tae[i].m_taeData->m_eventGroupCount * 0x20 + 0x20;
		for (int j = 0; j < this->m_tae[i].m_taeData->m_eventGroupCount; j++)
		{
			this->m_tae[i].m_taeData->m_groups[j].m_groupDataOffset = groupDataBase + j * 0x20;
			this->m_tae[i].m_taeData->m_groups[j].m_eventsOffset = this->m_tae[i].m_taeData->m_groups[j].m_groupDataOffset + groupTotalSize;
			
			if (this->m_tae[i].m_taeData->m_groups[j].m_eventsOffset > biggestOffset)
			{
				biggestOffset = this->m_tae[i].m_taeData->m_groups[j].m_eventsOffset + groupTotalSize;
			}
		}

		nextUnkDataOffset = biggestOffset;
	}
}

bool TimeActReader::SaveFile(PWSTR pszOutFilePath)
{
	this->m_outFilePath = pszOutFilePath;

	ofstream out;

	out.open(this->m_outFilePath, ios::binary);

	this->AdjustOffsets();

	this->m_header.GenerateBinary(&out);
	
	out.seekp(this->m_header.m_taeOffset);

	for (int i = 0; i < this->m_tae.size(); i++)
		this->m_tae[i].GenerateBinary(&out);

	out.seekp(this->m_header.m_taeLookupTableOffset);

	this->m_lookupTable.GenerateBinary(&out);

	out.close();

	return true;
}

void TimeActReader::CreateTaeGroups()
{
	this->m_lookupTable.m_groupCount = 0;
	this->m_lookupTable.m_groups.clear();

	//TODO adjust pointers to event groups
	for (int i = 0; i < this->m_tae.size(); i++)
		this->m_lookupTable.AddGroup(this->m_tae[i].m_id);
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