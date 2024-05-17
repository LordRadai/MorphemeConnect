#pragma once
#include "AttribData.h"

namespace MR
{
    class AttribDataUnknown : public AttribData
    {
    public:
        AttribDataUnknown();
        AttribDataUnknown(BYTE* pData, int size);
        ~AttribDataUnknown();

    private:
        std::vector<BYTE> m_data;
    };
}