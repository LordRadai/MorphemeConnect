#include "Morpheme.h"
#include "../Debug/Debug.h"

int Morpheme::LoadEventTracks(sEventTrackData* track_base, MorphemeEventTrackList* track_list)
{
	if (!track_base)
		return -1;

	int track_count = 0;
	int index_subBlend = 0;
	int index_subGeneric = 0;
	int index_subUnk = 0;

	if (track_base->m_eventTracks[0].m_trackCount > 0)
	{
		track_count = track_base->m_eventTracks[0].m_trackCount;

		track_list->parent = (uint64_t)track_base;
		track_list->count_discrete = track_count;
		track_list->tracks_discrete = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			track_list->tracks_discrete[i].parentId = -1;
			track_list->tracks_discrete[i].childId = -1;
			track_list->tracks_discrete[i].eventCount = track_base->m_eventTracks[0].m_tracks[i]->m_numEvents;
			track_list->tracks_discrete[i].eventId = track_base->m_eventTracks[0].m_tracks[i]->m_eventId;

			strcpy(track_list->tracks_discrete[i].trackName, track_base->m_eventTracks[0].m_tracks[i]->m_trackName);
			//track_list->tracks_discrete[i].trackName = track_base->m_eventTracks[0].m_tracks[i]->m_trackName;

			track_list->tracks_discrete[i].startTime = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_startTime;
			track_list->tracks_discrete[i].duration = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_duration;
			track_list->tracks_discrete[i].value = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_userData;
			track_list->tracks_discrete[i].is_discrete = true;
		}

		track_list->count_discreteSub = track_list->getSubTrackcount_discrete();
		track_list->tracks_discreteSub = new MorphemeEventTrack[track_list->count_discreteSub];

		for (int i = 0; i < track_count; i++)
		{
			for (size_t j = 1; j < track_list->tracks_discrete[i].eventCount; j++)
			{
				if (index_subBlend < track_list->count_discreteSub)
				{
					track_list->tracks_discreteSub[index_subBlend].parentId = i;
					track_list->tracks_discreteSub[index_subBlend].childId = j;
					track_list->tracks_discreteSub[index_subBlend].eventCount = 1;
					track_list->tracks_discreteSub[index_subBlend].eventId = track_list->tracks_discrete[i].eventId;
					strcpy(track_list->tracks_discreteSub[index_subBlend].trackName, track_base->m_eventTracks[0].m_tracks[i]->m_trackName);
					//track_list->tracks_discreteSub[index_subBlend].trackName = track_list->tracks_discrete[i].trackName;

					track_list->tracks_discreteSub[index_subBlend].startTime = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_startTime;
					track_list->tracks_discreteSub[index_subBlend].duration = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_duration;
					track_list->tracks_discreteSub[index_subBlend].value = track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_userData;
					track_list->tracks_discreteSub[index_subBlend].is_discrete = true;
					index_subBlend++;
				}
			}		
		}
	}

	if (track_base->m_eventTracks[1].m_trackCount > 0)
	{
		printf_s("[INFO, MorphemeSystem] This EventTrack has tracks of an unknown type\n");

		track_count = track_base->m_eventTracks[1].m_trackCount;

		track_list->parent = (uint64_t)track_base;
		track_list->count_unk = track_count;
		track_list->tracks_unk = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			track_list->tracks_unk[i].parentId = -1;
			track_list->tracks_unk[i].childId = -1;
			track_list->tracks_unk[i].eventCount = track_base->m_eventTracks[1].m_tracks[i]->m_numEvents;
			track_list->tracks_unk[i].eventId = track_base->m_eventTracks[1].m_tracks[i]->m_eventId;

			strcpy(track_list->tracks_unk[i].trackName, track_base->m_eventTracks[1].m_tracks[i]->m_trackName);
			//track_list->tracks_unk[i].trackName = track_base->m_eventTracks[1].m_tracks[i]->m_trackName;

			track_list->tracks_unk[i].startTime = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[0].m_startTime;
			track_list->tracks_unk[i].duration = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[0].m_duration;
			track_list->tracks_unk[i].value = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[0].m_userData;
			track_list->tracks_unk[i].is_discrete = false;
		}

		track_list->count_unkSub = track_list->getSubTrackcount_unk();
		track_list->tracks_unkSub = new MorphemeEventTrack[track_list->count_timedSub];

		for (int i = 0; i < track_count; i++)
		{
			for (size_t j = 1; j < track_list->tracks_unk[i].eventCount; j++)
			{
				if (index_subUnk < track_list->count_unkSub)
				{
					track_list->tracks_unkSub[index_subUnk].parentId = i;
					track_list->tracks_unkSub[index_subUnk].childId = j;
					track_list->tracks_unkSub[index_subUnk].eventCount = 1;
					track_list->tracks_unkSub[index_subUnk].eventId = track_list->tracks_timed[i].eventId;

					strcpy(track_list->tracks_unkSub[index_subUnk].trackName, track_list->tracks_timed[i].trackName);
					//track_list->tracks_unkSub[index_subUnk].trackName = track_list->tracks_timed[i].trackName;

					track_list->tracks_unkSub[index_subUnk].startTime = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[j].m_startTime;
					track_list->tracks_unkSub[index_subUnk].duration = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[j].m_duration;
					track_list->tracks_unkSub[index_subUnk].value = track_base->m_eventTracks[1].m_tracks[i]->m_trackData[j].m_userData;
					track_list->tracks_unkSub[index_subUnk].is_discrete = false;
					index_subUnk++;
				}
			}
		}
	}

	if (track_base->m_eventTracks[2].m_trackCount > 0)
	{
		track_count = track_base->m_eventTracks[2].m_trackCount;

		track_list->parent = (uint64_t)track_base;
		track_list->count_timed = track_count;
		track_list->tracks_timed = new MorphemeEventTrack[track_count];

		for (int i = 0; i < track_count; i++)
		{
			track_list->tracks_timed[i].parentId = -1;
			track_list->tracks_timed[i].childId = -1;
			track_list->tracks_timed[i].eventCount = track_base->m_eventTracks[2].m_tracks[i]->m_numEvents;
			track_list->tracks_timed[i].eventId = track_base->m_eventTracks[2].m_tracks[i]->m_eventId;

			strcpy(track_list->tracks_timed[i].trackName, track_base->m_eventTracks[2].m_tracks[i]->m_trackName);
			//track_list->tracks_timed[i].trackName = track_base->m_eventTracks[2].m_tracks[i]->m_trackName;

			track_list->tracks_timed[i].startTime = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_startTime;
			track_list->tracks_timed[i].duration = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_duration;
			track_list->tracks_timed[i].value = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_userData;
			track_list->tracks_timed[i].is_discrete = false;
		}

		track_list->count_timedSub = track_list->getSubTrackcount_timed();
		track_list->tracks_timedSub = new MorphemeEventTrack[track_list->count_timedSub];

		for (int i = 0; i < track_count; i++)
		{
			for (size_t j = 1; j < track_list->tracks_timed[i].eventCount; j++)
			{
				if (index_subGeneric < track_list->count_timedSub)
				{
					track_list->tracks_timedSub[index_subGeneric].parentId = i;
					track_list->tracks_timedSub[index_subGeneric].childId = j;
					track_list->tracks_timedSub[index_subGeneric].eventCount = 1;
					track_list->tracks_timedSub[index_subGeneric].eventId = track_list->tracks_timed[i].eventId;

					strcpy(track_list->tracks_timedSub[index_subGeneric].trackName, track_list->tracks_timed[i].trackName);
					//track_list->tracks_timedSub[index_subGeneric].trackName = track_list->tracks_timed[i].trackName;

					track_list->tracks_timedSub[index_subGeneric].startTime = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_startTime;
					track_list->tracks_timedSub[index_subGeneric].duration = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_duration;
					track_list->tracks_timedSub[index_subGeneric].value = track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_userData;
					track_list->tracks_timedSub[index_subGeneric].is_discrete = false;
					index_subGeneric++;
				}
			}
		}
	}

	return track_count;
}

void Morpheme::ClearTrackList(MorphemeEventTrackList* track_list)
{
	track_list->parent = 0;
	track_list->count_discrete = 0;
	track_list->count_timed = 0;
	delete[] track_list->tracks_discrete;
	delete[] track_list->tracks_timed;
	delete[] track_list->tracks_discreteSub;
	delete[] track_list->tracks_timedSub;
}

void Morpheme::SaveEventTracks(MorphemeEventTrackList* track_list)
{
	sEventTrackData* track_base;
	uint64_t track_data;
	uint64_t* list;
	int index_subBlend = 0;
	int index_subGeneric = 0;

	if (!track_list)
	{
		MessageBoxA(NULL, "EventTrack save task failed. Input is nullptr", "MorphemeNetworkInspector", MB_ICONERROR);
		return;
	}

	if (track_list->parent)
	{
		track_base = (sEventTrackData*)track_list->parent;

		if (track_list->count_discrete > 0)
		{
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "Saving Discrete Event Tracks\n");

			for (int i = 0; i < track_list->count_discrete; i++)
			{
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "%s:\n", track_base->m_eventTracks[0].m_tracks[i]->m_trackName);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tnumEvents: %d -> %d\n", track_base->m_eventTracks[0].m_tracks[i]->m_numEvents, track_list->tracks_discrete[i].eventCount);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\teventId: %d -> %d\n", track_base->m_eventTracks[0].m_tracks[i]->m_eventId, track_list->tracks_discrete[i].eventId);

				track_base->m_eventTracks[0].m_tracks[i]->m_numEvents = track_list->tracks_discrete[i].eventCount;
				track_base->m_eventTracks[0].m_tracks[i]->m_eventId = track_list->tracks_discrete[i].eventId;

				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[0]: %.3f -> %.3f\n", track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_startTime, track_list->tracks_discrete[i].startTime);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[0]: %.3f -> %.3f\n", track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_duration, track_list->tracks_discrete[i].duration);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[0]: %d -> %d\n", track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_userData, track_list->tracks_discrete[i].value);

				track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_startTime = track_list->tracks_discrete[i].startTime;
				track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_duration = track_list->tracks_discrete[i].duration;
				track_base->m_eventTracks[0].m_tracks[i]->m_trackData[0].m_userData = track_list->tracks_discrete[i].value;

				for (size_t j = 1; j < track_list->tracks_discrete[i].eventCount; j++)
				{
					if (index_subBlend < track_list->count_discreteSub)
					{
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[%d]: %.3f -> %.3f\n", j, track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_startTime, track_list->tracks_discreteSub[index_subBlend].startTime);
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[%d]: %.3f -> %.3f\n", j, track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_duration, track_list->tracks_discreteSub[index_subBlend].duration);
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[%d]: %d -> %d\n", j, track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_userData, track_list->tracks_discreteSub[index_subBlend].value);

						track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_startTime = track_list->tracks_discreteSub[index_subBlend].startTime;
						track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_duration = track_list->tracks_discreteSub[index_subBlend].duration;
						track_base->m_eventTracks[0].m_tracks[i]->m_trackData[j].m_userData = track_list->tracks_discreteSub[index_subBlend].value;
						index_subBlend++;
					}
				}
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\n");
			}
		}

		if (track_list->count_timed > 0)
		{	
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "Saving Timed Event Tracks\n");

			for (int i = 0; i < track_list->count_timed; i++)
			{
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "%s:\n", track_base->m_eventTracks[2].m_tracks[i]->m_trackName);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tnumEvents: %d -> %d\n", track_base->m_eventTracks[2].m_tracks[i]->m_numEvents, track_list->tracks_timed[i].eventCount);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\teventId: %d -> %d\n", track_base->m_eventTracks[2].m_tracks[i]->m_eventId, track_list->tracks_timed[i].eventId);

				track_base->m_eventTracks[2].m_tracks[i]->m_numEvents = track_list->tracks_timed[i].eventCount;
				track_base->m_eventTracks[2].m_tracks[i]->m_eventId = track_list->tracks_timed[i].eventId;

				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[0]: %.3f -> %.3f\n", track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_startTime, track_list->tracks_timed[i].startTime);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[0]: %.3f -> %.3f\n", track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_duration, track_list->tracks_timed[i].duration);
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[0]: %d -> %d\n", track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_userData, track_list->tracks_timed[i].value);

				track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_startTime = track_list->tracks_timed[i].startTime;
				track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_duration = track_list->tracks_timed[i].duration;
				track_base->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_userData = track_list->tracks_timed[i].value;

				for (size_t j = 1; j < track_list->tracks_timed[i].eventCount; j++)
				{
					if (index_subGeneric < track_list->count_timedSub)
					{
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tstartTime[%d]: %.3f -> %.3f\n", j, track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_startTime, track_list->tracks_timedSub[index_subBlend].startTime);
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tduration[%d]: %.3f -> %.3f\n", j, track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_duration, track_list->tracks_timedSub[index_subBlend].duration);
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "\tuserData[%d]: %d -> %d\n", j, track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_userData, track_list->tracks_timedSub[index_subBlend].value);

						track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_startTime = track_list->tracks_timedSub[index_subGeneric].startTime;
						track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_duration = track_list->tracks_timedSub[index_subGeneric].duration;
						track_base->m_eventTracks[2].m_tracks[i]->m_trackData[j].m_userData = track_list->tracks_timedSub[index_subGeneric].value;
						index_subGeneric++;
					}
				}
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\n");
			}
		}
	}
}

const char* Morpheme::getStringFromStringTable(StringTable* string_table, int id)
{
	//printf_s("String Table: %llx\n", string_table);
	//printf_s("\tm_numEntrys: %d\n", string_table->m_NumEntrys);

	if (id > string_table->m_NumEntrys)
	{	
		printf_s("[ERR, MorphemeSystem] ID %d is OOB. Maximum is %d\n", id, string_table->m_NumEntrys);
		return NULL;
	}

	//printf_s("Offset: %d\n", string_table->m_Offsets[id]);

	return (string_table->m_Data + string_table->m_Offsets[id]);
}

const char* Morpheme::getNetworkNodeNameFromStringTable(uint64_t character_ctrl, int id)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* node_names = *(StringTable**)(tmp + 0xC8);

		string = getStringFromStringTable(node_names, id);

		printf_s("%s\n", string);

		return string;
	}

	return NULL; 
}

const char* Morpheme::getNetworkMessageName(uint64_t character_ctrl, int id)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* message_names = *(StringTable**)(tmp + 0xD0);

		string = getStringFromStringTable(message_names, id);

		printf_s("%s\n", string);

		return string;
	}

	return NULL;
}

const char* Morpheme::getNetworkEventTrackName(uint64_t character_ctrl, int id)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* event_track_names = *(StringTable**)(tmp + 0xD8);

		string = getStringFromStringTable(event_track_names, id);

		printf_s("%s\n", string);

		return string;
	}

	return NULL;
}

void Morpheme::getNetworkAllNodesName(uint64_t character_ctrl)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		FILE* fp;
		char filename[50];
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* node_names = *(StringTable**)(tmp + 0xC8);

		sprintf(filename, ".//DebugManager//out//Nodes_c%i.txt", *(int*)(character_ctrl + 0x28));
		if (fp = fopen(filename, "w"))
		{
			for (size_t i = 0; i < node_names->m_NumEntrys; i++)
			{
				string = getStringFromStringTable(node_names, i);

				if (string)
					fprintf_s(fp, "%i:%s\n", node_names->m_IDs[i], string);
			}

			fclose(fp);
		}
		else
			MessageBoxA(NULL, "Write to file failed. Couldn't find 'out' folder.", "AppDebugManager", MB_ICONERROR);
	}
}

void Morpheme::getNetworkAllMessagesName(uint64_t character_ctrl)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		FILE* fp;
		char filename[50];
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* message_names = *(StringTable**)(tmp + 0xD0);

		sprintf(filename, ".//DebugManager//out//Messages_c%i.txt", *(int*)(character_ctrl + 0x28));
		if (fp = fopen(filename, "w"))
		{
			for (size_t i = 0; i < message_names->m_NumEntrys; i++)
			{
				string = getStringFromStringTable(message_names, i);

				if (string)
					fprintf_s(fp, "%i:%s\n", message_names->m_IDs[i], string);
			}

			fclose(fp);
		}
		else
			MessageBoxA(NULL, "Write to file failed. Couldn't find 'out' folder.", "AppDebugManager", MB_ICONERROR);
	}
}

void Morpheme::getNetworkAllEventTracksName(uint64_t character_ctrl)
{
	if (character_ctrl && *(uint64_t*)(character_ctrl + 0xF8))
	{
		FILE* fp;
		char filename[50];
		const char* string;
		uint64_t tmp = *(uint64_t*)(character_ctrl + 0xF8);
		tmp = *(uint64_t*)(tmp + 0x28);
		tmp = *(uint64_t*)(tmp + 0x20);
		tmp = *(uint64_t*)(tmp);
		StringTable* event_track_names = *(StringTable**)(tmp + 0xD8);

		sprintf(filename, ".//DebugManager//out//EventTrackTypes_c%i.txt", *(int*)(character_ctrl + 0x28));
		if (fp = fopen(filename, "w"))
		{
			for (size_t i = 0; i < event_track_names->m_NumEntrys; i++)
			{
				string = getStringFromStringTable(event_track_names, i);

				if (string)
					fprintf_s(fp, "%i:%s\n", event_track_names->m_IDs[i], string);
			}

			fclose(fp);
		}
		else
			MessageBoxA(NULL, "Write to file failed. Couldn't find 'out' folder.", "AppDebugManager", MB_ICONERROR);
	}
}

void Morpheme::getNetworkAllNames(uint64_t character_ctrl)
{
	getNetworkAllNodesName(character_ctrl);
	getNetworkAllMessagesName(character_ctrl);
	getNetworkAllEventTracksName(character_ctrl);
}

/*
void Morpheme::printBoneList(uint64_t character_ctrl)
{
	if (character_ctrl == 0)
		return;

	FILE* fp;
	char filename[255];

	int bone_count = *(int*)(*(uint64_t*)(character_ctrl + 0xF0) + 0x90);
	//printf_s("[%llX] Bone Count: %d\n", character_ctrl, bone_count);

	uint64_t character_model_ctrl = *(uint64_t*)(character_ctrl + 0xF0);
	uint64_t mdl_skeleton = *(uint64_t*)(character_model_ctrl + 0x88);
	uint64_t morpheme_skeleton = *(uint64_t*)(mdl_skeleton + 0x20);
	uint64_t bone_data = morpheme_skeleton;

	sprintf(filename, ".//DebugManager//out//skeleton//c%d_skeleton.txt", *(int*)(character_ctrl + 0x2C));
	if (fp = fopen(filename, "w"))
	{
		for (size_t i = 0; i < bone_count; i++)
		{
			bone_data = morpheme_skeleton + (byte)i * 0x10;

			short bone_id = *(int*)(bone_data + 0x4);
			char* bone_name = new char[255];
			StringParser::convertString(*(char**)(bone_data + 0x8), bone_name);

			//printf_s("[%d] %s\n", (int)i, bone_name);
			fprintf_s(fp, "%d:%s\n", (int)i, bone_name);

			delete[] bone_name;
		}

		fclose(fp);
	}
	else
		MessageBoxA(NULL, "Write to file failed. Couldn't find 'out/skeleton' folder.", "AppDebugManager", MB_ICONERROR);	
}

void Morpheme::loadBoneData(uint64_t character_ctrl, sBoneData buffer[])
{
	if (character_ctrl)
	{
		uint64_t character_model_ctrl = *(uint64_t*)(character_ctrl + 0xF0);
		uint64_t mdl_skeleton = *(uint64_t*)(character_model_ctrl + 0x88);
		int bone_count = *(uint64_t*)(character_model_ctrl + 0x90);

		uint64_t morpheme_skeleton;

		for (size_t i = 0; i < bone_count; i++)
		{
			morpheme_skeleton = *(uint64_t*)(mdl_skeleton + 0x20) + (byte)i * 0x10;

			buffer[i].unk00 = *(short*)(morpheme_skeleton);
			buffer[i].unk02 = *(short*)(morpheme_skeleton + 0x2);
			buffer[i].unk04 = *(short*)(morpheme_skeleton + 0x4);
			buffer[i].unk06 = *(short*)(morpheme_skeleton + 0x6);
			StringParser::convertString(*(char**)(morpheme_skeleton + 0x8), buffer[i].name);
		}
	}
}

void Morpheme::getCategoryInfo(int category_id, char buffer[])
{
	INIReader reader(".//DebugManager//res//morpheme//EventTrack//morpheme_events.ini");

	if (reader.ParseError() < 0)
	{
		MessageBoxA(NULL, "Failed to load morpheme_events.ini", "AppDebugManager", MB_ICONERROR);

		strcpy(buffer, "Unknown Event");
		return;
	}

	char event_id[32];

	sprintf(event_id, "%d", category_id);

	std::string name = reader.GetString("EventTrackCategory", event_id, "Unknown Event");

	strcpy(buffer, name.c_str());

	return;
}

void Morpheme::getValueInfo(int category, int value, char buffer[])
{
	INIReader reader(".//DebugManager//res//morpheme//EventTrack//morpheme_events.ini");

	if (reader.ParseError() < 0)
	{
		MessageBoxA(NULL, "Failed to load morpheme_events.ini", "AppDebugManager", MB_ICONERROR);

		strcpy(buffer, "Unknown Event");
		return;
	}

	char section[32];
	char event_id[32];
	char event_unk[32];

	sprintf(section, "Value%d", category);
	sprintf(event_id, "%d", value);
	sprintf(event_unk, "Unknown Event %d", value);

	std::string name = reader.GetString(section, event_id, event_unk);

	strcpy(buffer, name.c_str());

	return;
}*/

Morpheme::Network* Morpheme::getNetwork(uint64_t character_ctrl)
{
	if (!character_ctrl)
		return NULL;

	if (*(uint64_t*)(character_ctrl + 0xF8) == NULL)
		return NULL;

	uint64_t chr_motion_ctrl = *(uint64_t*)(character_ctrl + 0xF8);

	if (*(uint64_t*)(chr_motion_ctrl + 0x28) == NULL)
		return NULL;
	
	uint64_t morpheme_motion_ctrl = *(uint64_t*)(chr_motion_ctrl + 0x28);

	if (*(Network**)(morpheme_motion_ctrl + 0x20) == NULL)
		return NULL;

	Network* network = *(Network**)(morpheme_motion_ctrl + 0x20);

	return network;
}

Morpheme::NodeDef* Morpheme::getNetworkNode(Network* network, short node_id)
{
	if (!network || !doesNodeExist(network, node_id))
		return NULL;

	return network->m_networkDef->m_nodes[node_id];
}

/*
std::vector<Morpheme::NodeDef*> Morpheme::getNetworkAllNodesType(uint64_t character_ctrl, NodeType node_type)
{
	Network* network = getNetwork(character_ctrl);
	std::vector<Morpheme::NodeDef*> nodes;

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "CharacterCtrl: %llX, Network: %llX\n", character_ctrl, network);

	if (!network)
		return nodes;

	for (size_t i = 0; i < network->m_networkDef->m_numNodes; i++)
	{
		if (node_type == NodeType::NodeType_NodeAnimSyncEvents && network_inspector.network_config.filter_events)
		{
			if (network->m_networkDef->m_nodes[i]->m_nodeTypeID == node_type)
			{
				NodeData104* node_data = (NodeData104*)network->m_networkDef->m_nodes[i]->node_data;

				uint32_t event_track_count = node_data->m_eventTrackData->m_eventTracks[0].m_trackCount + node_data->m_eventTrackData->m_eventTracks[1].m_trackCount + node_data->m_eventTrackData->m_eventTracks[2].m_trackCount;
				if (event_track_count > 0)
					nodes.push_back(network->m_networkDef->m_nodes[i]);
			}
		}	
		else if (network->m_networkDef->m_nodes[i]->m_nodeTypeID == node_type)
			nodes.push_back(network->m_networkDef->m_nodes[i]);
	}

	return nodes;
}
*/

const char* Morpheme::getAnimNameFromAnimNode(NodeDef* node)
{
	if (node->m_nodeTypeID != NodeType::NodeType_NodeAnimSyncEvents)
	{
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Node %d is not an Animation node\n", node->m_nodeID);
		return NULL;
	}

	NodeData104* node_data = (NodeData104*)node->node_data;
	uint64_t nsa_file = (uint64_t)node_data->m_animData;

	nsa_file = *(uint64_t*)(nsa_file + 0x10);

	const char* animFileName = (const char*)(*(uint64_t*)(nsa_file - 0x8) + 0xD);

	return animFileName;
}

/*
std::vector<Morpheme::NodeDef*> Morpheme::getNetworkControlParameterNodes(uint64_t character_ctrl)
{
	std::vector<Morpheme::NodeDef*> cp_nodes;

	for (size_t i = 0; i < network_inspector.network->m_networkDef->m_numNodes; i++)
		if (network_inspector.network->m_networkDef->m_nodes[i]->m_nodeTypeID == NodeType::NodeType_ControlParameterFloat || network_inspector.network->m_networkDef->m_nodes[i]->m_nodeTypeID == NodeType::NodeType_ControlParameterInt || network_inspector.network->m_networkDef->m_nodes[i]->m_nodeTypeID == NodeType::NodeType_ControlParameterVector3 || network_inspector.network->m_networkDef->m_nodes[i]->m_nodeTypeID == NodeType::NodeType_ControlParameterBool)
			cp_nodes.push_back(network_inspector.network->m_networkDef->m_nodes[i]);

	return cp_nodes;
}*/

const char* Morpheme::stringTableLookup(StringTable* table, short id)
{
	if (id != -1)
	{
		const char* names = table->m_Data;
		return names + table->m_Offsets[id];
	}
	return "";
}

const char* Morpheme::getNodeName(uint64_t character_ctrl, short node_id)
{
	Morpheme::Network* network = Morpheme::getNetwork(character_ctrl);

	if (doesNodeExist(network, node_id))
	{
		StringTable* string_table = network->m_networkDef->m_nodeIDNamesTable;
		return stringTableLookup(string_table, node_id);
	}

	return "";
}

const char* Morpheme::getMessageName(uint64_t character_ctrl, short message_id)
{
	if (message_id != -1)
	{
		Morpheme::Network* network = Morpheme::getNetwork(character_ctrl);

		StringTable* string_table = network->m_networkDef->m_requestIDNamesTable;
		return stringTableLookup(string_table, message_id);
	}

	return "";
}

Morpheme::NodeBin* Morpheme::getNetworkNodeBin(Network* network, short node_id)
{
	if (doesNodeExist(network, node_id))
		return &network->m_nodeBins[node_id];
	
	return NULL;
}

std::vector<Morpheme::sMessageDef*> Morpheme::getMessageDefs(uint64_t character_ctrl)
{
	Morpheme::Network* network = Morpheme::getNetwork(character_ctrl);
	std::vector<sMessageDef*> message_defs;

	for (size_t i = 0; i < network->m_networkDef->message_count; i++)
		message_defs.push_back(network->m_networkDef->message_def[i]);

	return message_defs;
}

bool Morpheme::isNodeActive(Network* network, short node_id)
{
	if (doesNodeExist(network, node_id))
		if ((network->m_nodeConnections[node_id]->flags_1 & 2) >> 1)
			return true;

	return false;
}

bool Morpheme::isNodeContainer(Network* network, short node_id)
{
	if (doesNodeExist(network, node_id))
		if ((network->m_networkDef->m_nodes[node_id]->m_flags1 & 16) >> 4)
			return true;

	return false;
}

bool Morpheme::isNodeConnectedToOutput(Network* network, short node_id)
{
	if (doesNodeExist(network, node_id))
		if ((network->m_networkDef->m_nodes[node_id]->m_flags2 & 64) >> 6)
			return true;

	return false;
}


const char* Morpheme::getNodeTypeName_Alt(Morpheme::Network* network, short node_id)
{
	if (network)
	{
		if (doesNodeExist(network, node_id))
		{
			int node_type = network->m_networkDef->m_nodes[node_id]->m_nodeTypeID;

			switch (node_type)
			{
			case 9:
				return "Network";
			case 10:
				return "StateMachine";
			case 20:
				return "CP_Float";
			case 21:
				return "CP_Vector3";
			case 23:
				return "CP_Bool";
			case 24:
				return "CP_Int";
			case 104:
				return "AnimSyncEvents";
			case 105:
				return "ShareChildren_105";
			case 107:
				return "Blend2SyncEvents";
			case 108:
				return "Blend2Additive_108";
			case 109:
				return "Share1Child1InputCP_109";
			case 110:
				return "ShareCreateFloatOutputAttribute_110";
			case 112:
				return "ShareCreateFloatOutputAttribute_112";
			case 114:
				return "Blend2Additive_114";
			case 120:
				return "TwoBoneIK";
			case 121:
				return "LockFoot";
			case 122:
				return "ShareChildren1CompulsoryManyOptionalInputCPs_120";
			case 125:
				return "Share1Child1InputCP_125";
			case 126:
				return "Freeze";
			case 129:
				return "ShareChildrenOptionalInputCPs";
			case 131:
				return "Switch";
			case 134:
				return "ShareChildren_134";
			case 135:
				return "ShareChildren_135";
			case 136:
				return "Share1Child2OptionalInputCP";
			case 138:
				return "PredictiveUnevenTerrain";
			case 142:
				return "OperatorSmoothDamp";
			case 144:
				return "ShareCreateVector3OutputAttribute";
			case 146:
				return "OperatorRandomFloat";
			case 150:
				return "ShareChildren1CompulsoryManyOptionalInputCPs_150";
			case 151:
				return "ShareChild1InputCP_151";
			case 153:
				return "ShareChildren_153";
			case 170:
				return "SubtractiveBlend";
			case 400:
				return "TransitSyncEvents";
			case 402:
				return "Transit";
			case 500:
				return "Share1Child1OptionalInputCP";
			default:
				char name[255];
				sprintf_s(name, "NodeType_%d", node_type);
				return name;
			}
		}
	}

	return "";
}

/*
const char* Morpheme::getNodeTypeName(Morpheme::Network* network, short node_id)
{
	INIReader node_type(".//MorphemeNetworkInspector//res//NodeType.ini");

	if (node_type.ParseError() < 0)
	{
		MessageBoxA(NULL, "Failed to load NodeType.ini", "MorphemeNetworkInspector", MB_ICONERROR);

		return "";
	}
	char typeID_unk[32];
	char typeID[4];
	sprintf_s(typeID, "%d", network->m_networkDef->m_nodes[node_id]->m_nodeTypeID);
	sprintf_s(typeID_unk, "NodeType_%d", network->m_networkDef->m_nodes[node_id]->m_nodeTypeID);

	std::string typeName = node_type.GetString("NodeType", typeID, typeID_unk);

	return typeName.c_str();
}
*/

bool Morpheme::doesNodeExist(Network* network, short node_id)
{
	if (node_id != -1 && network)
	{
		if (node_id <= network->m_networkDef->m_numNodes)
			return true;
	}
	
	Debug::DebuggerMessage(Debug::LVL_INFO, "Node %d is not present in the current Network\n", node_id);
	return false;
}

uint32_t Morpheme::getTimeActId(Morpheme::NodeDef* node_def)
{
	if (node_def->m_nodeTypeID == NodeType::NodeType_NodeAnimSyncEvents)
	{
		Morpheme::NodeData104* node_data = (Morpheme::NodeData104*)node_def->node_data;

		for (size_t i = 0; i < node_data->m_eventTrackData->m_eventTracks[2].m_trackCount; i++)
		{
			if (node_data->m_eventTrackData->m_eventTracks[2].m_tracks[i]->m_eventId == 1000)
				return node_data->m_eventTrackData->m_eventTracks[2].m_tracks[i]->m_trackData[0].m_userData;
		}	
		MessageBoxA(NULL, "Animation has no TAE associated to it", "MorphemeNetworkInspector", MB_ICONINFORMATION);
		return 0;
	}
	
	MessageBoxA(NULL, "Node is not an animation node", "MorphemeNetworkInspector", MB_ICONERROR);
	return 0;
}

Morpheme::NodeConnections* Morpheme::getNetworkNodeConnections(Morpheme::Network* network, short node_id)
{
	if (doesNodeExist(network, node_id))
		return network->m_nodeConnections[node_id];

	return NULL;
}

/*
int Morpheme::getCurrentAnimFrame(Morpheme::Network* network, short node_id)
{
	if (network)
	{
		if (doesNodeExist(network, node_id))
		{
			NodeDef* node_def = getNetworkNode(network, node_id);

			if (node_def && node_def->m_nodeTypeID != NodeType_NodeAnimSyncEvents)
			{
				Debug::DebuggerMessage(Debug::LVL_ERROR, "Node %d is not an animation node\n", node_def->m_nodeID);
				return 0;
			}

			int current_frame = 0;

			Morpheme::NodeData104* node_data = (Morpheme::NodeData104*)node_def->node_data;

			uint64_t nsaFile = (uint64_t)node_data->m_animData;

			float track_len = *(float*)(nsaFile + 0x84);
			float anim_len = *(float*)(nsaFile + 0x88);

			float current_time = 0;
			float mult = 1;

			NodeBin* node_bin = getNetworkNodeBin(network, node_id);

			if (node_bin && node_bin->m_attributes)
			{
				for (NodeBinEntry* current_bin_entry = node_bin->m_attributes; current_bin_entry != NULL; current_bin_entry = current_bin_entry->m_next)
				{
					if (current_bin_entry->m_semantic == ATTRIB_SEMANTIC_FRACTION_POS)
					{
						current_time = (float)current_bin_entry->m_attribDataHandle->field7_0x18;
						//Debug::DebuggerMessage(Debug::LVL_DEBUG, "UpdateTimePos = (%.3f, %.3f, %.3f, %.3f)\n", *(float*)&current_bin_entry->m_attribDataHandle->m_activeStateID, current_bin_entry->m_attribDataHandle->field6_0x14, current_bin_entry->m_attribDataHandle->field7_0x18, *(float*)&current_bin_entry->m_attribDataHandle->field11_0x1c);
						break;
					}
				}

				if (network_inspector.network_config.eventTrackConfig_scaleToAnim)
					mult = anim_len / track_len;

				current_time *= mult;
				current_frame = MathHelper::TimeToFrame(current_time, 60);
			}

			return current_frame;
		}
	}
	
	return 0;
}

void Morpheme::getNetworkNodeName(char buffer[], uint64_t character_ctrl, short id)
{
	INIReader reader(".//MorphemeNetworkInspector//networks//c%d//c%d_def.ini");

	if (reader.ParseError() < 0)
	{
		MessageBoxA(NULL, "Failed to load def.ini", "MorphemeNetworkInspector", MB_ICONERROR);

		return;
	}

	char id_str[8];

	sprintf(id_str, "%d", id);

	std::string name = reader.GetString("NodeNames", id_str, "");

	if (name == "")
		name = getNodeName(character_ctrl, id);
	
	strcpy(buffer, name.c_str());
	return;
}
*/