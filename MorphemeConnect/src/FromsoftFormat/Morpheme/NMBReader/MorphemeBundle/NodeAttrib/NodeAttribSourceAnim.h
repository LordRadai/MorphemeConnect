#include "NodeAttribBase.h"

class NodeAttribSourceAnim : public NodeAttribBase
{
public:
    UINT64 m_pAnimFile;     //The runtime module will put the referenced NSA pointer here
    UINT64 m_pVar8;
    float m_fVar10;
    float m_fVar14;
    UINT64 m_iVar18;
    UINT64 m_iVar20;
    float m_fVar28;
    float m_fVar2C;
    float m_fVar30;
    float m_fVar34;
    UINT64 m_iVar38;
    UINT64 m_iVar40;
    float m_fVar48;
    float m_fVar4C;
    UINT64 m_pVar50;
    int m_pad0;
    int m_iVar5C;
    int m_pad1;
    int m_animIdx;      //Used to access the FileNameLookupTable and get the NSA file pointer
    int m_iVar68;
    BYTE m_bVar6C;
    BYTE m_bVar6D;
    BYTE m_bVar6E;
    BYTE m_pad2;
    float m_clipStart;
    float m_clipEnd;
    float m_animLen;
    float m_fVar7C;
    BYTE m_bVar80;
    BYTE m_pad3[15];

    NodeAttribSourceAnim() {}
    NodeAttribSourceAnim(BYTE* data);
};