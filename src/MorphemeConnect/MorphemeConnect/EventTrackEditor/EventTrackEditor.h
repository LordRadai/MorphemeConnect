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
        bool IsEventActive(int event_idx, int frame);
    };

    NodeDef* m_nodeSource = NULL;
    int m_animIdx = -1;
    std::vector<EventTrack> m_eventTracks;
    int m_frameMin, m_frameMax;
    bool focused = false;

    struct EventTrackColor
    {
        ImVec4 m_trackColor = { 0.31f, 0.31f, 0.91f, 1.f };
        ImVec4 m_trackColorInactive = { 0.22f, 0.22f, 0.44f, 1.f };
        ImVec4 m_trackColorInvert = { 0.51f, 0.49f, 0.95f, 1.f };
        ImVec4 m_trackColorActive = { 0.28f, 0.28f, 0.48f, 1.f };
        ImVec4 m_trackBoundingBox = { 0.f, 0.f, 0.f, 1.f };
        ImVec4 m_trackBoundingBoxActive = { 1.f, 0.f, 0.f, 1.f };
        ImVec4 m_trackTextColor = { 1.f, 1.f, 1.f, 1.f };
        ImVec4 m_cursorColor = { 1.f, 0.f, 0.f, 1.f };
    } m_colors;

    EventTrackEditor();

    int GetFrameMin() const;
    int GetFrameMax() const;
    int GetTrackCount() const;

    char* GetTrackName(int idx) const;
    std::string GetEventLabel(int track_idx, int event_idx) const;

    void AddTrack(int event_id, char* name, bool duration);
    void DeleteTrack(int idx);

    void AddEvent(int track_idx, EventTrack::Event event);
    void DeleteEvent(int track_idx, int event_idx);

    void ReloadTracks();

    void Clear();
};
