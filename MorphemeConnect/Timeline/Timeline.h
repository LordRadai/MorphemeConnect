#pragma once
#include "../framework.h"
#include "../extern.h"
#include "../MathHelper/MathHelper.h"
#include "../NMBReader/NMBReader.h"
#include <math.h>
#include <vector>
#include <algorithm>

#define TRACK_MAX 50

struct TimeActDef
{
    int group_id;
    const char* group_name;
    int tae_id;
    char tae_name[256];
    int arg_count;
    std::vector<byte> arg_type;
    
    struct ArgName
    {
        char name[256];
    };

    std::vector<ArgName> arg_names;
};

struct TimeActTrack
{
    int tae_count;
    int group_id;
    int tae_id;
    float startTime;
    float endTime;
    char trackName[50];
    int parentId;
    int childId;
    uint64_t args;
    TimeActDef tae_def;
};

struct TimeActTrackList
{
    uint64_t parent;
    int count, countSub;
    TimeActTrack* tracks;
    TimeActTrack* tracksSub;

    int getSubTrackcount();
};

struct MorphemeEventTrack
{
    int eventCount;
    int eventId;
    int value;
    float startTime;
    float duration;
    const char* trackName;
    int parentId;
    int childId;
    bool is_discrete;
};

struct MorphemeEventTrackList
{
    NodeDataContent_EventTrack* parent;
    int count_discrete = 0;
    int count_discreteSub = 0;
    int count_unk = 0;
    int count_unkSub = 0;
    int count_timed = 0;
    int count_timedSub = 0;
    MorphemeEventTrack* tracks_discrete;
    MorphemeEventTrack* tracks_discreteSub;
    MorphemeEventTrack* tracks_unk;
    MorphemeEventTrack* tracks_unkSub;
    MorphemeEventTrack* tracks_timed;
    MorphemeEventTrack* tracks_timedSub;

    MorphemeEventTrackList() {}
    MorphemeEventTrackList(NodeDataContent_EventTrack* src);
    void ClearTrackList();
    void SaveEventTracks();
    int GetSubTrackcount_discrete();
    int GetSubTrackcount_unk();
    int GetSubTrackcount();
    void AllocSubTracks();
};

struct RampEdit : public ImCurveEdit::Delegate
{
    RampEdit()
    {
        mPts[0][0] = ImVec2(-10.f, 0);
        mPts[0][1] = ImVec2(20.f, 0.6f);
        mPts[0][2] = ImVec2(25.f, 0.2f);
        mPts[0][3] = ImVec2(70.f, 0.4f);
        mPts[0][4] = ImVec2(120.f, 1.f);
        mPointCount[0] = 5;

        mPts[1][0] = ImVec2(-50.f, 0.2f);
        mPts[1][1] = ImVec2(33.f, 0.7f);
        mPts[1][2] = ImVec2(80.f, 0.2f);
        mPts[1][3] = ImVec2(82.f, 0.8f);
        mPointCount[1] = 4;


        mPts[2][0] = ImVec2(40.f, 0);
        mPts[2][1] = ImVec2(60.f, 0.1f);
        mPts[2][2] = ImVec2(90.f, 0.82f);
        mPts[2][3] = ImVec2(150.f, 0.24f);
        mPts[2][4] = ImVec2(200.f, 0.34f);
        mPts[2][5] = ImVec2(250.f, 0.12f);
        mPointCount[2] = 6;
        mbVisible[0] = mbVisible[1] = mbVisible[2] = true;
        mMax = ImVec2(1.f, 1.f);
        mMin = ImVec2(0.f, 0.f);
    }
    size_t GetCurveCount()
    {
        return 3;
    }

    bool IsVisible(size_t curveIndex)
    {
        return mbVisible[curveIndex];
    }
    size_t GetPointCount(size_t curveIndex)
    {
        return mPointCount[curveIndex];
    }

    uint32_t GetCurveColor(size_t curveIndex)
    {
        uint32_t cols[] = { 0xFF0000FF, 0xFF00FF00, 0xFFFF0000 };
        return cols[curveIndex];
    }
    ImVec2* GetPoints(size_t curveIndex)
    {
        return mPts[curveIndex];
    }
    virtual ImCurveEdit::CurveType GetCurveType(size_t curveIndex) const { return ImCurveEdit::CurveSmooth; }
    virtual int EditPoint(size_t curveIndex, int pointIndex, ImVec2 value)
    {
        mPts[curveIndex][pointIndex] = ImVec2(value.x, value.y);
        SortValues(curveIndex);
        for (size_t i = 0; i < GetPointCount(curveIndex); i++)
        {
            if (mPts[curveIndex][i].x == value.x)
                return (int)i;
        }
        return pointIndex;
    }
    virtual void AddPoint(size_t curveIndex, ImVec2 value)
    {
        if (mPointCount[curveIndex] >= 8)
            return;
        mPts[curveIndex][mPointCount[curveIndex]++] = value;
        SortValues(curveIndex);
    }
    virtual ImVec2& GetMax() { return mMax; }
    virtual ImVec2& GetMin() { return mMin; }
    virtual unsigned int GetBackgroundColor() { return 0; }
    ImVec2 mPts[3][8];
    size_t mPointCount[3];
    bool mbVisible[3];
    ImVec2 mMin;
    ImVec2 mMax;
private:
    void SortValues(size_t curveIndex)
    {
        auto b = std::begin(mPts[curveIndex]);
        auto e = std::begin(mPts[curveIndex]) + GetPointCount(curveIndex);
        std::sort(b, e, [](ImVec2 a, ImVec2 b) { return a.x < b.x; });
    }
};

struct EventTrackEditor : public ImSequencer::SequenceInterface
{
    const char* trackNames[TRACK_MAX];

    virtual int GetFrameMin() const {
        return mFrameMin;
    }
    virtual int GetFrameMax() const {
        return mFrameMax;
    }
    virtual int GetItemCount() const { return (int)myItems.size(); }

    virtual int GetItemTypeCount() const { return sizeof(trackNames) / sizeof(char*); }
    virtual const char* GetItemTypeName(int typeIndex) const { return trackNames[typeIndex]; }
    virtual const char* GetItemLabel(int index, int eventId) const
    {
        static char tmps[512];
        snprintf(tmps, 512, "[%d] %s", eventId, myItems[index].trackName);
        return tmps;
    }

    virtual void Get(int index, int** start, int** end, int* type, int* eventId, int** value, bool* isDiscrete, int* isActive, unsigned int* color)
    {
        EventTrack& item = myItems[index];
        if (color)
            *color = 0xFFAA8080; // same color for everyone, return color based on type
        if (start)
            *start = &item.mFrameStart;
        if (end)
            *end = &item.mFrameEnd;
        if (type)
            *type = item.id;
        if (eventId)
            *eventId = item.eventId;
        if (value)
            *value = &item.value;
        if (isDiscrete)
            *isDiscrete = item.isDiscrete;
        if (isActive)
            *isActive = item.eventCount;
    }

    virtual void Add(int type) { myItems.push_back(EventTrack{type, 80, 0, 10, 0, 0, "Track", false}); };
    virtual void Del(int index) { myItems.erase(myItems.begin() + index); }
    virtual void Duplicate(int index) { myItems.push_back(myItems[index]); }

    void AddTimeActTrack(int id, TimeActTrack* time_act_track, float multiplier);
    void AddMorphemeEventTrack(int id, MorphemeEventTrack* event_track, float multiplier);
    void Clear();
    void LoadTrackName(int id, MorphemeEventTrack event_track);

    virtual size_t GetCustomHeight(int index) { return myItems[index].mExpanded ? 300 : 0; }

    // my datas
    EventTrackEditor() : mFrameMin(0), mFrameMax(0) {}
    int mFrameMin, mFrameMax;

    struct EventTrack
    {
        int id;
        int eventId;
        int mFrameStart, mFrameEnd;
        int value;
        int eventCount;
        const char* trackName;
        bool isDiscrete;
        bool mExpanded;
        MorphemeEventTrack* morpheme_track;
        TimeActTrack* time_act_track;

        void SaveEventTrackData(MorphemeEventTrack* event_track, float multiplier);
        void SaveTaeTrackData(TimeActTrack* tae_track, float multiplier);
    };

    std::vector<EventTrack> myItems;
    RampEdit rampEdit;

    virtual void DoubleClick(int index) {
        if (myItems[index].mExpanded)
        {
            myItems[index].mExpanded = false;
            return;
        }
        for (auto& item : myItems)
            item.mExpanded = false;
        myItems[index].mExpanded = !myItems[index].mExpanded;
    }

    virtual void CustomDrawCompact(int index, ImDrawList* draw_list, const ImRect& rc, const ImRect& clippingRect)
    {
        rampEdit.mMax = ImVec2(float(mFrameMax), 1.f);
        rampEdit.mMin = ImVec2(float(mFrameMin), 0.f);
        draw_list->PushClipRect(clippingRect.Min, clippingRect.Max, true);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < rampEdit.mPointCount[i]; j++)
            {
                float p = rampEdit.mPts[i][j].x;
                if (p < myItems[index].mFrameStart || p > myItems[index].mFrameEnd)
                    continue;
                float r = (p - mFrameMin) / float(mFrameMax - mFrameMin);
                float x = ImLerp(rc.Min.x, rc.Max.x, r);
                draw_list->AddLine(ImVec2(x, rc.Min.y + 6), ImVec2(x, rc.Max.y - 4), 0xAA000000, 4.f);
            }
        }
        draw_list->PopClipRect();
    }
};