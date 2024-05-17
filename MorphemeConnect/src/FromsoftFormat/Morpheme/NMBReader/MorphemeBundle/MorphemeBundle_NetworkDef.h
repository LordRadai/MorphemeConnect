#pragma once
#include "MorphemeBundle.h"

namespace NMB
{
    class MorphemeBundle_NetworkDef : public MorphemeBundle_Base
    {
    public:
        NetworkDef* m_data;

        MorphemeBundle_NetworkDef();
        MorphemeBundle_NetworkDef(MorphemeBundle* bundle);
        ~MorphemeBundle_NetworkDef();

        void WriteBinary(ofstream* out);
        UINT64 GetMemoryRequirements();
    };
}