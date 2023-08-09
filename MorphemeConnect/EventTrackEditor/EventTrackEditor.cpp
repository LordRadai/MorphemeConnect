#include "EventTrackEditor.h"
#include "../Application/Application.h"

EventTrackEditor::EventTrack::EventTrack(int signature, int numEvents, int eventId, Event* event, const char* name, bool is_discrete)
{
    this->m_source = NULL;

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
        Debug::DebuggerMessage(Debug::LVL_WARN, "Signature mismach for track %s\n", this->m_name);
        Debug::Alert(MB_ICONEXCLAMATION, "EventTrackEditor.cpp", "Signature mismach for track %s", this->m_name);

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

    MorphemeBundle_EventTrack new_bundle;

    new_bundle.m_magic[0] = 24;
    new_bundle.m_magic[1] = 10;

    if (discrete)
        new_bundle.m_bundleType = Bundle_DiscreteEventTrack;
    else
        new_bundle.m_bundleType = Bundle_DurationEventTrack;

    new_bundle.m_signature = signature;

    for (size_t i = 0; i < 16; i++)
    {
        new_bundle.m_header[i] = 0; //This is most likely incorrect. Need a way to generate the header
    }

    int data_size = 32 + 12 * 0 + strlen(name); //32 bytes fixed + 12 * trackCount + nameLenght + padding for alignment
    int remainder = data_size % 16;

    if (remainder != 0)
    {
        int next_integer = (data_size - remainder) + 16; //Adjust so that the bundle end address will be aligned to 16 bytes
        data_size = next_integer;
    }

    new_bundle.m_dataSize = data_size;
    new_bundle.m_dataAlignment = 16;
    new_bundle.m_iVar2C = 0;

    new_bundle.m_data = new MorphemeBundle_EventTrack::BundleData_EventTrack;

    new_bundle.m_data->m_numEvents = 0;
    new_bundle.m_data->m_iVar4 = 0;
    new_bundle.m_data->m_trackName = name;
    new_bundle.m_data->m_eventId = event_id;
    new_bundle.m_data->m_iVar14 = 0;
    new_bundle.m_data->m_events = NULL;

    morpheme_connect.nmb.m_eventTracks.push_back(new_bundle);

    m_eventTracks.push_back(EventTrack(signature, 0, event_id, NULL, name, discrete));
    m_eventTracks.back().m_source = &morpheme_connect.nmb.m_eventTracks.back();

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added track %d (%s)\n", signature, name);
};

void EventTrackEditor::DeleteTrack(int idx)
{
    int erase_idx = 0;
    for (int i = 0; i < morpheme_connect.nmb.m_eventTracks.size(); i++)
    {
        if (morpheme_connect.nmb.m_eventTracks[i].m_signature == this->m_eventTracks[idx].m_signature)
        {
            erase_idx = i;
            break;
        }
    }

    if (erase_idx > -1)
    {
        Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted track %d (%s)\n", this->m_eventTracks[idx].m_signature, this->m_eventTracks[idx].m_name);

        this->m_eventTracks.erase(this->m_eventTracks.begin() + idx);

        morpheme_connect.nmb.m_eventTracks.erase(morpheme_connect.nmb.m_eventTracks.begin() + erase_idx);

        return;
    }

    Debug::Alert(MB_ICONERROR, "EventTrackEditor.cpp", "Could not find event track with the specified signature");
}

void EventTrackEditor::AddEvent(int track_idx, EventTrack::Event event)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    if (track->m_numEvents == 0)
    {
        track->m_numEvents++;
        track->m_source->m_data->m_numEvents++;

        track->m_event = new EventTrack::Event{ event.m_frameStart, event.m_duration, event.m_value };
        track->m_source->m_data->m_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value };
        
        Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added event to track %d (%.3f, %.3f, %d)\n", track->m_signature, MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value);

        return;
    }

    EventTrack::Event* new_events = new EventTrack::Event[track->m_numEvents + 1];

    for (size_t i = 0; i < track->m_numEvents; i++)
        new_events[i] = track->m_event[i];

    new_events[track->m_numEvents] = event;

    track->m_numEvents++;

    delete[] track->m_event;

    track->m_event = new_events;

    MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->m_source->m_data->m_numEvents + 1];

    for (size_t i = 0; i < track->m_source->m_data->m_numEvents; i++)
        new_src_events[i] = track->m_source->m_data->m_events[i];

    new_src_events[track->m_source->m_data->m_numEvents] = MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value };

    track->m_source->m_data->m_numEvents++;

    delete[] track->m_source->m_data->m_events;

    track->m_source->m_data->m_events = new_src_events;

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added event to track %d (%.3f, %.3f, %d)\n", track->m_signature, MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value);
}

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

        MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->m_source->m_data->m_numEvents - 1];

        for (size_t i = 0; i < track->m_source->m_data->m_numEvents; i++)
        {
            if (i < event_idx)
                new_src_events[i] = track->m_source->m_data->m_events[i];
            else if (i > event_idx)
                new_src_events[i - 1] = track->m_source->m_data->m_events[i];
        }

        track->m_source->m_data->m_numEvents--;

        delete[] track->m_source->m_data->m_events;

        track->m_source->m_data->m_events = new_src_events;

        Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d from Track %d\n", event_idx, track->m_signature);

        return;
    }

    track->m_numEvents--;
    track->m_source->m_data->m_numEvents--;

    delete[] track->m_event;
    delete[] track->m_source->m_data->m_events;

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d from Track %d\n", event_idx, track->m_signature);
}

EventTrackEditor::EventTrackEditor() {}

void EventTrackEditor::Clear()
{
    this->m_eventTracks.clear();
}