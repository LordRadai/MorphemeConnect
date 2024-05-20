#include "AttribDataUnknown.h"

using namespace MR;

AttribDataUnknown::AttribDataUnknown()
{
}

AttribDataUnknown::AttribDataUnknown(BYTE* pData, int size) : AttribData(pData)
{
	if (size == 0)
		return;

	this->m_data.reserve(size - 16);
	for (size_t i = 0; i < size - 16; i++)
		this->m_data.push_back(pData[i] + 0x10);
}

AttribDataUnknown::~AttribDataUnknown()
{
}

int AttribDataUnknown::GetMemoryRequirements()
{
	return 16 + this->m_data.size();
}