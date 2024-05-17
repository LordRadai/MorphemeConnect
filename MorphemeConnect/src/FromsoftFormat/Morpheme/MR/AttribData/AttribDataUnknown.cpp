#include "AttribDataUnknown.h"

using namespace MR;

AttribDataUnknown::AttribDataUnknown()
{
}

AttribDataUnknown::AttribDataUnknown(BYTE* pData, int size) : AttribData(pData)
{
	this->m_data.reserve(size);
	for (size_t i = 0; i < size; i++)
		this->m_data.push_back(pData[i]);
}

AttribDataUnknown::~AttribDataUnknown()
{
}