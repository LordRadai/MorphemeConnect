#pragma once
#include "MorphemeBundle.h"

class MorphemeBundle_Header : public MorphemeBundle_Base
{
public:
	struct BundleData_Header
	{
		INT64 m_iVar0;
		INT64 m_iVar1;
		INT64 m_iVar2;
		INT64 m_iVar3;
	};

	BundleData_Header* m_data;

	MorphemeBundle_Header();
	MorphemeBundle_Header(MorphemeBundle* bundle);
	
	void WriteBinary(ofstream* out, UINT64 alignment);
	int CalculateBundleSize();
};