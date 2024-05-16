#include "ExportBinary.h"
#include "../../../Utils/MemReader/MemReader.h"

using namespace ME;

void ME::ExportEvent(ofstream* out, int alignment, EventTrack::Event* event)
{
	MemReader::Write(out, event->m_start);
	MemReader::Write(out, event->m_duration);
	MemReader::Write(out, event->m_userData);
}

void ME::ExportAttribute(ofstream* out, int alignment, Attribute* attribute)
{

}

void ME::ExportNodeDef(ofstream* out, int alignment, NodeDef* nodeDef)
{

}

void ME::ExportNetworkDef(ofstream* out, int alignment, NetworkDef* networkDef)
{

}

void ME::ExportEventTrack(ofstream* out, int alignment, EventTrack* eventTrack)
{
	MemReader::Write(out, eventTrack->GetNumEvents());
	MemReader::Write(out, eventTrack->GetIndex());

	MemReader::Write(out, (UINT64)(32 + 12 * eventTrack->GetNumEvents()));

	MemReader::Write(out, eventTrack->GetUserData());
	MemReader::Write(out, eventTrack->GetChannelID());
	MemReader::Write(out, (UINT64)32);

	for (size_t i = 0; i < eventTrack->GetNumEvents(); i++)
		ME::ExportEvent(out, alignment, eventTrack->GetEvent(i));

	int str_len = eventTrack->GetTrackName().length() + 1;

	MemReader::WriteArray(out, eventTrack->GetTrackName().c_str(), str_len);
}

void ME::ExportStringTable(ofstream* out, int alignment, StringTable* table)
{
	MemReader::Write(out, table->GetNumEntries());
	MemReader::Write(out, table->GetDataLenght());
	MemReader::Write(out, (UINT64)32);
	MemReader::Write(out, (UINT64)(32 + table->GetNumEntries() * 4));
	MemReader::Write(out, (UINT64)(32 + table->GetNumEntries() * 8));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::Write(out, table->GetID(i));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::Write(out, table->GetOffset(i));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::WriteArray(out, table->GetString(i).c_str(), table->GetString(i).length() + 1);
}