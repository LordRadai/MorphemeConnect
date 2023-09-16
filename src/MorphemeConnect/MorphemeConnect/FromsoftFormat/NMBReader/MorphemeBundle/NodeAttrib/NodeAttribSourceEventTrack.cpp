#include "NodeAttribSourceEventTrack.h"

NodeAttribSourceEventTrack::NodeAttribSourceEventTrack(BYTE* data) : NodeAttribBase(data)
{
    if (this->m_type != ATTRIB_TYPE_SOURCE_EVENT_TRACKS)
        Debug::Panic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_type, ATTRIB_TYPE_SOURCE_EVENT_TRACKS);

    this->m_eventTracks[0].m_trackCount = *(int*)(data + 0x10);
    this->m_eventTracks[0].padding = *(int*)(data + 0x14);

    if (this->m_eventTracks[0].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        int* size_list = (int*)(*(UINT64*)(data + 0x20) + data);

        this->m_eventTracks[0].m_trackSignatures.reserve(this->m_eventTracks[0].m_trackCount);
        this->m_eventTracks[0].m_trackSize.reserve(this->m_eventTracks[0].m_trackCount);

        for (size_t i = 0; i < this->m_eventTracks[0].m_trackCount; i++)
        {
            this->m_eventTracks[0].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[0].m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_eventTracks[1].m_trackCount = *(int*)(data + 0x10 + 0x18);
    this->m_eventTracks[1].padding = *(int*)(data + 0x14 + 0x18);

    if (this->m_eventTracks[1].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18 + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        this->m_eventTracks[1].m_trackSignatures.reserve(this->m_eventTracks[1].m_trackCount);
        this->m_eventTracks[1].m_trackSize.reserve(this->m_eventTracks[1].m_trackCount);
        int* size_list = (int*)(*(UINT64*)(data + 0x20 + 0x18) + data);

        for (size_t i = 0; i < this->m_eventTracks[1].m_trackCount; i++)
        {
            this->m_eventTracks[1].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[1].m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_eventTracks[2].m_trackCount = *(int*)(data + 0x10 + 2 * 0x18);
    this->m_eventTracks[2].padding = *(int*)(data + 0x14 + 2 * 0x18);

    if (this->m_eventTracks[2].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18 + 2 * 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        this->m_eventTracks[2].m_trackSignatures.reserve(this->m_eventTracks[2].m_trackCount);
        this->m_eventTracks[2].m_trackSize.reserve(this->m_eventTracks[2].m_trackCount);
        int* size_list = (int*)(*(UINT64*)(data + 0x20 + 2 * 0x18) + data);

        for (size_t i = 0; i < this->m_eventTracks[2].m_trackCount; i++)
        {
            this->m_eventTracks[2].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[2].m_trackSize.push_back(size_list[i]);
        }
    }
}
