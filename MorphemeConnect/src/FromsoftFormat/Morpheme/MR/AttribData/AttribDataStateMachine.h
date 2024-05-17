#pragma once
#include "AttribData.h"

namespace MR
{
	struct SMChildNodeInfo
	{
		short m_id;
		short m_sVar0;
		short m_transitConditionCount;
		UINT64 m_pVar3;
		short m_sVar4;
		short m_sVar5;
		UINT64 m_pVar6;
	};

	class AttribDataStateMachine
	{
	public:
		AttribDataStateMachine();
		AttribDataStateMachine(BYTE* pData);
		~AttribDataStateMachine();

		int GetMemoryRequirements();
	private:
		int m_sVar0;
		int m_totalChildCount;
		bool m_bVar1;
		short m_childTransitConditionCount;

	};
}