#include "TimeActReader.h"

TimeActReader::TimeActReader()
{
}

TimeActReader::TimeActReader(PWSTR filePath)
{
	this->m_init = true;
	this->m_filePath = filePath;

	ifstream tae;

	tae.open(this->m_filePath, ios::binary);
	this->m_header = Header(&tae);

	this->m_fileSize = this->m_header.m_fileSize;

	this->m_tae.reserve(this->m_header.m_taeCount);

	for (int i = 0; i < this->m_header.m_taeCount; i++)
		this->m_tae.push_back(TimeAct(&tae));

	tae.close();
}

TimeActReader::~TimeActReader()
{
}