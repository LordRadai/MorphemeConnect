#pragma once
#include <math.h>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <string>
#include "../NMBReader/NMBReader.h"
#include "../MathHelper/MathHelper.h"

struct EventTrackEditor
{
    struct EventTrack
    {
        struct Event
        {
            int m_frameStart, m_frameEnd;
            int m_value;
        };

        MorphemeBundle_EventTrack* source;

        int m_signature;
        int m_numEvents;
        int m_eventId;
        Event* m_event;
        const char* m_name;
        bool m_discrete;

        EventTrack(int signature, int numEvents, int eventId, Event* event, const char* name, bool is_discrete)
        {
            this->source = NULL;

            this->m_signature = signature;
            this->m_numEvents = numEvents;
            this->m_eventId = eventId;
            this->m_name = name;
            this->m_discrete = is_discrete;

            this->m_event = new Event[this->m_numEvents];

            for (size_t i = 0; i < numEvents; i++)
            {
                this->m_event[i].m_frameStart = event[i].m_frameStart;
                this->m_event[i].m_frameEnd = event[i].m_frameEnd;
                this->m_event[i].m_value = event[i].m_value;
            }
        }

        EventTrack(MorphemeBundle_EventTrack* src, float len, bool discrete)
        {
            this->source = src;
            this->m_signature = src->m_signature;
            this->m_numEvents = src->m_data->m_numEvents;
            this->m_eventId = src->m_data->m_eventId;
            this->m_name = src->m_data->m_trackName;

            this->m_discrete = discrete;

            this->m_event = new Event[this->m_numEvents];

            for (size_t i = 0; i < src->m_data->m_numEvents; i++)
            {
                this->m_event[i].m_frameStart = MathHelper::TimeToFrame(src->m_data->m_trackData[i].m_start * len);
                
                if (this->m_discrete == false)
                    this->m_event[i].m_frameEnd = MathHelper::TimeToFrame((src->m_data->m_trackData[i].m_start + src->m_data->m_trackData[i].m_duration) * len);
                else
                    this->m_event[i].m_frameEnd = this->m_event[i].m_frameStart;

                this->m_event[i].m_value = src->m_data->m_trackData[i].m_userData;
            }
        }

        //void SaveEventTrackData(float multiplier);
    };
    std::vector<EventTrack> m_eventTracks;
    int mFrameMin, mFrameMax;
    bool focused = false;

    int GetFrameMin() const;
    int GetFrameMax() const;
    int GetTrackCount() const;

    void BeginEdit(int idx);
    void EndEdit();

    const char* GetTrackName(int idx) const;
    std::string GetEventLabel(int track_idx, int event_idx) const;

    void AddTrack(bool discrete);

    void DelTrack(int index);
    void DuplicateTrack(int index);

    EventTrackEditor();

    void Clear();
};
