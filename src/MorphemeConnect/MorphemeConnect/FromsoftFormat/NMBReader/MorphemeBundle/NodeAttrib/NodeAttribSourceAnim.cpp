#include "NodeAttribSourceAnim.h"

NodeAttribSourceAnim::NodeAttribSourceAnim(BYTE* data) : NodeAttribBase(data)
{
    if (this->m_type != ATTRIB_TYPE_SOURCE_ANIM)
        Debug::Panic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_type, ATTRIB_TYPE_SOURCE_ANIM);

    this->m_pAnimFile = *(UINT64*)(data + 0x10);
    this->m_pVar8 = *(UINT64*)(data + 0x18);
    this->m_fVar10 = *(float*)(data + 0x20);
    this->m_fVar14 = *(float*)(data + 0x24);
    this->m_iVar18 = *(UINT64*)(data + 0x28);
    this->m_iVar20 = *(UINT64*)(data + 0x30);
    this->m_fVar28 = *(float*)(data + 0x38);
    this->m_fVar2C = *(float*)(data + 0x3C);
    this->m_fVar30 = *(float*)(data + 0x40);
    this->m_fVar34 = *(float*)(data + 0x44);
    this->m_iVar38 = *(UINT64*)(data + 0x48);
    this->m_iVar40 = *(UINT64*)(data + 0x50);
    this->m_fVar48 = *(float*)(data + 0x58);
    this->m_fVar4C = *(float*)(data + 0x5C);
    this->m_pVar50 = *(UINT64*)(data + 0x60);
    this->m_pad0 = *(int*)(data + 0x68);
    this->m_iVar5C = *(int*)(data + 0x6C);
    this->m_pad1 = *(int*)(data + 0x70);
    this->m_animIdx = *(int*)(data + 0x74);
    this->m_iVar68 = *(int*)(data + 0x78);
    this->m_bVar6C = *(BYTE*)(data + 0x7C);
    this->m_bVar6D = *(BYTE*)(data + 0x7D);
    this->m_bVar6E = *(BYTE*)(data + 0x7E);
    this->m_pad2 = *(BYTE*)(data + 0x7F);
    this->m_fVar70 = *(float*)(data + 0x80);
    this->m_trackLen = *(float*)(data + 0x84);
    this->m_animLen = *(float*)(data + 0x88);
    this->m_fVar7C = *(float*)(data + 0x8C);
    this->m_bVar80 = *(BYTE*)(data + 0x90);

    for (size_t i = 0; i < 15; i++)
        this->m_pad3[i] = *(BYTE*)(data + 0x91 + (BYTE)i);
}