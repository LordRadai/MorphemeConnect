#pragma once
#include "MorphemeBundle_Base.h"

namespace NMB
{
	class MorphemeBundle : public MorphemeBundle_Base
	{
	public:
		BYTE* m_data;				//Pointer in which memory will be allocated

		MorphemeBundle();
		MorphemeBundle(ifstream* pFile);
		~MorphemeBundle();

		void WriteBinary(ofstream* out);
		UINT64 GetMemoryRequirements();
	};
}