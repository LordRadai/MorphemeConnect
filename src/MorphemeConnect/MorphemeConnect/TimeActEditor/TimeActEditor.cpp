#include "TimeActEditor.h"
#include "../Application/Application.h"

TimeActEditor::TimeActTrack::TimeActTrack(int eventId, float start, float end)
{
	this->m_source = NULL;
	this->m_eventGroup = eventId;
	//this->m_event.m_frameStart = MathHelper::TimeToFrame(start);
	//this->m_event.m_duration = MathHelper::TimeToFrame(end - start);
}

TimeActEditor::TimeActTrack::TimeActTrack(EventGroup* src)
{
	this->m_source = src;

	this->m_eventGroup = src->m_groupData->m_eventType;
	this->m_count = src->m_count;

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

std::string getGroupName(int group_id)
{
	switch (group_id)
	{
	case 200:
		return "SoundCtrl";
	case 300:
		return "AiCtrl";
	case 1100:
		return "DamageCtrl";
	case 1150:
		return "BulletCtrl";
	case 1220:
		return "ParryCtrl";
	case 1500:
		return "CameraCtrl";
	case 2100:
		return "SfxCtrl";
	case 2200:
		return "FootEffectCtrl";
	case 2300:
		return "WeaponCtrl";
	case 2400:
		return "LockOnCtrl";
	case 101000:
		return "StaminaCtrl";
	case 110000:
		return "DamageActionCtrl";
	case 120000:
		return "AttackCtrl";
	case 210000:
		return "GimmickCtrl";
	case 220000:
		return "ItemCtrl";
	case 230000:
		return "ChrGenerateCtrl";
	case 240000:
		return "DeadCtrl";
	case 250000:
		return "ObjGenerateCtrl";
	case 260000:
		return "ModelCtrl";
	case 270000:
		return "ChrPartsCtrl";
	case 280000:
		return "ChrMoveCtrl";
	case 290000:
		return "ChrCollidCtrl";
	case 300000:
		return "EventCtrl";
	case 310000:
		return "SpEffectCtrl";
	default:
		return std::to_string(group_id);
	}
}

TimeActEditor::TimeActEditor() {}

std::string TimeActEditor::GetTrackName(int idx) 
{ 
	return getGroupName(this->m_tracks[idx].m_eventGroup);
}

std::string TimeActEditor::GetEventLabel(int idx, int event_idx) const
{
	INIReader reader(".//MorphemeConnect//res//tae.ini");

	if (reader.ParseError() < 0) {
		printf_s("[ERROR] Failed to load tae.ini\n");
		return "";
	}

	std::string default_str = std::string(getGroupName(this->m_tracks[idx].m_eventGroup)) + "_" + std::to_string(this->m_tracks[idx].m_event[event_idx].m_value);
	std::string tae_group_str = std::to_string(this->m_tracks[idx].m_eventGroup);
	std::string tae_id_str = std::to_string(this->m_tracks[idx].m_event[event_idx].m_value);

	return reader.GetString(tae_group_str, tae_id_str, default_str) + "[" + tae_id_str + "]" + this->m_tracks[idx].m_event[event_idx].m_args->GetArgumentAsString();
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

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d (group=%d)\n", event_idx, group_idx);

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
	else
		Debug::Alert(Debug::LVL_INFO, "TimeActEditor.cpp", "This TimeAct track has no events associated to it\n");
}

void TimeActEditor::Clear()
{
	this->m_tracks.clear();
}