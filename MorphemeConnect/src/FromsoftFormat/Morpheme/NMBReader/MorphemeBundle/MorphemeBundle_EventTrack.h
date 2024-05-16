#pragma once
#include "MorphemeBundle.h"

class MorphemeBundle_EventTrack : public MorphemeBundle_Base
{
public:
	MR::EventTrack* m_data;

	MorphemeBundle_EventTrack();
	MorphemeBundle_EventTrack(int signature, bool is_duration, int index, char* trackName, int userData, int channelID);
	MorphemeBundle_EventTrack(MorphemeBundle* bundle);
	~MorphemeBundle_EventTrack();

	void WriteBinary(ofstream* out);
	UINT64 GetMemoryRequirements();
};