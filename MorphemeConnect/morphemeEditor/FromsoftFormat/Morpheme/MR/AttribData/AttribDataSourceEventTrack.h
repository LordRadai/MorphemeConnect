#pragma once
#include "AttribData.h"

struct EventTrackSet
{
	int m_trackCount;
	std::vector<int> m_trackSignatures;
	std::vector<int> m_trackSize;

	int GetMemoryRequirements();

	void DeleteEventTrack(int idx);
	void AddEventTrack(int signature);
};

namespace MR
{
	class AttribDataSourceEventTrack : public AttribData
	{
	public:
		AttribDataSourceEventTrack();
		AttribDataSourceEventTrack(BYTE* pData);
		~AttribDataSourceEventTrack();

		int GetMemoryRequirements();

		EventTrackSet GetDiscreteEventTrackSet();
		EventTrackSet GetCurveEventTrackSet();
		EventTrackSet GetDurationEventTrackSet();

		void SetDiscreteEventTrackSet(EventTrackSet set);
		void SetCurveEventTrackSet(EventTrackSet set);
		void SetDurationEventTrackSet(EventTrackSet set);
	private:
		EventTrackSet m_discreteEventTrackSet;
		EventTrackSet m_curveEventTrackSet;
		EventTrackSet m_durationEventTrackSet;
	};
}