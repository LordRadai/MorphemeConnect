#include "EventTrackEditor.h"
#include "../Application/Application.h"

int EventTrackEditor::GetFrameMin() const
{
    return mFrameMin;
}
int EventTrackEditor::GetFrameMax() const
{
    return mFrameMax;
}
int EventTrackEditor::GetTrackCount() const { return (int)m_eventTracks.size(); }

void EventTrackEditor::BeginEdit(int idx) {}
void EventTrackEditor::EndEdit() {}

const char* EventTrackEditor::GetTrackName(int idx) const { return m_eventTracks[idx].m_name; }
std::string EventTrackEditor::GetEventLabel(int track_idx, int event_idx) const
{
    return std::to_string(this->m_eventTracks[track_idx].m_event[event_idx].m_value);
}

void EventTrackEditor::AddTrack(bool discrete)
{
    EventTrack::Event event[1];

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
        m_eventTracks.push_back(EventTrack(signature, 1, 0, &event[0], "DiscreteTrack", true));
    else
        m_eventTracks.push_back(EventTrack(signature, 1, 0, &event[0], "DurationTrack", true));
};

void EventTrackEditor::DelTrack(int index) { m_eventTracks.erase(m_eventTracks.begin() + index); }
void EventTrackEditor::DuplicateTrack(int index) { m_eventTracks.push_back(m_eventTracks[index]); }

EventTrackEditor::EventTrackEditor() {}

void EventTrackEditor::Clear()
{
    this->m_eventTracks.clear();
}