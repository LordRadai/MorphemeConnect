#include "NodeAttribBase.h"

class NodeAttribUnknown : public NodeAttribBase
{
public:
    BYTE* m_content;

    NodeAttribUnknown() {}
    NodeAttribUnknown(BYTE* data, int size);
    void GenerateBinary(std::ofstream* out) override;
};