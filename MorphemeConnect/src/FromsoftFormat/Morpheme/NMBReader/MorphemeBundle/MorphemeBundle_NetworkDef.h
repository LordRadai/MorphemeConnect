#pragma once
#include "MorphemeBundle.h"
#include "NodeAttrib/NodeAttribUnknown.h"
#include "NodeAttrib/NodeAttribBool.h"
#include "NodeAttrib/NodeAttribSourceAnim.h"
#include "NodeAttrib/NodeAttribSourceEventTrack.h"

using namespace Morpheme4;

class MorphemeBundle_NetworkDef : public MorphemeBundle_Base
{
public:
    NetworkDef* m_data;

    MorphemeBundle_NetworkDef();
    MorphemeBundle_NetworkDef(MorphemeBundle* bundle);
    ~MorphemeBundle_NetworkDef();

    void WriteBinary(ofstream* out);
    int CalculateBundleSize();
};