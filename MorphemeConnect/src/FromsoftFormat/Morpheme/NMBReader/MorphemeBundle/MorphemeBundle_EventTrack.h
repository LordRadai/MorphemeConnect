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
		int m_index;
		char* m_trackName;
		int m_eventId;
		int m_channelId;
		std::vector<Event> m_events;
	};

	BundleData_EventTrack* m_data;

	MorphemeBundle_EventTrack();
	MorphemeBundle_EventTrack(MorphemeBundle* bundle);
	~MorphemeBundle_EventTrack();

	void WriteBinary(ofstream* out, UINT64 alignment);
	int CalculateBundleSize();
};