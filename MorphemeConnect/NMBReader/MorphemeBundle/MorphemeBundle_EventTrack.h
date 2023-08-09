#pragma once
#include "MorphemeBundle.h"

struct MorphemeBundle_EventTrack
{
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
		const char* m_trackName;
		int m_eventId;
		int m_iVar14;
		Event* m_events;
	};

	UINT m_magic[2];			//They must always be 24 and 10 in order
	eBundleType m_bundleType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	BundleData_EventTrack* m_data;

	MorphemeBundle_EventTrack();
	MorphemeBundle_EventTrack(MorphemeBundle* bundle);
};