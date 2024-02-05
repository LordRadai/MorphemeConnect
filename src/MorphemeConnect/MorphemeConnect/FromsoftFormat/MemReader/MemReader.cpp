#include "MemReader.h"

void MemReader::ReadByte(ifstream* pStream, BYTE* pDst)
{
	pStream->read((char*)pDst, 1);
}

void MemReader::ReadWord(ifstream* pStream, WORD* pDst)
{
	pStream->read((char*)pDst, 2);
}

void MemReader::ReadDWord(ifstream* pStream, DWORD* pDst)
{
	pStream->read((char*)pDst, 4);
}

void MemReader::ReadQWord(ifstream* pStream, UINT64* pDst)
{
	pStream->read((char*)pDst, 8);
}

void MemReader::ReadByteArray(ifstream* pStream, BYTE* pDst, int iSize)
{
	pStream->read((char*)pDst, 1 * iSize);
}

void MemReader::ReadWordArray(ifstream* pStream, WORD* pDst, int iSize)
{
	pStream->read((char*)pDst, 2 * iSize);
}

void MemReader::ReadDWordArray(ifstream* pStream, DWORD* pDst, int iSize)
{
	pStream->read((char*)pDst, 4 * iSize);
}

void MemReader::ReadQWordArray(ifstream* pStream, UINT64* pDst, int iSize)
{
	pStream->read((char*)pDst, 8 * iSize);
}

void MemReader::WriteByte(ofstream* pStream, BYTE* pDst)
{
	pStream->write((const char*)pDst, 1);
}

void MemReader::WriteWord(ofstream* pStream, WORD* pDst)
{
	pStream->write((const char*)pDst, 2);
}

void MemReader::WriteDWord(ofstream* pStream, DWORD* pDst)
{
	pStream->write((const char*)pDst, 4);
}

void MemReader::WriteQWord(ofstream* pStream, UINT64* pDst)
{
	pStream->write((const char*)pDst, 8);
}

void MemReader::WriteByteArray(ofstream* pStream, BYTE* pDst, int iSize)
{
	pStream->write((const char*)pDst, 1 * iSize);
}

void MemReader::WriteWordArray(ofstream* pStream, WORD* pDst, int iSize)
{
	pStream->write((const char*)pDst, 2 * iSize);
}

void MemReader::WriteDWordArray(ofstream* pStream, DWORD* pDst, int iSize)
{
	pStream->write((const char*)pDst, 4 * iSize);
}

void MemReader::WriteQWordArray(ofstream* pStream, UINT64* pDst, int iSize)
{
	pStream->write((const char*)pDst, 8 * iSize);
}

void MemReader::WriteString(ofstream* pStream, const char** pString)
{
	int strlen = std::strlen(*pString);

	MemReader::WriteByteArray(pStream, (BYTE*)pString, strlen);
}

void MemReader::AlignStream(ofstream* pStream, UINT64 alignment)
{
	if (alignment == 0)
		return;

	streampos pPos = pStream->tellp();
	UINT64 remainder = pPos % alignment;
	UINT64 pad_amt = alignment - remainder;

	if (pad_amt > 0)
	{
		BYTE* pad = new BYTE[pad_amt];

		for (size_t i = 0; i < pad_amt; i++)
			pad[i] = 0xCD;

		MemReader::WriteByteArray(pStream, pad, pad_amt);

		delete[] pad;
	}
}