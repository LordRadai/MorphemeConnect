#pragma once
#include "MorphemeBundle.h"

class MorphemeBundle_EventTrack : public MorphemeBundle_Base
{
public:
	MR::EventTrack* m_data;

	MorphemeBundle_EventTrack();
	MorphemeBundle_EventTrack(MorphemeBundle* bundle);
	~MorphemeBundle_EventTrack();

	void WriteBinary(ofstream* out, UINT64 alignment);
	UINT64 GetMemoryRequirements();
};