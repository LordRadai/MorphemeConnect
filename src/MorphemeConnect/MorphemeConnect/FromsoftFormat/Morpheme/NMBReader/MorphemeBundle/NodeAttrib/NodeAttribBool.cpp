#include "NodeAttribBool.h"

NodeAttribBool::NodeAttribBool(BYTE* data) : NodeAttribBase(data)
{
    if (this->m_type != ATTRIB_TYPE_BOOL)
        Debug::Panic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_type, ATTRIB_TYPE_BOOL);

    this->m_bool = *(bool*)(data + 0x10);
}