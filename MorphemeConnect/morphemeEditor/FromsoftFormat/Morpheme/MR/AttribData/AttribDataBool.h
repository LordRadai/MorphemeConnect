#pragma once
#include "AttribData.h"

namespace MR
{
	class AttribDataBool : public AttribData
	{
	public:
		AttribDataBool();
		AttribDataBool(BYTE* pData);
		~AttribDataBool();

		int GetMemoryRequirements();

		bool Get();
	private:
		bool m_value;
	};
}