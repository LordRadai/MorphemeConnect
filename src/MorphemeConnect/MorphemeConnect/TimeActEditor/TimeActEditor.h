#pragma once
#include <math.h>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <string>

#include "../FromsoftFormat/TimeActReader/TimeActReader.h"
#include "../MathHelper/MathHelper.h"

struct TimeActEditor
{
    struct TimeActTrack
    {
        struct Event
        {
            int m_frameStart = 0;
            int m_duration = 0;
            int m_value = 0;

            TimeActEventData* m_args = nullptr;
        };

        EventGroup* m_source;
        int m_count;
        int m_eventGroup;
        std::vector<Event> m_event;
        char m_name[50];

        TimeActTrack(int eventId, float start, float end);
        TimeActTrack(EventGroup* src);

        void SaveTimeActTrack();
        bool IsEventActive(int idx, int frame);
    };

    TimeAct* m_source;

    std::vector<TimeActTrack> m_tracks;
    int m_frameMin, m_frameMax;
    bool focused = false;

    struct EventTrackColor
    {
        ImVec4 m_trackColor = { 0.33f, 0.33f, 0.33f, 1.f };
        ImVec4 m_trackColorInactive = { 0.33f, 0.33f, 0.33f, 1.f };
        ImVec4 m_trackColorInvert = { 0.33f, 0.33f, 0.33f, 1.f };
        ImVec4 m_trackColorActive = { 0.f, 0.4f, 0.8f, 1.f };
        ImVec4 m_trackBoundingBox = { 0.f, 0.f, 0.f, 1.f };
        ImVec4 m_trackBoundingBoxActive = { 1.f, 1.f, 0.f, 1.f };
        ImVec4 m_trackTextColor = { 1.f, 1.f, 1.f, 1.f };
        ImVec4 m_cursorColor = { 0.f, 0.f, 0.f, 1.f };
    } m_colors;

    TimeActEditor();

    int GetFrameMin() const;
    int GetFrameMax() const;
    int GetTrackCount() const;

    std::string GetTrackName(int idx);
    std::string GetEventLabel(int idx, int event_idx) const;

    void AddGroup(int id);
    void DeleteGroup(int idx);

    void AddEvent(int group_idx, TimeActEvent event);
    void DeleteEvent(int group_idx, int event_idx);

    void ReloadTracks();

    void Clear();
};
