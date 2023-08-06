#include "Timeline.h"

const char* trackNames[50];

void EventTrackEditor::AddTimeActTrack(int id, TimeActTrack* time_act_track, float multiplier)
{
	myItems.push_back(EventTrack{ id, time_act_track->group_id, MathHelper::TimeToFrame(time_act_track->startTime * multiplier, 60), MathHelper::TimeToFrame((time_act_track->endTime) * multiplier, 60), time_act_track->tae_id, time_act_track->tae_count, time_act_track->trackName, false, false, NULL, time_act_track });
}

void EventTrackEditor::AddMorphemeEventTrack(int id, MorphemeEventTrack* event_track, float multiplier)
{ 
	if (event_track->is_discrete)
		this->myItems.push_back(EventTrack{ id, event_track->eventId, MathHelper::TimeToFrame(event_track->startTime * multiplier, 60), MathHelper::TimeToFrame((event_track->startTime) * multiplier, 60), event_track->value, event_track->eventCount, event_track->trackName, event_track->is_discrete, false, event_track, NULL });
	else
		this->myItems.push_back(EventTrack{ id, event_track->eventId, MathHelper::TimeToFrame(event_track->startTime * multiplier, 60), MathHelper::TimeToFrame((event_track->startTime + event_track->duration) * multiplier, 60), event_track->value, event_track->eventCount, event_track->trackName, event_track->is_discrete, false, event_track, NULL });
}

void EventTrackEditor::Clear()
{
	myItems.clear();
}

void EventTrackEditor::LoadTrackName(int id, MorphemeEventTrack event_track)
{
	trackNames[id] = event_track.trackName;
	//printf_s("%s\n", trackNames[id]);
}

void EventTrackEditor::EventTrack::SaveEventTrackData(MorphemeEventTrack* event_track, float multiplier)
{
	event_track->eventCount = eventCount;
	event_track->eventId = eventId;
	event_track->value = value;
	event_track->startTime = MathHelper::FrameToTime(mFrameStart, 60) / multiplier;

	if (event_track->is_discrete == false)
		event_track->duration = MathHelper::FrameToTime((mFrameEnd - mFrameStart), 60) / multiplier;	
}

void EventTrackEditor::EventTrack::SaveTaeTrackData(TimeActTrack* tae_track, float multiplier)
{
	tae_track->tae_count = eventCount;
	tae_track->group_id = eventId;
	tae_track->tae_id = value;
	tae_track->startTime = MathHelper::FrameToTime(mFrameStart, 60) / multiplier;
	tae_track->endTime = MathHelper::FrameToTime(mFrameEnd, 60) / multiplier;
}

int MorphemeEventTrackList::getSubTrackcount_discrete()
{
	int result = 0;

	for (size_t i = 0; i < count_discrete; i++)
		result += (tracks_discrete[i].eventCount - 1);

	return result;
}

int MorphemeEventTrackList::getSubTrackcount_timed()
{
	int result = 0;

	for (size_t i = 0; i < count_timed; i++)
		result += (tracks_timed[i].eventCount - 1);

	return result;
}

int MorphemeEventTrackList::getSubTrackcount_unk()
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

void MorphemeEventTrackList::allocSubTracks()
{
	count_discreteSub = getSubTrackcount_discrete();
	tracks_discreteSub = new MorphemeEventTrack[count_discreteSub];
	//printf_s("Allocated %d sub blend tracks\n", count_discreteSub);

	count_timedSub = getSubTrackcount_timed();
	tracks_timedSub = new MorphemeEventTrack[count_timedSub];
	//printf_s("Allocated %d sub generic tracks\n", count_timedSub);
}
