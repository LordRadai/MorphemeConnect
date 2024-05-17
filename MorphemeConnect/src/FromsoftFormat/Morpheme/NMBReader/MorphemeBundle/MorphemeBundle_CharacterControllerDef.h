#pragma once
#include "MorphemeBundle.h"

namespace NMB
{
	class MorphemeBundle_CharacterControllerDef : public MorphemeBundle_Base
	{
	public:
		MR::CharacterController* m_data;

		MorphemeBundle_CharacterControllerDef();
		MorphemeBundle_CharacterControllerDef(MorphemeBundle* bundle);
		~MorphemeBundle_CharacterControllerDef();

		void WriteBinary(ofstream* out);
		UINT64 GetMemoryRequirements();
	};
}