#include "EventTrackEditor.h"
#include "../Application/Application.h"

EventTrackEditor::EventTrack::EventTrack(int signature, int numEvents, int eventId, Event* event, const char* name, bool is_discrete)
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
        this->m_event[i].m_duration = event[i].m_duration;
        this->m_event[i].m_value = event[i].m_value;
    }
}

EventTrackEditor::EventTrack::EventTrack(MorphemeBundle_EventTrack* src, float len, bool discrete)
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
        this->m_event[i].m_frameStart = MathHelper::TimeToFrame(src->m_data->m_events[i].m_start * len);
        this->m_event[i].m_duration = MathHelper::TimeToFrame(src->m_data->m_events[i].m_duration * len);
        this->m_event[i].m_value = src->m_data->m_events[i].m_value;
    }
}

void EventTrackEditor::EventTrack::SaveEventTrackData(float len)
{
    if (this->m_signature != this->source->m_signature)
    {
        Debug::DebuggerMessage(Debug::LVL_WARN, "Signature mismach for track %s\n", this->m_name);
        Debug::Alert(MB_ICONEXCLAMATION, "EventTrackEditor.cpp", "Signature mismach for track %s", this->m_name);

        return;
    }

    this->source->m_data->m_numEvents = this->m_numEvents;
    this->source->m_data->m_eventId = this->m_eventId;
    
    for (int i = 0; i < this->m_numEvents; i++)
    {
        this->source->m_data->m_events[i].m_start = MathHelper::FrameToTime(this->m_event[i].m_frameStart) / len;
        this->source->m_data->m_events[i].m_duration = MathHelper::FrameToTime(this->m_event[i].m_duration) / len;
        this->source->m_data->m_events[i].m_value = this->m_event[i].m_value;
    }
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

void EventTrackEditor::BeginEdit(int idx) {}

void EventTrackEditor::EndEdit() {}

const char* EventTrackEditor::GetTrackName(int idx) const { return m_eventTracks[idx].m_name; }

std::string EventTrackEditor::GetEventLabel(int track_idx, int event_idx) const
{
    return std::to_string(this->m_eventTracks[track_idx].m_event[event_idx].m_value);
}

void EventTrackEditor::AddTrack(int event_id, const char* name, bool discrete)
{
    int signature = rand();
    bool valid = true;
    do
    {
        signature = rand();

        for (int i = 0; i < morpheme_connect.nmb.m_bundles.size(); i++)
        {
            if (morpheme_connect.nmb.m_bundles[i].m_signature == signature)
            {
                valid = false;
            }
        }

    } while (valid == false);

    if (discrete)
        m_eventTracks.push_back(EventTrack(signature, 0, event_id, NULL, name, true));
    else
        m_eventTracks.push_back(EventTrack(signature, 0, event_id, NULL, name, true));
};

void EventTrackEditor::DeleteEvent(int track_idx, int event_idx)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    if (track->m_numEvents > 1)
    {
        EventTrack::Event* new_events = new EventTrack::Event[track->m_numEvents - 1];

        for (size_t i = 0; i < track->m_numEvents; i++)
        {
            if (i < event_idx)
                new_events[i] = track->m_event[i];
            else if (i > event_idx)
                new_events[i - 1] = track->m_event[i];
        }

        track->m_numEvents--;

        delete[] track->m_event;

        track->m_event = new_events;

        MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->source->m_data->m_numEvents - 1];

        for (size_t i = 0; i < track->source->m_data->m_numEvents; i++)
        {
            if (i < event_idx)
                new_src_events[i] = track->source->m_data->m_events[i];
            else if (i > event_idx)
                new_src_events[i - 1] = track->source->m_data->m_events[i];
        }

        track->source->m_data->m_numEvents--;

        delete[] track->source->m_data->m_events;

        track->source->m_data->m_events = new_src_events;

        return;
    }

    track->m_numEvents--;
    track->source->m_data->m_numEvents--;

    delete[] track->m_event;
    delete[] track->source->m_data->m_events;
}

void EventTrackEditor::AddEvent(int track_idx, EventTrack::Event event)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    if (track->m_numEvents == 0)
    {
        track->m_numEvents++;
        track->source->m_data->m_numEvents++;

        track->m_event = new EventTrack::Event{ event.m_frameStart, event.m_duration, event.m_value };
        track->source->m_data->m_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value };
        return;
    }

    EventTrack::Event* new_events = new EventTrack::Event[track->m_numEvents + 1];

    for (size_t i = 0; i < track->m_numEvents; i++)
        new_events[i] = track->m_event[i];

    new_events[track->m_numEvents] = event;

    track->m_numEvents++;

    delete[] track->m_event;

    track->m_event = new_events;

    MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->source->m_data->m_numEvents + 1];

    for (size_t i = 0; i < track->source->m_data->m_numEvents; i++)
        new_src_events[i] = track->source->m_data->m_events[i];

    new_src_events[track->source->m_data->m_numEvents] = MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value };

    track->source->m_data->m_numEvents++;

    delete[] track->source->m_data->m_events;

    track->source->m_data->m_events = new_src_events;
}

EventTrackEditor::EventTrackEditor() {}

void EventTrackEditor::Clear()
{
    this->m_eventTracks.clear();
}