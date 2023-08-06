#include "NMBReader.h"

NMBReader::NMBReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	ifstream nmb(this->m_filePath, ios::binary | ios::ate);

	this->m_fileSize = nmb.tellg();
}

NMBReader::~NMBReader()
{
}