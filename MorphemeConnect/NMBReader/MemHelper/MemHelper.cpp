#include "MemHelper.h"

void MemHelper::ReadByte(ifstream* pStream, LPVOID* pDst)
{
	pStream->read((char*)pDst, 1);
}

void MemHelper::ReadWord(ifstream* pStream, LPVOID* pDst)
{
	pStream->read((char*)pDst, 2);
}

void MemHelper::ReadDWord(ifstream* pStream, LPVOID* pDst)
{
	pStream->read((char*)pDst, 4);
}

void MemHelper::ReadQWord(ifstream* pStream, LPVOID* pDst)
{
	pStream->read((char*)pDst, 8);
}

void MemHelper::ReadByteArray(ifstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->read((char*)pDst, 1 * iSize);
}

void MemHelper::ReadWordArray(ifstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->read((char*)pDst, 2 * iSize);
}

void MemHelper::ReadDWordArray(ifstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->read((char*)pDst, 4 * iSize);
}

void MemHelper::ReadQWordArray(ifstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->read((char*)pDst, 8 * iSize);
}

void MemHelper::WriteByte(ofstream* pStream, LPVOID* pDst)
{
	pStream->write((const char*)pDst, 1);
}

void MemHelper::WriteWord(ofstream* pStream, LPVOID* pDst)
{
	pStream->write((const char*)pDst, 2);
}

void MemHelper::WriteDWord(ofstream* pStream, LPVOID* pDst)
{
	pStream->write((const char*)pDst, 4);
}

void MemHelper::WriteQWord(ofstream* pStream, LPVOID* pDst)
{
	pStream->write((const char*)pDst, 8);
}

void MemHelper::WriteByteArray(ofstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->write((const char*)pDst, 1 * iSize);
}

void MemHelper::WriteWordArray(ofstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->write((const char*)pDst, 2 * iSize);
}

void MemHelper::WriteDWordArray(ofstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->write((const char*)pDst, 4 * iSize);
}

void MemHelper::WriteQWordArray(ofstream* pStream, LPVOID* pDst, int iSize)
{
	pStream->write((const char*)pDst, 8 * iSize);
}