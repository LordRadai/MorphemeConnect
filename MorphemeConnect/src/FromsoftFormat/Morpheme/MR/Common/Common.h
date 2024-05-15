#pragma once
#include <Windows.h>
#include <vector>
#include <string>

class StringTable
{
public:
    StringTable();
    StringTable(BYTE* pData);
    ~StringTable();

    int GetNumEntries();
    int GetDataLenght();
    int GetID(int id);
    UINT GetOffset(int id);
    std::string GetString(int id);
    int GetMemoryRequirement();
private:
    int m_numEntries;
    int m_dataLenght;
    std::vector<int> m_IDs;
    std::vector<UINT> m_offsets;
    std::vector<char> m_data;
};