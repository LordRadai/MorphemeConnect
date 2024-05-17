#pragma once
#include <SimpleMath.h>
#include "MorphemeBundle.h"

namespace NMB
{
	class MorphemeBundle_Rig : public MorphemeBundle_Base
	{
	public:
		MR::Rig* m_data;

		MorphemeBundle_Rig();
		MorphemeBundle_Rig(MorphemeBundle* bundle);
		~MorphemeBundle_Rig();

		void WriteBinary(ofstream* out);
		UINT64 GetMemoryRequirements();
	};
}