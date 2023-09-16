#include "NodeAttribUnknown.h"

NodeAttribUnknown::NodeAttribUnknown(BYTE* data, int size) : NodeAttribBase(data)
{
    int data_size = size - 16;

    if (data_size > -1)
    {
        this->m_content = new BYTE[data_size];

        for (size_t i = 0; i < data_size; i++)
            this->m_content[i] = (*(data + 0x10 + (BYTE)i));
    }
}

void NodeAttribUnknown::GenerateBinary(std::ofstream* out)
{
    MemReader::WriteDWord(out, (DWORD*)&this->field0_0x0);
    MemReader::WriteDWord(out, (DWORD*)&this->field1_0x4);
    MemReader::WriteDWord(out, (DWORD*)&this->field2_0x8);
    MemReader::WriteWord(out, (WORD*)&this->m_type);
    MemReader::WriteWord(out, (WORD*)&this->padding);
}