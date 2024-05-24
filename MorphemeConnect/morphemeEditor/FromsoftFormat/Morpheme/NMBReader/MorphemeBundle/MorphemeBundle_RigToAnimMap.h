#pragma once
#include <SimpleMath.h>
#include "MorphemeBundle.h"

namespace NMB
{
	class MorphemeBundle_RigToAnimMap : public MorphemeBundle_Base
	{
	public:
		MR::RigToAnimMap* m_data;

		MorphemeBundle_RigToAnimMap();
		MorphemeBundle_RigToAnimMap(MorphemeBundle* bundle);
		~MorphemeBundle_RigToAnimMap();

		void WriteBinary(ofstream* out);
		UINT64 GetMemoryRequirements();
	};
}