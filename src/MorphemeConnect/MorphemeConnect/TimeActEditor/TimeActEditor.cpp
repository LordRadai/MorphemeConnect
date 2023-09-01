#include "TimeActEditor.h"
#include "../Application/Application.h"
#include "../TaeTemplate/TaeTemplate.h"

TimeActEditor::TimeActTrack::TimeActTrack(int eventId)
{
	this->m_source = NULL;
	this->m_eventGroup = eventId;
}

TimeActEditor::TimeActTrack::TimeActTrack(EventGroup* src)
{
	this->m_source = src;
	this->m_count = src->m_count;

	this->m_eventGroup = src->m_groupData->m_eventType;

	for (size_t i = 0; i < src->m_count; i++)
		this->m_event.push_back(Event{ MathHelper::TimeToFrame(src->m_event[i]->m_start), MathHelper::TimeToFrame(src->m_event[i]->m_end - src->m_event[i]->m_start), (int)src->m_event[i]->m_eventData->m_id,  src->m_event[i]->m_eventData->m_args });
}

void TimeActEditor::TimeActTrack::SaveTimeActTrack()
{
	this->m_source->m_count = this->m_count;
	this->m_source->m_groupData->m_eventType = this->m_eventGroup;

	for (size_t i = 0; i < this->m_count; i++)
	{
		this->m_source->m_event[i]->m_start = MathHelper::FrameToTime(this->m_event[i].m_frameStart);
		this->m_source->m_event[i]->m_end = MathHelper::FrameToTime(this->m_event[i].m_frameStart + this->m_event[i].m_duration);
		this->m_source->m_event[i]->m_eventData->m_id = this->m_event[i].m_value;
	}
}

bool TimeActEditor::TimeActTrack::IsEventActive(int idx, int frame)
{
	if ((frame >= this->m_event[idx].m_frameStart) && frame <= (this->m_event[idx].m_duration + this->m_event[idx].m_frameStart))
		return true;

	return false;
}

int TimeActEditor::GetFrameMin() const
{
	return m_frameMin;
}

int TimeActEditor::GetFrameMax() const
{
	return m_frameMax;
}

int TimeActEditor::GetTrackCount() const { return (int)m_tracks.size(); }

TimeActEditor::TimeActEditor() 
{
	this->m_source = nullptr;

	INIReader reader(".//MorphemeConnect//res//color//timeact.ini");

	if (reader.ParseError() < 0) 
	{
		Debug::Alert(Debug::LVL_ERROR, "TimeActEditor.cpp", "Failed to load timeact.ini\n");

		this->m_colors.m_trackColor = { 0.33f, 0.33f, 0.33f, 1.f };
		this->m_colors.m_trackColorInactive = { 0.33f, 0.33f, 0.33f, 1.f };
		this->m_colors.m_trackColorActive = { 0.f, 0.4f, 0.8f, 1.f };
		this->m_colors.m_trackBoundingBox = { 0.f, 0.f, 0.f, 1.f };
		this->m_colors.m_trackBoundingBoxActive = { 1.f, 1.f, 0.f, 1.f };
		this->m_colors.m_trackTextColor = { 1.f, 1.f, 1.f, 1.f };
		this->m_colors.m_cursorColor = { 0.f, 0.f, 0.f, 1.f };
	}

	this->m_colors.m_trackColor = { (float)reader.GetReal("Track", "r", 0.33f), (float)reader.GetReal("Track", "g", 0.33f), (float)reader.GetReal("Track", "b", 0.33f), (float)reader.GetReal("Track", "a", 1.f) };
	this->m_colors.m_trackColorInactive = { (float)reader.GetReal("TrackInactive", "r", 0.33f), (float)reader.GetReal("TrackInactive", "g", 0.33f), (float)reader.GetReal("TrackInactive", "b", 0.33f), (float)reader.GetReal("TrackInactive", "a", 1.f) };
	this->m_colors.m_trackColorActive = { (float)reader.GetReal("TrackActive", "r", 0.f), (float)reader.GetReal("TrackActive", "g", 0.4f), (float)reader.GetReal("TrackActive", "b", 0.8f), (float)reader.GetReal("TrackActive", "a", 1.f) };
	this->m_colors.m_trackBoundingBox = { (float)reader.GetReal("TrackBoundingBox", "r", 0.f), (float)reader.GetReal("TrackBoundingBox", "g", 0.f), (float)reader.GetReal("TrackBoundingBox", "b", 0.f), (float)reader.GetReal("TrackBoundingBox", "a", 1.f) };
	this->m_colors.m_trackBoundingBoxActive = { (float)reader.GetReal("TrackActiveBoundingBox", "r", 1.f), (float)reader.GetReal("TrackActiveBoundingBox", "g", 1.f), (float)reader.GetReal("TrackActiveBoundingBox", "b", 0.f), (float)reader.GetReal("TrackActiveBoundingBox", "a", 1.f) };
	this->m_colors.m_trackTextColor = { (float)reader.GetReal("TrackText", "r", 1.f), (float)reader.GetReal("TrackText", "g", 1.f), (float)reader.GetReal("TrackText", "b", 1.f), (float)reader.GetReal("TrackText", "a", 1.f) };
	this->m_colors.m_cursorColor = { (float)reader.GetReal("TrackCursor", "r", 1.f), (float)reader.GetReal("TrackCursor", "g", 1.f), (float)reader.GetReal("TrackCursor", "b", 1.f), (float)reader.GetReal("TrackCursor", "a", 1.f) };
}

std::string TimeActEditor::GetTrackName(int idx) 
{ 
	return g_taeTemplate.GetGroupName(this->m_tracks[idx].m_eventGroup);
}

std::string TimeActEditor::GetEventLabel(int idx, int event_idx) const
{
	return g_taeTemplate.GetEventName(this->m_tracks[idx].m_eventGroup, this->m_tracks[idx].m_event[event_idx].m_value) + this->m_tracks[idx].m_event[event_idx].m_args->GetArgumentsAsString();
}

void TimeActEditor::AddGroup(int id)
{
	this->m_source->m_taeData->m_eventGroupCount++;
	this->m_source->m_taeData->m_groups.push_back(EventGroup(id));

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added group ID %d\n", id);
	this->ReloadTracks();
}

void TimeActEditor::DeleteGroup(int idx)
{
	for (size_t i = 0; i < this->m_source->m_taeData->m_groups[idx].m_count; i++)
		this->DeleteEvent(idx, i);

	this->m_source->m_taeData->m_eventGroupCount--;
	this->m_source->m_taeData->m_groups.erase(this->m_source->m_taeData->m_groups.begin() + idx);

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Removed group %d\n", idx);

	this->ReloadTracks();
}

void TimeActEditor::AddEvent(int group_idx, TimeActEvent event)
{
	this->m_source->m_taeData->m_eventCount++;

	this->m_source->m_taeData->m_events.push_back(event);

	this->m_source->m_taeData->m_groups[group_idx].m_count++;

	this->m_source->m_taeData->m_groups[group_idx].m_eventOffset.push_back(0);
	this->m_source->m_taeData->m_groups[group_idx].m_eventIndex.push_back(this->m_source->m_taeData->m_events.size() - 1);

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added event (%.3f, %.3f, %d)\n", event.m_start, event.m_end, event.m_eventData->m_id);

	this->ReloadTracks();
}

void TimeActEditor::DeleteEvent(int group_idx, int event_idx)
{
	this->m_source->m_taeData->m_groups[group_idx].m_count--;

	int delete_index = this->m_source->m_taeData->m_groups[group_idx].m_eventIndex[event_idx];

	this->m_source->m_taeData->m_groups[group_idx].m_eventOffset.erase(this->m_source->m_taeData->m_groups[group_idx].m_eventOffset.begin() + event_idx);
	this->m_source->m_taeData->m_groups[group_idx].m_eventIndex.erase(this->m_source->m_taeData->m_groups[group_idx].m_eventIndex.begin() + event_idx);

	this->m_source->m_taeData->m_eventCount--;

	this->m_source->m_taeData->m_events.erase(this->m_source->m_taeData->m_events.begin() + delete_index);

	for (size_t i = 0; i < this->m_source->m_taeData->m_groups.size(); i++)
	{
		for (size_t j = 0; j < this->m_source->m_taeData->m_groups[i].m_eventIndex.size(); j++)
		{
			if (this->m_source->m_taeData->m_groups[i].m_eventIndex[j] >= delete_index)
				this->m_source->m_taeData->m_groups[i].m_eventIndex[j] -= 1;
		}
	}

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d (group=%d)\n", event_idx, group_idx);

	if (this->m_source->m_taeData->m_groups[group_idx].m_count < 1)
		this->DeleteGroup(group_idx);

	this->ReloadTracks();
}

void TimeActEditor::ReloadTracks()
{
	this->m_tracks.clear();

	for (size_t i = 0; i < this->m_source->m_taeData->m_eventGroupCount; i++)
	{
		this->m_source->m_taeData->m_groups[i].m_event.clear();

		for (size_t j = 0; j < this->m_source->m_taeData->m_groups[i].m_count; j++)
			this->m_source->m_taeData->m_groups[i].m_event.push_back(&this->m_source->m_taeData->m_events[this->m_source->m_taeData->m_groups[i].m_eventIndex[j]]);
	}

	if (this->m_source->m_taeData->m_eventGroupCount > 0)
	{
		for (int j = 0; j < this->m_source->m_taeData->m_eventGroupCount; j++)
			this->m_tracks.push_back(&this->m_source->m_taeData->m_groups[j]);
	}
}

void TimeActEditor::Clear()
{
	this->m_source = nullptr;
	this->m_tracks.clear();
}