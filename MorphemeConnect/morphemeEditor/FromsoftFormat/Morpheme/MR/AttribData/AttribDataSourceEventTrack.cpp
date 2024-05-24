#include "AttribDataSourceEventTrack.h"

using namespace MR;

int EventTrackSet::GetMemoryRequirements()
{
    return 24 + this->m_trackCount * 8 + this->m_trackCount * 4;
}

void EventTrackSet::DeleteEventTrack(int idx)
{
    this->m_trackCount--;
    this->m_trackSignatures.erase(this->m_trackSignatures.begin() + idx);
    this->m_trackSize.erase(this->m_trackSize.begin() + idx);
}

void EventTrackSet::AddEventTrack(int signature)
{
    this->m_trackCount++;
    this->m_trackSignatures.push_back(signature);
    this->m_trackSize.push_back(0);
}

AttribDataSourceEventTrack::AttribDataSourceEventTrack()
{
}

AttribDataSourceEventTrack::AttribDataSourceEventTrack(BYTE* pData) : AttribData(pData)
{
    if (this->m_attribTypeID != ATTRIB_TYPE_SOURCE_EVENT_TRACKS)
        RDebug::SystemPanic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_attribTypeID, ATTRIB_TYPE_SOURCE_EVENT_TRACKS);

    this->m_discreteEventTrackSet.m_trackCount = *(int*)(pData + 0x10);

    if (this->m_discreteEventTrackSet.m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(pData + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + pData);

        int* size_list = (int*)(*(UINT64*)(pData + 0x20) + pData);

        this->m_discreteEventTrackSet.m_trackSignatures.reserve(this->m_discreteEventTrackSet.m_trackCount);
        this->m_discreteEventTrackSet.m_trackSize.reserve(this->m_discreteEventTrackSet.m_trackCount);

        for (size_t i = 0; i < this->m_discreteEventTrackSet.m_trackCount; i++)
        {
            this->m_discreteEventTrackSet.m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_discreteEventTrackSet.m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_curveEventTrackSet.m_trackCount = *(int*)(pData + 0x10 + 0x18);

    if (this->m_curveEventTrackSet.m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(pData + 0x18 + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + pData);

        this->m_curveEventTrackSet.m_trackSignatures.reserve(this->m_curveEventTrackSet.m_trackCount);
        this->m_curveEventTrackSet.m_trackSize.reserve(this->m_curveEventTrackSet.m_trackCount);
        int* size_list = (int*)(*(UINT64*)(pData + 0x20 + 0x18) + pData);

        for (size_t i = 0; i < this->m_curveEventTrackSet.m_trackCount; i++)
        {
            this->m_curveEventTrackSet.m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_curveEventTrackSet.m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_durationEventTrackSet.m_trackCount = *(int*)(pData + 0x10 + 2 * 0x18);

    if (this->m_durationEventTrackSet.m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(pData + 0x18 + 2 * 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + pData);

        this->m_durationEventTrackSet.m_trackSignatures.reserve(this->m_durationEventTrackSet.m_trackCount);
        this->m_durationEventTrackSet.m_trackSize.reserve(this->m_durationEventTrackSet.m_trackCount);
        int* size_list = (int*)(*(UINT64*)(pData + 0x20 + 2 * 0x18) + pData);

        for (size_t i = 0; i < this->m_durationEventTrackSet.m_trackCount; i++)
        {
            this->m_durationEventTrackSet.m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_durationEventTrackSet.m_trackSize.push_back(size_list[i]);
        }
    }
}

AttribDataSourceEventTrack::~AttribDataSourceEventTrack()
{
}

int AttribDataSourceEventTrack::GetMemoryRequirements()
{
    return 16 + this->m_discreteEventTrackSet.GetMemoryRequirements() + this->m_curveEventTrackSet.GetMemoryRequirements() + this->m_durationEventTrackSet.GetMemoryRequirements();
}

EventTrackSet AttribDataSourceEventTrack::GetDiscreteEventTrackSet()
{
    return this->m_discreteEventTrackSet;
}

EventTrackSet AttribDataSourceEventTrack::GetCurveEventTrackSet()
{
    return this->m_curveEventTrackSet;
}

EventTrackSet AttribDataSourceEventTrack::GetDurationEventTrackSet()
{
    return this->m_durationEventTrackSet;
}

void AttribDataSourceEventTrack::SetDiscreteEventTrackSet(EventTrackSet set)
{
    this->m_discreteEventTrackSet = set;
}

void AttribDataSourceEventTrack::SetCurveEventTrackSet(EventTrackSet set)
{
    this->m_curveEventTrackSet = set;
}

void AttribDataSourceEventTrack::SetDurationEventTrackSet(EventTrackSet set)
{
    this->m_durationEventTrackSet = set;
}