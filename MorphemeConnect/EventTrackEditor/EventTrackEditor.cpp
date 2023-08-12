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
        Debug::Panic("EventTrackEditor.cpp", "Signature mismach for track %s", this->m_name);

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

    if (!duration)
        new_bundle.m_bundleType = Bundle_DiscreteEventTrack;
    else
        new_bundle.m_bundleType = Bundle_DurationEventTrack;

    new_bundle.m_signature = signature;

    for (size_t i = 0; i < 16; i++)
        new_bundle.m_header[i] = 0; //This is most likely incorrect. Need a way to generate the header

    new_bundle.m_dataSize = 0;
    new_bundle.m_dataAlignment = 16;
    new_bundle.m_iVar2C = 0;

    new_bundle.m_data = new MorphemeBundle_EventTrack::BundleData_EventTrack;

    new_bundle.m_data->m_numEvents = 0;
    new_bundle.m_data->m_iVar4 = 0;

    new_bundle.m_data->m_trackName = new char[50];
    strcpy(new_bundle.m_data->m_trackName, name);

    new_bundle.m_data->m_eventId = event_id;
    new_bundle.m_data->m_iVar14 = 0;
    new_bundle.m_data->m_events = NULL;

    new_bundle.CalculateBundleSize();

    morpheme_connect.nmb.m_eventTracks.push_back(new_bundle);

    NodeData104* data = (NodeData104*)this->m_nodeSource->node_data;

    if (!duration)
    {
        UINT64* new_signatures = new UINT64[data->m_attribEventTrack->m_eventTracks[0].m_trackCount + 1];

        for (size_t i = 0; i < data->m_attribEventTrack->m_eventTracks[0].m_trackCount; i++)
            new_signatures[i] = data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures[i];
        
        new_signatures[data->m_attribEventTrack->m_eventTracks[0].m_trackCount] = new_bundle.m_signature;

        data->m_attribEventTrack->m_eventTracks[0].m_trackCount++;

        delete[] data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures;

        data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures = new_signatures;
    }
    else
    {
        UINT64* new_signatures = new UINT64[data->m_attribEventTrack->m_eventTracks[2].m_trackCount + 1];

        for (size_t i = 0; i < data->m_attribEventTrack->m_eventTracks[2].m_trackCount; i++)
            new_signatures[i] = data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures[i];

        new_signatures[data->m_attribEventTrack->m_eventTracks[2].m_trackCount] = new_bundle.m_signature;

        data->m_attribEventTrack->m_eventTracks[2].m_trackCount++;

        delete[] data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures;

        data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures = new_signatures;
    }

    std::vector<NodeDef*> nodes = morpheme_connect.nmb.GetNodesByAnimReference(data->m_attribSourceAnim->m_animIdx);

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] != this->m_nodeSource)
        {
            NodeData104* node_data = (NodeData104*)nodes[i]->node_data;

            node_data->m_attribEventTrack->m_eventTracks[0] = data->m_attribEventTrack->m_eventTracks[0];
            node_data->m_attribEventTrack->m_eventTracks[1] = data->m_attribEventTrack->m_eventTracks[1];
            node_data->m_attribEventTrack->m_eventTracks[2] = data->m_attribEventTrack->m_eventTracks[2];
        }
    }

    this->ReloadTracks();

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added EventTrack %d (%s) (node=%d)\n", signature, name, this->m_nodeSource->m_nodeID);
};

void EventTrackEditor::DeleteTrack(int idx)
{
    int delete_signature = this->m_eventTracks[idx].m_signature;
    char delete_name[50];

    strcpy(delete_name, this->m_eventTracks[idx].m_name);

    for (size_t i = 0; i < this->m_eventTracks[idx].m_numEvents; i++)
        this->DeleteEvent(idx, i);

    NodeData104* data = (NodeData104*)this->m_nodeSource->node_data;
    
    if (this->m_eventTracks[idx].m_discrete)
    {
        int sgn_idx = 0;
        UINT64* new_signatures = new UINT64[data->m_attribEventTrack->m_eventTracks[0].m_trackCount - 1];

        for (int i = 0; i < data->m_attribEventTrack->m_eventTracks[0].m_trackCount; i++)
        {
            if (data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures[i] != this->m_eventTracks[idx].m_signature)
            {
                new_signatures[sgn_idx] = data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures[i];
                sgn_idx++;
            }
        }

        data->m_attribEventTrack->m_eventTracks[0].m_trackCount--;

        delete[] data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures;

        data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures = new_signatures;
    }
    else
    {
        int sgn_idx = 0;
        UINT64* new_signatures = new UINT64[data->m_attribEventTrack->m_eventTracks[2].m_trackCount - 1];

        for (int i = 0; i < data->m_attribEventTrack->m_eventTracks[2].m_trackCount; i++)
        {
            if (data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures[i] != this->m_eventTracks[idx].m_signature)
            {
                new_signatures[sgn_idx] = data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures[i];
                sgn_idx++;
            }
        }

        data->m_attribEventTrack->m_eventTracks[2].m_trackCount--;

        delete[] data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures;

        data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures = new_signatures;
    }

    std::vector<NodeDef*> nodes = morpheme_connect.nmb.GetNodesByAnimReference(data->m_attribSourceAnim->m_animIdx);

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] != this->m_nodeSource)
        {
            NodeData104* node_data = (NodeData104*)nodes[i]->node_data;

            node_data->m_attribEventTrack->m_eventTracks[0] = data->m_attribEventTrack->m_eventTracks[0];
            node_data->m_attribEventTrack->m_eventTracks[1] = data->m_attribEventTrack->m_eventTracks[1];
            node_data->m_attribEventTrack->m_eventTracks[2] = data->m_attribEventTrack->m_eventTracks[2];
        }
    }

    this->ReloadTracks();

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted track %d (%s) (node=%d)\n", delete_signature, delete_name, this->m_nodeSource->m_nodeID);
}

void EventTrackEditor::AddEvent(int track_idx, EventTrack::Event event)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    if (track->m_numEvents == 0)
    {
        track->m_source->m_data->m_numEvents++;
        track->m_source->m_data->m_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart / this->m_frameMax), MathHelper::FrameToTime(event.m_duration / this->m_frameMax), event.m_value };
        
        this->ReloadTracks();

        Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added event to track %d (%.3f, %.3f, %d) (node=%d)\n", track->m_signature, MathHelper::FrameToTime(event.m_frameStart) / MathHelper::FrameToTime(this->m_frameMax), MathHelper::FrameToTime(event.m_duration) / MathHelper::FrameToTime(this->m_frameMax), event.m_value, this->m_nodeSource->m_nodeID);

        return;
    }

    MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->m_source->m_data->m_numEvents + 1];

    for (size_t i = 0; i < track->m_source->m_data->m_numEvents; i++)
        new_src_events[i] = track->m_source->m_data->m_events[i];

    new_src_events[track->m_source->m_data->m_numEvents] = MorphemeBundle_EventTrack::BundleData_EventTrack::Event{ MathHelper::FrameToTime(event.m_frameStart) / MathHelper::FrameToTime(this->m_frameMax), MathHelper::FrameToTime(event.m_duration) / MathHelper::FrameToTime(this->m_frameMax), event.m_value};
    track->m_source->m_data->m_numEvents++;

    delete[] track->m_source->m_data->m_events;
    track->m_source->m_data->m_events = new_src_events;

    this->ReloadTracks();

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Added event to track %d (%.3f, %.3f, %d) (node=%d)\n", track->m_signature, MathHelper::FrameToTime(event.m_frameStart), MathHelper::FrameToTime(event.m_duration), event.m_value, this->m_nodeSource->m_nodeID);
}

void EventTrackEditor::DeleteEvent(int track_idx, int event_idx)
{
    EventTrack* track = &this->m_eventTracks[track_idx];

    if (track->m_numEvents > 1)
    {
        MorphemeBundle_EventTrack::BundleData_EventTrack::Event* new_src_events = new MorphemeBundle_EventTrack::BundleData_EventTrack::Event[track->m_source->m_data->m_numEvents - 1];

        int new_event_idx = 0;
        for (size_t i = 0; i < track->m_source->m_data->m_numEvents; i++)
        {
            if (i != event_idx)
            {
                new_src_events[new_event_idx] = track->m_source->m_data->m_events[i];
                new_event_idx++;
            }
        }

        track->m_source->m_data->m_numEvents--;

        delete[] track->m_source->m_data->m_events;

        track->m_source->m_data->m_events = new_src_events;

        Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d from Track %d (node=%d)\n", event_idx, track->m_signature, this->m_nodeSource->m_nodeID);

        this->ReloadTracks();

        return;
    }

    track->m_source->m_data->m_numEvents--;

    delete[] track->m_source->m_data->m_events;

    this->ReloadTracks();

    Debug::DebuggerMessage(Debug::LVL_DEBUG, "Deleted event %d from Track %d (node=%d)\n", event_idx, track->m_signature, this->m_nodeSource->m_nodeID);
}

void EventTrackEditor::ReloadTracks()
{
    this->Clear();

    if ((morpheme_connect.nmb.m_init == true) && (morpheme_connect.m_eventTrackEditorFlags.m_targetAnimIdx != -1))
    {
        bool found = false;

        NodeData104* node_data = (NodeData104*)this->m_nodeSource->node_data;

        if (node_data != NULL)
        {
            for (int i = 0; i < node_data->m_attribEventTrack->m_eventTracks[0].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = morpheme_connect.nmb.GetEventTrackBundle(node_data->m_attribEventTrack->m_eventTracks[0].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), true));
            }

            for (int i = 0; i < node_data->m_attribEventTrack->m_eventTracks[1].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = morpheme_connect.nmb.GetEventTrackBundle(node_data->m_attribEventTrack->m_eventTracks[1].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), false));
            }

            for (int i = 0; i < node_data->m_attribEventTrack->m_eventTracks[2].m_trackCount; i++)
            {
                MorphemeBundle_EventTrack* event_tracks = morpheme_connect.nmb.GetEventTrackBundle(node_data->m_attribEventTrack->m_eventTracks[2].m_trackSignatures[i]);

                if (event_tracks)
                    this->m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, MathHelper::FrameToTime(this->m_frameMax), false));
            }
        }
    }
}

EventTrackEditor::EventTrackEditor() {}

void EventTrackEditor::Clear()
{
    this->m_eventTracks.clear();
}