#include "NodeAttribBase.h"

struct EventTrackList {
    int m_trackCount;
    int padding;
    std::vector<int> m_trackSignatures;
    std::vector<int> m_trackSize;
};

class NodeAttribSourceEventTrack : public NodeAttribBase
{
public:
    EventTrackList m_eventTracks[3];

    NodeAttribSourceEventTrack() {}
    NodeAttribSourceEventTrack(BYTE* data);
};