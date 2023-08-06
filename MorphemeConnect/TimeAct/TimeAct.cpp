#include <sstream>
#include "Debug.h"
#include "inih/ini.h"
#include "inih/INIReader.h"
#include "TimeAct.h"

uint64_t TimeAct::getTimeActFile_pl(uint64_t character_ctrl)
{
	if (character_ctrl == NULL)
		return NULL;

	if (*(uint64_t*)(character_ctrl + 0x58))
	{
		uint64_t chr_res = *(uint64_t*)(character_ctrl + 0x58);

		return *(uint64_t*)(chr_res + 0x48);
	}

	return NULL;
}

uint64_t TimeAct::getTimeActFile_sfx(uint64_t character_ctrl)
{
	if (character_ctrl == NULL)
		return NULL;

	if (character_ctrl == NULL)
		return NULL;

	if (*(uint64_t*)(character_ctrl + 0x58))
	{
		uint64_t chr_res = *(uint64_t*)(character_ctrl + 0x58);

		return *(uint64_t*)(chr_res + 0x50);
	}

	return NULL;
}

uint64_t TimeAct::getTimeActFile_snd(uint64_t character_ctrl)
{
	if (character_ctrl == NULL)
		return NULL;

	if (*(uint64_t*)(character_ctrl + 0x58))
	{
		uint64_t chr_res = *(uint64_t*)(character_ctrl + 0x58);

		return *(uint64_t*)(chr_res + 0x58);
	}

	return NULL;
}

sEventGroup* TimeAct::getEventGroup(sTaeData* tae_data, int index)
{
	return &tae_data->event_group[index];
}

int TimeAct::loadTimeActTrack(sTaeData* tae_data, TimeActTrackList* tae_list)
{
	if (tae_data == NULL)
		return -1;

	int track_count = tae_data->event_group_count;

	tae_list->parent = (uint64_t)tae_data;
	tae_list->count = track_count;
	tae_list->tracks = new TimeActTrack[track_count];

	for (size_t i = 0; i < track_count; i++)
	{
		getTaeEventName(tae_list->tracks[i].trackName, *tae_data->event_group[i].group_id, tae_data->event_group[i].tae_data[0]->event_data->value);

		sEventGroup* event_group = getEventGroup(tae_data, i);

		tae_list->tracks[i].tae_count = tae_data->event_group[i].group_count;
		tae_list->tracks[i].group_id = *tae_data->event_group[i].group_id;
		tae_list->tracks[i].startTime = tae_data->event_group[i].tae_data[0]->start_time;
		tae_list->tracks[i].endTime = tae_data->event_group[i].tae_data[0]->end_time;
		tae_list->tracks[i].tae_id = tae_data->event_group[i].tae_data[0]->event_data->value;
		tae_list->tracks[i].args = tae_data->event_group[i].tae_data[0]->event_data->args;
		tae_list->tracks[i].tae_def = getTimeActDef(tae_list->tracks[i].group_id, tae_list->tracks[i].tae_id);

		tae_list->tracks[i].parentId = -1;
		tae_list->tracks[i].childId = -1;
	}

	tae_list->countSub = tae_list->getSubTrackcount();
	tae_list->tracksSub = new TimeActTrack[tae_list->countSub];

	int indexSub = 0;
	for (int i = 0; i < track_count; i++)
	{
		for (size_t j = 1; j < tae_list->tracks[i].tae_count; j++)
		{
			if (indexSub < tae_list->countSub)
			{
				getTaeEventName(tae_list->tracksSub[indexSub].trackName, *tae_data->event_group[i].group_id, tae_data->event_group[i].tae_data[j]->event_data->value);

				tae_list->tracksSub[indexSub].parentId = i;
				tae_list->tracksSub[indexSub].childId = j;
				tae_list->tracksSub[indexSub].tae_count = 1;

				tae_list->tracksSub[indexSub].group_id = *tae_data->event_group[i].group_id;
				tae_list->tracksSub[indexSub].startTime = tae_data->event_group[i].tae_data[j]->start_time;
				tae_list->tracksSub[indexSub].endTime = tae_data->event_group[i].tae_data[j]->end_time;
				tae_list->tracksSub[indexSub].tae_id = tae_data->event_group[i].tae_data[j]->event_data->value;
				tae_list->tracksSub[indexSub].args = tae_data->event_group[i].tae_data[j]->event_data->args;
				tae_list->tracksSub[indexSub].tae_def = getTimeActDef(tae_list->tracksSub[indexSub].group_id, tae_list->tracksSub[indexSub].tae_id);
				indexSub++;
			}
		}
	}

	return track_count;
}

void TimeAct::clearTrackList(TimeActTrackList* track_list)
{
	track_list->parent = 0;
	track_list->count = 0;
	track_list->countSub = 0;
	delete[] track_list->tracks;
	delete[] track_list->tracksSub;
}

void TimeAct::saveTimeActTrack(TimeActTrackList* tae_list)
{
	sTaeData* track_base;
	int index_sub = 0;

	if (!tae_list)
	{
		MessageBoxA(NULL, "TimeAct save task failed. Input is nullptr", "MorphemeNetworkInspector", MB_ICONERROR);
		return;
	}

	if (tae_list->parent)
	{
		track_base = (sTaeData*)tae_list->parent;
		Debug::debuggerMessage(Debug::LVL_DEBUG, "Saving TimeAct tracks\n");

		if (tae_list->count > 0)
		{
			for (int i = 0; i < tae_list->count; i++)
			{
				Debug::debuggerMessage(Debug::LVL_DEBUG, "%s:\n", tae_list->tracks[i].trackName);
				Debug::debuggerMessage(Debug::LVL_DEBUG, "\tgroupCount: %d -> %d\n", track_base->event_group[i].group_count, tae_list->tracks[i].tae_count);
				Debug::debuggerMessage(Debug::LVL_DEBUG, "\tgroupID: %d -> %d\n", *track_base->event_group[i].group_id, tae_list->tracks[i].group_id);
				
				track_base->event_group[i].group_count = tae_list->tracks[i].tae_count;
				*track_base->event_group[i].group_id = tae_list->tracks[i].group_id;

				Debug::debuggerMessage(Debug::LVL_DEBUG, "\tstartTime[0]: %.3f -> %.3f\n", track_base->event_group[i].tae_data[0]->start_time, tae_list->tracks[i].startTime);
				Debug::debuggerMessage(Debug::LVL_DEBUG, "\tendTime[0]: %.3f -> %.3f\n", track_base->event_group[i].tae_data[0]->end_time, tae_list->tracks[i].endTime);
				Debug::debuggerMessage(Debug::LVL_DEBUG, "\tvalue[0]: %d -> %d\n", track_base->event_group[i].tae_data[0]->event_data->value, tae_list->tracks[i].tae_id);

				track_base->event_group[i].tae_data[0]->start_time = tae_list->tracks[i].startTime;
				track_base->event_group[i].tae_data[0]->end_time = tae_list->tracks[i].endTime;
				track_base->event_group[i].tae_data[0]->event_data->value = tae_list->tracks[i].tae_id;

				for (size_t j = 1; j < tae_list->tracks[i].tae_count; j++)
				{
					if (index_sub < tae_list->countSub)
					{
						Debug::debuggerMessage(Debug::LVL_DEBUG, "\tstartTime[%d]: %.3f -> %.3f\n", j, track_base->event_group[i].tae_data[j]->start_time, tae_list->tracksSub[index_sub].startTime);
						Debug::debuggerMessage(Debug::LVL_DEBUG, "\tendTime[%d]: %.3f -> %.3f\n", j, track_base->event_group[i].tae_data[j]->end_time, tae_list->tracksSub[index_sub].endTime);
						Debug::debuggerMessage(Debug::LVL_DEBUG, "\tvalue[%d]: %d -> %d\n", j, track_base->event_group[i].tae_data[j]->event_data->value, tae_list->tracksSub[index_sub].tae_id);

						track_base->event_group[i].tae_data[j]->start_time = tae_list->tracksSub[index_sub].startTime;
						track_base->event_group[i].tae_data[j]->end_time = tae_list->tracksSub[index_sub].endTime;
						track_base->event_group[i].tae_data[j]->event_data->value = tae_list->tracksSub[index_sub].tae_id;
						index_sub++;
					}
				}
				Debug::debuggerMessage(Debug::LVL_DEBUG, "\n");
			}
		}
	}
}

const char* TimeAct::getGroupName(int group_id)
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
		return "";
	}
}

void TimeAct::getTaeEventName(char buf[], int group_id, int tae_id)
{
	INIReader reader(".//MorphemeNetworkInspector//res//tae_def.ini");

	if (reader.ParseError() < 0) {
		printf_s("[ERROR] Failed to load tae_def.ini\n");
		return;
	}

	char def[36];
	char group_str[10];
	char tae_id_str[10];

	sprintf(def, "%s_%d", getGroupName(group_id), tae_id);
	//sprintf(group_str, "%d", group_id);
	sprintf(tae_id_str, "%d", tae_id);

	sprintf(buf, "%s", reader.GetString(tae_id_str, "tae_name", def).c_str());
}

TimeActDef TimeAct::getTimeActDef(int group_id, int tae_id)
{
	TimeActDef tae_def;

	INIReader tae_template(".//MorphemeNetworkInspector//res//tae_def.ini");

	if (tae_template.ParseError() < 0) {
		printf_s("[ERROR] Failed to load tae_def.ini\n");
		return tae_def;
	}

	char def[36];
	char tae_id_str[10];
	std::string tae_args, tae_args_names;

	sprintf(def, "%s_%d", getGroupName(group_id), tae_id);
	sprintf(tae_id_str, "%d", tae_id);

	tae_def.group_id = tae_template.GetInteger(tae_id_str, "group_id", 0);
	tae_def.group_name = getGroupName(group_id);
	tae_def.tae_id = tae_id;
	sprintf(tae_def.tae_name, "%s", tae_template.GetString(tae_id_str, "tae_name", def).c_str());
	tae_def.arg_count = tae_template.GetInteger(tae_id_str, "arg_count", 0);
	
	if (tae_def.arg_count > 8)
	{
		MessageBoxA(NULL, "Invalid TAE template. Argument count must not exceed 8", "MorphemeNetworkInspector", MB_ICONERROR);
		tae_def.arg_count = 0;
	}

	tae_args = tae_template.GetString(tae_id_str, "args_type", "");

	if (tae_args != "")
	{
		int count = 0;

		std::size_t start_pos = tae_args.find("{");
		while (start_pos != std::string::npos)
		{
			std::size_t end_pos = tae_args.find("}", start_pos);
			if (end_pos == std::string::npos)
				break;

			std::string value_str = tae_args.substr(start_pos + 1, end_pos - start_pos - 1);
			tae_def.arg_type.push_back(std::stoi(value_str));
			start_pos = tae_args.find("{", end_pos);
			count++;
		}
	}

	tae_args_names = tae_template.GetString(tae_id_str, "args_name", "");

	if (tae_args_names != "")
	{
		std::size_t start_pos = tae_args_names.find("{");
		while (start_pos != std::string::npos)
		{
			std::size_t end_pos = tae_args_names.find("}", start_pos);
			if (end_pos == std::string::npos)
			{
				// Invalid input string
				break;
			}
			std::string value_str = tae_args_names.substr(start_pos + 1, end_pos - start_pos - 1);
			
			TimeActDef::ArgName name;

			strcpy(name.name, value_str.c_str());

			tae_def.arg_names.push_back(name);
			start_pos = tae_args_names.find("{", end_pos);
		}
	}

	return tae_def;
}

int TimeAct::getTaeArgCount(int tae_id)
{
	
}

