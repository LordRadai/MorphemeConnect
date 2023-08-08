#include "Timeline.h"
#include "../Application/Application.h"

const char* trackNames[50];

void EventTrackEditor::AddTimeActTrack(int id, TimeActTrack* time_act_track, float mult)
{
	myItems.push_back(EventTrack{ id, time_act_track->group_id, MathHelper::TimeToFrame(time_act_track->startTime * mult), MathHelper::TimeToFrame((time_act_track->endTime) * mult), time_act_track->tae_id, time_act_track->tae_count, time_act_track->trackName, false, false, NULL, time_act_track });
}

void EventTrackEditor::AddMorphemeEventTrack(int id, MorphemeEventTrack* event_track, float mult)
{ 
	if (event_track->is_discrete)
		this->myItems.push_back(EventTrack{ id, event_track->eventId, MathHelper::TimeToFrame(event_track->startTime * mult), MathHelper::TimeToFrame((event_track->startTime) * mult), event_track->value, event_track->eventCount, event_track->trackName, event_track->is_discrete, false, event_track, NULL });
	else
		this->myItems.push_back(EventTrack{ id, event_track->eventId, MathHelper::TimeToFrame(event_track->startTime * mult), MathHelper::TimeToFrame((event_track->startTime + event_track->duration) * mult), event_track->value, event_track->eventCount, event_track->trackName, event_track->is_discrete, false, event_track, NULL });
}

void EventTrackEditor::Clear()
{
	myItems.clear();
}

void EventTrackEditor::LoadTrackName(int id, MorphemeEventTrack event_track)
{
	trackNames[id] = event_track.trackName;
}

void EventTrackEditor::EventTrack::SaveEventTrackData(MorphemeEventTrack* event_track, float mult)
{
	event_track->eventCount = eventCount;
	event_track->eventId = eventId;
	event_track->value = value;
	event_track->startTime = MathHelper::FrameToTime(mFrameStart) / mult;

	if (event_track->is_discrete == false)
		event_track->duration = MathHelper::FrameToTime((mFrameEnd - mFrameStart)) / mult;
}

void EventTrackEditor::EventTrack::SaveTaeTrackData(TimeActTrack* tae_track, float mult)
{
	tae_track->tae_count = eventCount;
	tae_track->group_id = eventId;
	tae_track->tae_id = value;
	tae_track->startTime = MathHelper::FrameToTime(mFrameStart) / mult;
	tae_track->endTime = MathHelper::FrameToTime(mFrameEnd) / mult;
}

MorphemeEventTrackList::MorphemeEventTrackList(NodeDataContent_EventTrack* src)
{
	if (!src)
	{
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Event track source is NULL\n");
		return;
	}

	int track_count = 0;
	int index_subBlend = 0;
	int index_subGeneric = 0;
	int index_subUnk = 0;

	if (src->m_eventTracks[0].m_trackCount > 0)
	{
		track_count = src->m_eventTracks[0].m_trackCount;

		this->parent = src;
		this->count_discrete = track_count;
		this->tracks_discrete = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[0].m_trackSignatures[i]);

			this->tracks_discrete[i].parentId = -1;
			this->tracks_discrete[i].childId = -1;
			this->tracks_discrete[i].eventCount = bundle_event_track->m_data->m_numEvents;
			this->tracks_discrete[i].eventId = bundle_event_track->m_data->m_eventId;

			this->tracks_discrete[i].trackName = bundle_event_track->m_data->m_trackName;

			this->tracks_discrete[i].startTime = bundle_event_track->m_data->m_trackData[0].m_start;
			this->tracks_discrete[i].duration = bundle_event_track->m_data->m_trackData[0].m_duration;
			this->tracks_discrete[i].value = bundle_event_track->m_data->m_trackData[0].m_userData;
			this->tracks_discrete[i].is_discrete = true;
		}

		this->count_discreteSub = this->GetSubTrackcount_discrete();
		this->tracks_discreteSub = new MorphemeEventTrack[this->count_discreteSub];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[0].m_trackSignatures[i]);

			for (size_t j = 1; j < this->tracks_discrete[i].eventCount; j++)
			{
				if (index_subBlend < this->count_discreteSub)
				{
					this->tracks_discreteSub[index_subBlend].parentId = i;
					this->tracks_discreteSub[index_subBlend].childId = j;
					this->tracks_discreteSub[index_subBlend].eventCount = 1;
					this->tracks_discreteSub[index_subBlend].eventId = this->tracks_discrete[i].eventId;
					this->tracks_discreteSub[index_subBlend].trackName = this->tracks_discrete[i].trackName;

					this->tracks_discreteSub[index_subBlend].startTime = bundle_event_track->m_data->m_trackData[j].m_start;
					this->tracks_discreteSub[index_subBlend].duration = bundle_event_track->m_data->m_trackData[j].m_duration;
					this->tracks_discreteSub[index_subBlend].value = bundle_event_track->m_data->m_trackData[j].m_userData;
					this->tracks_discreteSub[index_subBlend].is_discrete = true;
					index_subBlend++;
				}
			}
		}
	}

	if (src->m_eventTracks[1].m_trackCount > 0)
	{
		Debug::DebuggerMessage(Debug::LVL_INFO, "Track node data has tracks of an unknown type\n");

		track_count = src->m_eventTracks[1].m_trackCount;

		this->parent = src;
		this->count_unk = track_count;
		this->tracks_unk = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[1].m_trackSignatures[i]);

			this->tracks_unk[i].parentId = -1;
			this->tracks_unk[i].childId = -1;
			this->tracks_unk[i].eventCount = bundle_event_track->m_data->m_numEvents;
			this->tracks_unk[i].eventId = bundle_event_track->m_data->m_eventId;

			this->tracks_unk[i].trackName = bundle_event_track->m_data->m_trackName;

			this->tracks_unk[i].startTime = bundle_event_track->m_data->m_trackData[0].m_start;
			this->tracks_unk[i].duration = bundle_event_track->m_data->m_trackData[0].m_duration;
			this->tracks_unk[i].value = bundle_event_track->m_data->m_trackData[0].m_userData;
			this->tracks_unk[i].is_discrete = false;
		}

		this->count_unkSub = this->GetSubTrackcount_unk();
		this->tracks_unkSub = new MorphemeEventTrack[this->count_timedSub];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[1].m_trackSignatures[i]);

			for (size_t j = 1; j < this->tracks_unk[i].eventCount; j++)
			{
				if (index_subUnk < this->count_unkSub)
				{
					this->tracks_unkSub[index_subUnk].parentId = i;
					this->tracks_unkSub[index_subUnk].childId = j;
					this->tracks_unkSub[index_subUnk].eventCount = 1;
					this->tracks_unkSub[index_subUnk].eventId = this->tracks_timed[i].eventId;

					this->tracks_unkSub[index_subUnk].trackName = this->tracks_timed[i].trackName;

					this->tracks_unkSub[index_subUnk].startTime = bundle_event_track->m_data->m_trackData[j].m_start;
					this->tracks_unkSub[index_subUnk].duration = bundle_event_track->m_data->m_trackData[j].m_duration;
					this->tracks_unkSub[index_subUnk].value = bundle_event_track->m_data->m_trackData[j].m_userData;
					this->tracks_unkSub[index_subUnk].is_discrete = false;
					index_subUnk++;
				}
			}
		}
	}

	if (src->m_eventTracks[2].m_trackCount > 0)
	{
		track_count = src->m_eventTracks[2].m_trackCount;

		this->parent = src;
		this->count_timed = track_count;
		this->tracks_timed = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[2].m_trackSignatures[i]);

			this->tracks_timed[i].parentId = -1;
			this->tracks_timed[i].childId = -1;
			this->tracks_timed[i].eventCount = bundle_event_track->m_data->m_numEvents;
			this->tracks_timed[i].eventId = bundle_event_track->m_data->m_eventId;

			this->tracks_timed[i].trackName = bundle_event_track->m_data->m_trackName;

			this->tracks_timed[i].startTime = bundle_event_track->m_data->m_trackData[0].m_start;
			this->tracks_timed[i].duration = bundle_event_track->m_data->m_trackData[0].m_duration;
			this->tracks_timed[i].value = bundle_event_track->m_data->m_trackData[0].m_userData;
			this->tracks_timed[i].is_discrete = false;
		}

		this->count_timedSub = this->GetSubTrackcount();
		this->tracks_timedSub = new MorphemeEventTrack[this->count_timedSub];

		for (int i = 0; i < track_count; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(src->m_eventTracks[2].m_trackSignatures[i]);

			for (size_t j = 1; j < this->tracks_timed[i].eventCount; j++)
			{
				if (index_subGeneric < this->count_timedSub)
				{
					this->tracks_timedSub[index_subGeneric].parentId = i;
					this->tracks_timedSub[index_subGeneric].childId = j;
					this->tracks_timedSub[index_subGeneric].eventCount = 1;
					this->tracks_timedSub[index_subGeneric].eventId = this->tracks_timed[i].eventId;

					this->tracks_timedSub[index_subGeneric].trackName = this->tracks_timed[i].trackName;

					this->tracks_timedSub[index_subGeneric].startTime = bundle_event_track->m_data->m_trackData[j].m_start;
					this->tracks_timedSub[index_subGeneric].duration = bundle_event_track->m_data->m_trackData[j].m_duration;
					this->tracks_timedSub[index_subGeneric].value = bundle_event_track->m_data->m_trackData[j].m_userData;
					this->tracks_timedSub[index_subGeneric].is_discrete = false;
					index_subGeneric++;
				}
			}
		}
	}
}

void MorphemeEventTrackList::ClearTrackList()
{
	if (this->count_discrete != 0)
	{
		delete[] this->tracks_discrete;
		delete[] this->tracks_discreteSub;
	}

	if (this->count_timed != 0)
	{
		delete[] this->tracks_timed;
		delete[] this->tracks_timedSub;
	}

	this->parent = NULL;
	this->count_discrete = 0;
	this->count_timed = 0;

}

void MorphemeEventTrackList::SaveEventTracks()
{
	NodeDataContent_EventTrack* track_base;
	uint64_t track_data;
	uint64_t* list;
	int index_subBlend = 0;
	int index_subGeneric = 0;

	if (this->parent == NULL)
	{
		Debug::Alert(MB_ICONERROR, "Timeline.cpp", "EventTrack save task failed. Output is nullptr");
		return;
	}

	track_base = this->parent;

	if (this->count_discrete > 0)
	{
		Debug::DebuggerMessage(Debug::LVL_DEBUG, "Saving Discrete Event Tracks\n");

		for (int i = 0; i < this->count_discrete; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(track_base->m_eventTracks[0].m_trackSignatures[i]);

			Debug::DebuggerMessage(Debug::LVL_DEBUG, "%s:\n", bundle_event_track->m_data->m_trackName);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tnumEvents: %d -> %d\n", bundle_event_track->m_data->m_numEvents, this->tracks_discrete[i].eventCount);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\teventId: %d -> %d\n", bundle_event_track->m_data->m_eventId, this->tracks_discrete[i].eventId);

			bundle_event_track->m_data->m_numEvents = this->tracks_discrete[i].eventCount;
			bundle_event_track->m_data->m_eventId = this->tracks_discrete[i].eventId;

			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[0]: %.3f -> %.3f\n", bundle_event_track->m_data->m_trackData[0].m_start, this->tracks_discrete[i].startTime);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[0]: %.3f -> %.3f\n", bundle_event_track->m_data->m_trackData[0].m_duration, this->tracks_discrete[i].duration);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[0]: %d -> %d\n", bundle_event_track->m_data->m_trackData[0].m_userData, this->tracks_discrete[i].value);

			bundle_event_track->m_data->m_trackData[0].m_start = this->tracks_discrete[i].startTime;
			bundle_event_track->m_data->m_trackData[0].m_duration = this->tracks_discrete[i].duration;
			bundle_event_track->m_data->m_trackData[0].m_userData = this->tracks_discrete[i].value;

			for (size_t j = 1; j < this->tracks_discrete[i].eventCount; j++)
			{
				if (index_subBlend < this->count_discreteSub)
				{
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[%d]: %.3f -> %.3f\n", j, bundle_event_track->m_data->m_trackData[j].m_start, this->tracks_discreteSub[index_subBlend].startTime);
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[%d]: %.3f -> %.3f\n", j, bundle_event_track->m_data->m_trackData[j].m_duration, this->tracks_discreteSub[index_subBlend].duration);
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[%d]: %d -> %d\n", j, bundle_event_track->m_data->m_trackData[j].m_userData, this->tracks_discreteSub[index_subBlend].value);

					bundle_event_track->m_data->m_trackData[j].m_start = this->tracks_discreteSub[index_subBlend].startTime;
					bundle_event_track->m_data->m_trackData[j].m_duration = this->tracks_discreteSub[index_subBlend].duration;
					bundle_event_track->m_data->m_trackData[j].m_userData = this->tracks_discreteSub[index_subBlend].value;
					index_subBlend++;
				}
			}
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\n");
		}
	}

	if (this->count_timed > 0)
	{
		Debug::DebuggerMessage(Debug::LVL_DEBUG, "Saving Timed Event Tracks\n");

		for (int i = 0; i < this->count_timed; i++)
		{
			MorphemeBundle_EventTrack* bundle_event_track = morpheme_connect.nmb.GetEventTrackBundle(track_base->m_eventTracks[2].m_trackSignatures[i]);

			Debug::DebuggerMessage(Debug::LVL_DEBUG, "%s:\n", bundle_event_track->m_data->m_trackName);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tnumEvents: %d -> %d\n", bundle_event_track->m_data->m_numEvents, this->tracks_timed[i].eventCount);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\teventId: %d -> %d\n", bundle_event_track->m_data->m_eventId, this->tracks_timed[i].eventId);

			bundle_event_track->m_data->m_numEvents = this->tracks_timed[i].eventCount;
			bundle_event_track->m_data->m_eventId = this->tracks_timed[i].eventId;

			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[0]: %.3f -> %.3f\n", bundle_event_track->m_data->m_trackData[0].m_start, this->tracks_timed[i].startTime);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[0]: %.3f -> %.3f\n", bundle_event_track->m_data->m_trackData[0].m_duration, this->tracks_timed[i].duration);
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[0]: %d -> %d\n", bundle_event_track->m_data->m_trackData[0].m_userData, this->tracks_timed[i].value);

			bundle_event_track->m_data->m_trackData[0].m_start = this->tracks_timed[i].startTime;
			bundle_event_track->m_data->m_trackData[0].m_duration = this->tracks_timed[i].duration;
			bundle_event_track->m_data->m_trackData[0].m_userData = this->tracks_timed[i].value;

			for (size_t j = 1; j < this->tracks_timed[i].eventCount; j++)
			{
				if (index_subGeneric < this->count_timedSub)
				{
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[%d]: %.3f -> %.3f\n", j, bundle_event_track->m_data->m_trackData[j].m_start, this->tracks_timedSub[index_subBlend].startTime);
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[%d]: %.3f -> %.3f\n", j, bundle_event_track->m_data->m_trackData[j].m_duration, this->tracks_timedSub[index_subBlend].duration);
					Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[%d]: %d -> %d\n", j, bundle_event_track->m_data->m_trackData[j].m_userData, this->tracks_timedSub[index_subBlend].value);

					bundle_event_track->m_data->m_trackData[j].m_start = this->tracks_timedSub[index_subGeneric].startTime;
					bundle_event_track->m_data->m_trackData[j].m_duration = this->tracks_timedSub[index_subGeneric].duration;
					bundle_event_track->m_data->m_trackData[j].m_userData = this->tracks_timedSub[index_subGeneric].value;
					index_subGeneric++;
				}
			}
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\n");
		}
	}
}

int MorphemeEventTrackList::GetSubTrackcount_discrete()
{
	int result = 0;

	for (size_t i = 0; i < count_discrete; i++)
		result += (tracks_discrete[i].eventCount - 1);

	return result;
}

int MorphemeEventTrackList::GetSubTrackcount()
{
	int result = 0;

	for (size_t i = 0; i < count_timed; i++)
		result += (tracks_timed[i].eventCount - 1);

	return result;
}

int MorphemeEventTrackList::GetSubTrackcount_unk()
{
	int result = 0;

	for (size_t i = 0; i < count_unk; i++)
		result += (tracks_unk[i].eventCount - 1);

	return result;
}

int TimeActTrackList::getSubTrackcount()
{
	int result = 0;

	for (size_t i = 0; i < count; i++)
		result += (tracks[i].tae_count - 1);

	return result;
}

void MorphemeEventTrackList::AllocSubTracks()
{
	count_discreteSub = GetSubTrackcount_discrete();
	tracks_discreteSub = new MorphemeEventTrack[count_discreteSub];

	count_timedSub = GetSubTrackcount();
	tracks_timedSub = new MorphemeEventTrack[count_timedSub];
}
