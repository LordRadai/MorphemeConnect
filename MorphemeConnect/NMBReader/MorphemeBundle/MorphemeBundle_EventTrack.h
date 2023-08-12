#pragma once
#include "MorphemeBundle.h"

class MorphemeBundle_EventTrack : public MorphemeBundle_Base
{
public:
	struct BundleData_EventTrack
	{
		struct Event
		{
			float m_start;
			float m_duration;
			int m_value;
		};

		int m_numEvents;
		int m_iVar4;
		char* m_trackName;
		int m_eventId;
		int m_iVar14;
		Event* m_events;
	};

	BundleData_EventTrack* m_data;

	MorphemeBundle_EventTrack();
	MorphemeBundle_EventTrack(MorphemeBundle* bundle);

	void GenerateBundle();
	int CalculateBundleSize();
};