#include "NodeAttribBase.h"

NodeAttribBase::NodeAttribBase(BYTE* data)
{
    this->field0_0x0 = *(int*)(data);
    this->field1_0x4 = *(int*)(data + 0x4);
    this->field2_0x8 = *(short*)(data + 0x8);
    this->m_type = *(AttribType*)(data + 0xA);
    this->padding = *(int*)(data + 0xC);
}