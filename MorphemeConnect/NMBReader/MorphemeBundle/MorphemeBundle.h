#pragma once
#include "MorphemeBundle_Base.h"

class MorphemeBundle : public MorphemeBundle_Base
{
public:
	byte* m_data;				//Pointer in which memory will be allocated

	MorphemeBundle();
	MorphemeBundle(ifstream* pFile);

	void GenerateBundle();
	int CalculateBundleSize();
};