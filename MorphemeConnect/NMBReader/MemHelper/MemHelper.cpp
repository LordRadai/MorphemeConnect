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