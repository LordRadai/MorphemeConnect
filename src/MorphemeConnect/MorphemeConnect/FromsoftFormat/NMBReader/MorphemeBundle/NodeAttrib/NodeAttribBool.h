#include "NodeAttribBase.h"

class NodeAttribBool : public NodeAttribBase
{
public:
    bool m_bool;

    NodeAttribBool() {}
    NodeAttribBool(BYTE* data);
};