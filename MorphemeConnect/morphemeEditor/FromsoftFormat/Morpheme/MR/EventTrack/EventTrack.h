#pragma once
#include "../Common/Common.h"

namespace MR
{
	class EventTrack
	{
	public:
		class Event
		{
		public:
			float m_start;
			float m_duration;
			int m_userData;

			Event();
			Event(BYTE* pData);
			Event(float start, float duration, int userData);
			~Event();
		};

		EventTrack();
		EventTrack(BYTE* pData);
		EventTrack(int index, char* trackName, int userData, int channelID);
		~EventTrack();

		std::string GetTrackName();
		int GetIndex();
		int GetChannelID();
		int GetNumEvents();
		int GetUserData();
		Event* GetEvent(int idx);

		void SetUserData(int userData);

		int GetMemoryRequirements();
		void AddEvent(float start, float end, int userData);
		void DeleteEvent(int idx);

	private:
		int m_numEvents;
		int m_index;
		std::string m_trackName;
		int m_userData;
		int m_channelId;
		std::vector<Event> m_events;
	};
}