#include "AttribDataSourceAnim.h"

using namespace MR;

AttribDataSourceAnim::AttribDataSourceAnim()
{
}

AttribDataSourceAnim::AttribDataSourceAnim(BYTE* pData) : AttribData(pData)
{
    if (this->m_attribTypeID != ATTRIB_TYPE_SOURCE_ANIM)
        RDebug::SystemPanic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_attribTypeID, ATTRIB_TYPE_SOURCE_ANIM);

    this->m_pAnimFile = *(UINT64*)(pData + 0x10);
    this->m_pVar8 = *(UINT64*)(pData + 0x18);
    this->m_fVar10 = *(float*)(pData + 0x20);
    this->m_fVar14 = *(float*)(pData + 0x24);
    this->m_iVar18 = *(UINT64*)(pData + 0x28);
    this->m_iVar20 = *(UINT64*)(pData + 0x30);
    this->m_fVar28 = *(float*)(pData + 0x38);
    this->m_fVar2C = *(float*)(pData + 0x3C);
    this->m_fVar30 = *(float*)(pData + 0x40);
    this->m_fVar34 = *(float*)(pData + 0x44);
    this->m_iVar38 = *(UINT64*)(pData + 0x48);
    this->m_iVar40 = *(UINT64*)(pData + 0x50);
    this->m_fVar48 = *(float*)(pData + 0x58);
    this->m_fVar4C = *(float*)(pData + 0x5C);
    this->m_pVar50 = *(UINT64*)(pData + 0x60);
    this->m_iVar5C = *(int*)(pData + 0x6C);
    this->m_animIdx = *(int*)(pData + 0x74);
    this->m_rigToAnimMapBundleID = *(int*)(pData + 0x78);
    this->m_bVar6C = *(BYTE*)(pData + 0x7C);
    this->m_bVar6D = *(BYTE*)(pData + 0x7D);
    this->m_bVar6E = *(BYTE*)(pData + 0x7E);
    this->m_clipStart = *(float*)(pData + 0x80);
    this->m_clipEnd = *(float*)(pData + 0x84);
    this->m_animLen = *(float*)(pData + 0x88);
    this->m_fVar7C = *(float*)(pData + 0x8C);
    this->m_bVar80 = *(BYTE*)(pData + 0x90);
}

AttribDataSourceAnim::~AttribDataSourceAnim()
{
}

int AttribDataSourceAnim::GetAnimID()
{
    return this->m_animIdx;
}

int AttribDataSourceAnim::GetRigToAnimMapBundleID()
{
    return this->m_rigToAnimMapBundleID;
}

float AttribDataSourceAnim::GetClipStart()
{
    return this->m_clipStart;
}

float AttribDataSourceAnim::GetClipEnd()
{
    return this->m_clipEnd;
}

float AttribDataSourceAnim::GetAnimLen()
{
    return this->m_animLen;
}