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
            int m_frameStart = 0;
            int m_duration = 0;
            int m_value = 0;
        };

        MorphemeBundle_EventTrack* m_source;

        int m_signature;
        int m_numEvents;
        int m_eventId;
        Event* m_event;
        char* m_name;
        bool m_discrete;

        EventTrack(int signature, int numEvents, int eventId, Event* event, char* name, bool is_discrete);
        EventTrack(MorphemeBundle_EventTrack* src, float len, bool discrete);

        void SaveEventTrackData(float len);
    };

    NodeDef* m_nodeSource = NULL;
    int m_animIdx = -1;
    std::vector<EventTrack> m_eventTracks;
    int m_frameMin, m_frameMax;
    bool focused = false;

    int GetFrameMin() const;
    int GetFrameMax() const;
    int GetTrackCount() const;

    void BeginEdit(int idx);
    void EndEdit();

    char* GetTrackName(int idx) const;
    std::string GetEventLabel(int track_idx, int event_idx) const;

    void AddTrack(int event_id, char* name, bool discrete);
    void DeleteTrack(int idx);
    void RenameTrack(int idx, char* name);

    void AddEvent(int track_idx, EventTrack::Event event);
    void DeleteEvent(int track_idx, int event_idx);

    EventTrackEditor();

    void Clear();
};
