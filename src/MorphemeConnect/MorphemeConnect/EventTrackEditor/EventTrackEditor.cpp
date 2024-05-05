#include "EventTrackEditor.h"
#include "../Application/Application.h"

EventTrackEditor::EventTrack::EventTrack(int signature, int numEvents, int eventId, Event* event, char* name, bool is_discrete)
{
    this->m_source = NULL;

    this->m_signature = signature;
    this->m_numEvents = numEvents;
    this->m_eventId = eventId;

    this->m_name = new char[50];
    strcpy(this->m_name, name);

    this->m_discrete = is_discrete;

    this->m_event = new Event[this->m_numEvents];

    for (size_t i = 0; i < numEvents; i++)
    {
        this->m_event[i].m_frameStart = event[i].m_frameStart;
        this->m_event[i].m_duration = event[i].m_duration;
        this->m_event[i].m_value = event[i].m_value;
    }
}

EventTrackEditor::EventTrack::EventTrack(MorphemeBundle_EventTrack* src, float len, bool discrete)
{
    this->m_source = src;
    this->m_signature = src->m_signature;
    this->m_numEvents = src->m_data->m_numEvents;
    this->m_eventId = src->m_data->m_eventId;
    this->m_name = src->m_data->m_trackName;

    this->m_discrete = discrete;

    this->m_event = new Event[this->m_numEvents];

    for (size_t i = 0; i < src->m_data->m_numEvents; i++)
    {
        this->m_event[i].m_frameStart = MathHelper::TimeToFrame(src->m_data->m_events[i].m_start * len);
        this->m_event[i].m_duration = MathHelper::TimeToFrame(src->m_data->m_events[i].m_duration * len);
        this->m_event[i].m_value = src->m_data->m_events[i].m_value;
    }
}

void EventTrackEditor::EventTrack::SaveEventTrackData(float len)
{
    if (this->m_signature != this->m_source->m_signature)
    {
        RDebug::SystemPanic("EventTrackEditor.cpp", "Signature mismach for track %s", this->m_name);

        return;
    }

    this->m_source->m_data->m_numEvents = this->m_numEvents;
    this->m_source->m_data->m_eventId = this->m_eventId;
    
    for (int i = 0; i < this->m_numEvents; i++)
    {
        this->m_source->m_data->m_events[i].m_start = MathHelper::FrameToTime(this->m_event[i].m_frameStart) / len;
        this->m_source->m_data->m_events[i].m_duration = MathHelper::FrameToTime(this->m_event[i].m_duration) / len;
        this->m_source->m_data->m_events[i].m_value = this->m_event[i].m_value;
    }
}

bool EventTrackEditor::EventTrack::IsEventActive(int event_idx, int frame)
{
    if (!this->m_discrete)
    {
        if ((frame >= this->m_event[event_idx].m_frameStart) && frame <= (this->m_event[event_idx].m_duration + this->m_event[event_idx].m_frameStart))
            return true;
    }
    else
    {
        if (frame == this->m_event[event_idx].m_frameStart)
            return true;
    }

    return false;
}


int EventTrackEditor::GetFrameMin() const
{
    return m_frameMin;
}

int EventTrackEditor::GetFrameMax() const
{
    return m_frameMax;
}

int EventTrackEditor::GetTrackCount() const { return (int)m_eventTracks.size(); }

char* EventTrackEditor::GetTrackName(int idx) const { return m_eventTracks[idx].m_name; }

std::string EventTrackEditor::GetEventLabel(int track_idx, int event_idx) const
{
    return std::to_string(this->m_eventTracks[track_idx].m_event[event_idx].m_value);
}

void EventTrackEditor::AddTrack(int event_id, char* name, bool duration)
{
    MorphemeBundle_EventTrack* new_track = g_morphemeConnect.m_nmb.AddEventTrack(this->m_nodeSource, event_id, name, duration);

    RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Added EventTrack %d (%s) (node=%d)\n", new_track->m_signature, name, this->m_nodeSource->m_nodeID);
};

void EventTrackEditor::DeleteTrack(int idx)
{
    int delete_signature = this->m_eventTracks[idx].m_signature;
    char delete_name[50];

    strcpy(delete_name, this->m_eventTracks[idx].m_name);

    while (this->m_eventTracks[idx].m_numEvents > 0)
        this->DeleteEvent(idx, 0);

    NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)this->m_nodeSource->m_nodeData[1].m_attrib;
    NodeAttribSourceEventTrack* event_tracks = (NodeAttribSourceEventTrack*)this->m_nodeSource->m_nodeData[2].m_attrib;

    if (this->m_eventTracks[idx].m_discrete)
    {
        event_tracks->m_eventTracks[0].m_trackCount--;
        event_tracks->m_eventTracks[0].m_trackSignatures.erase(event_tracks->m_eventTracks[0].m_trackSignatures.begin() + idx);
    }
    else
    {
        event_tracks->m_eventTracks[2].m_trackCount--;
        event_tracks->m_eventTracks[2].m_trackSignatures.erase(event_tracks->m_eventTracks[0].m_trackSignatures.begin() + idx);
    }

    std::vector<NodeDef*> nodes = g_morphemeConnect.m_nmb.GetNodesByAnimReference(source_anim->m_animIdx);

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] != this->m_nodeSource)
        {
            NodeAttribSourceEventTrack* event_tracks_new = (NodeAttribSourceEventTrack*)nodes[i]->m_nodeData[2].m_attrib;

            event_tracks_new->m_eventTracks[0] = event_tracks->m_eventTracks[0];
            event_tracks_new->m_eventTracks[1] = event_tracks->m_eventTracks[1];
            event_tracks_new->m_eventTracks[2] = event_tracks->m_eventTracks[2];
        }
    }

    this->m_reload = true;

    RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Deleted track %d (%s) (node=%d)\n", delete_signature, delete_name, this->m_nodeSource->m_nodeID);
}

void EventTrackEditor::AddEvent(int track_idx, EventTrack::Event event)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    track->m_source->m_data->m_numEvents++;
    track->m_source->m_data->m_events.push_back(MorphemeBundle_EventTrack::BundleData_EventTrack::Event{MathHelper::FrameToTime(event.m_frameStart) / MathHelper::FrameToTime(this->m_frameMax), MathHelper::FrameToTime(event.m_duration) / MathHelper::FrameToTime(this->m_frameMax), event.m_value});
        
    this->m_reload = true;

    RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Added event to track %d (%.3f, %.3f, %d) (node=%d)\n", track->m_signature, MathHelper::FrameToTime(event.m_frameStart) / MathHelper::FrameToTime(this->m_frameMax), MathHelper::FrameToTime(event.m_duration) / MathHelper::FrameToTime(this->m_frameMax), event.m_value, this->m_nodeSource->m_nodeID);

    return;
}

void EventTrackEditor::DeleteEvent(int track_idx, int event_idx)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    track->m_source->m_data->m_numEvents--;
    track->m_source->m_data->m_events.erase(track->m_source->m_data->m_events.begin() + event_idx);

    RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Deleted event %d from Track %d (node=%d)\n", event_idx, track->m_signature, this->m_nodeSource->m_nodeID);

    this->m_reload = true;

    return;
}

void EventTrackEditor::ReloadTracks()
{
    this->m_eventTracks.clear();
    this->SetEditedState(false);

    if ((g_morphemeConnect.m_nmb.IsInitialised()) && (g_morphemeConnect.m_eventTrackEditorFlags.m_targetAnimIdx != -1))
    {
        bool found = false;

        NodeAttribSourceAnim* source_anim = (NodeAttribSourceAnim*)this->m_nodeSource->m_nodeData[1].m_attrib;
        NodeAttribSourceEventTrack* event_track_source = (NodeAttribSourceEventTrack*)this->m_nodeSource->m_nodeData[2].m_attrib;

        if (event_track_source != NULL)
        {
            for (int i = 0; i < event_track_source->m_eventTracks[0].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = g_morphemeConnect.m_nmb.GetEventTrackBundle(event_track_source->m_eventTracks[0].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), true));
            }

            for (int i = 0; i < event_track_source->m_eventTracks[1].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = g_morphemeConnect.m_nmb.GetEventTrackBundle(event_track_source->m_eventTracks[1].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), false));
            }

            for (int i = 0; i < event_track_source->m_eventTracks[2].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = g_morphemeConnect.m_nmb.GetEventTrackBundle(event_track_source->m_eventTracks[2].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), false));
            }
        }
    }
}

EventTrackEditor::EventTrackEditor() 
{
    this->m_nodeSource = nullptr;

    INIReader reader(".//MorphemeConnect//res//color//eventrack.ini");

    if (reader.ParseError() < 0)
    {
        RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "EventTrackEditor.cpp", "Failed to load eventrack.ini\n");

        this->m_colors.m_trackColor = { 0.31f, 0.31f, 0.91f, 1.f };
        this->m_colors.m_trackColorInactive = { 0.22f, 0.22f, 0.44f, 1.f };
        this->m_colors.m_trackColorActive = { 0.39f, 0.39f, 1.f, 1.f };
        this->m_colors.m_trackBoundingBox = { 0.f, 0.f, 0.f, 1.f };
        this->m_colors.m_trackBoundingBoxActive = { 0.f, 0.f, 0.f, 1.f };
        this->m_colors.m_trackTextColor = { 1.f, 1.f, 1.f, 1.f };
        this->m_colors.m_cursorColor = { 0.f, 0.f, 0.f, 0.f };
    }

    this->m_colors.m_trackColor = { (float)reader.GetReal("Track", "r", 0.31f), (float)reader.GetReal("Track", "g", 0.31f), (float)reader.GetReal("Track", "b", 0.91f), (float)reader.GetReal("Track", "a", 1.f) };
    this->m_colors.m_trackColorInactive = { (float)reader.GetReal("TrackInactive", "r", 0.22f), (float)reader.GetReal("TrackInactive", "g", 0.22f), (float)reader.GetReal("TrackInactive", "b", 0.44f), (float)reader.GetReal("TrackInactive", "a", 1.f) };
    this->m_colors.m_trackColorActive = { (float)reader.GetReal("TrackActive", "r", 0.39f), (float)reader.GetReal("TrackActive", "g", 0.39f), (float)reader.GetReal("TrackActive", "b", 1.f), (float)reader.GetReal("TrackActive", "a", 1.f) };
    this->m_colors.m_trackBoundingBox = { (float)reader.GetReal("TrackBoundingBox", "r", 0.f), (float)reader.GetReal("TrackBoundingBox", "g", 0.f), (float)reader.GetReal("TrackBoundingBox", "b", 0.f), (float)reader.GetReal("TrackBoundingBox", "a", 1.f) };
    this->m_colors.m_trackBoundingBoxActive = { (float)reader.GetReal("TrackActiveBoundingBox", "r", 0.f), (float)reader.GetReal("TrackActiveBoundingBox", "g", 0.f), (float)reader.GetReal("TrackActiveBoundingBox", "b", 0.f), (float)reader.GetReal("TrackActiveBoundingBox", "a", 1.f) };
    this->m_colors.m_trackTextColor = { (float)reader.GetReal("TrackText", "r", 1.f), (float)reader.GetReal("TrackText", "g", 1.f), (float)reader.GetReal("TrackText", "b", 1.f), (float)reader.GetReal("TrackText", "a", 1.f) };
    this->m_colors.m_cursorColor = { (float)reader.GetReal("TrackCursor", "r", 0.f), (float)reader.GetReal("TrackCursor", "g", 0.f), (float)reader.GetReal("TrackCursor", "b", 0.f), (float)reader.GetReal("TrackCursor", "a", 0.f) };

}

void EventTrackEditor::SetEditedState(bool state)
{
    if (this->m_animIdx == -1)
        return;

    if (g_morphemeConnect.m_eventTrackEditorFlags.m_edited.size() > this->m_animIdx)
        g_morphemeConnect.m_eventTrackEditorFlags.m_edited[this->m_animIdx] = state;
    else
        RDebug::SystemPanic("EventTrackEditor.cpp", "Out of bound read while setting edited state (idx=%d, size=%d)\n", this->m_animIdx, g_morphemeConnect.m_eventTrackEditorFlags.m_edited.size());
}

void EventTrackEditor::Clear()
{
    this->m_animIdx = -1;
    this->m_frameMax = 0;
    this->m_frameMin = 0;
    this->m_nodeSource = nullptr;
    this->m_eventTracks.clear();
}