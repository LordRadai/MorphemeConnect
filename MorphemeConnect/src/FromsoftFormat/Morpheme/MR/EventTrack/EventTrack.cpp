#include "EventTrack.h"
#include "../../../Utils/MemReader/MemReader.h"

using namespace MR;

EventTrack::Event::Event()
{

}

EventTrack::Event::Event(BYTE* pData)
{
	this->m_start = *(float*)(pData);
	this->m_duration = *(float*)(pData + 0x4);
	this->m_userData = *(int*)(pData + 0x8);
}

EventTrack::Event::~Event()
{

}

EventTrack::EventTrack()
{
	this->m_numEvents = 0;
	this->m_userData = 0;
	this->m_channelId = 0;
	this->m_index = 0;
	this->m_trackName = "";
}

EventTrack::EventTrack(BYTE* pData)
{
	this->m_numEvents = *(int*)(pData);
	this->m_index = *(int*)(pData + 0x4);
	this->m_trackName = (char*)(pData + *(UINT64*)(pData + 0x8));
	this->m_userData = *(int*)(pData + 0x10);
	this->m_channelId = *(int*)(pData + 0x14);

	if (this->m_numEvents > 0)
	{
		this->m_events.reserve(this->m_numEvents);

		UINT64 offset = *(UINT64*)(pData + 0x18);
		Event* pEvents = (Event*)(pData + offset);

		for (size_t i = 0; i < this->m_numEvents; i++)
			this->m_events.push_back(Event(pEvents[i]));
	}
}

EventTrack::EventTrack(int index, char* trackName, int userData, int channelID)
{
	this->m_numEvents = 0;
	this->m_index = index;
	this->m_trackName = trackName;
	this->m_userData = userData;
	this->m_channelId = channelID;
}

EventTrack::~EventTrack()
{
	this->m_events.clear();
}

std::string EventTrack::GetTrackName()
{
	return this->m_trackName;
}

int EventTrack::GetIndex()
{
	return this->m_index;
}

int EventTrack::GetChannelID()
{
	return this->m_channelId;
}

int EventTrack::GetNumEvents()
{
	return this->m_numEvents;
}

int EventTrack::GetUserData()
{
	return this->m_userData;
}

EventTrack::Event* EventTrack::GetEvent(int idx)
{
	return &this->m_events[idx];
}

int EventTrack::GetMemoryRequirements()
{
	return 32 + 12 * this->m_numEvents + this->m_trackName.length();
}