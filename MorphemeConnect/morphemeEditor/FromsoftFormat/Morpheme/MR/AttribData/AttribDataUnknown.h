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

        int GetMemoryRequirements();

    private:
        std::vector<BYTE> m_data;
    };
}