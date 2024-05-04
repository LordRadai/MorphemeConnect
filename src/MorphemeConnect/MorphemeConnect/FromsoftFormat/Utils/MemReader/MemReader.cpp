#include "MemReader.h"

template <typename T> void MemReader::Read(ifstream* pStream, T* pBuf)
{
	pStream->read(pBuf, sizeof(T));
}

template <typename T> void MemReader::ReadArray(ifstream* pStream, T* pBuf, size_t iCount)
{
	pStream->read(pBuf, iCount * sizeof(T));
}

template <typename T> void MemReader::Write(ofstream* pStream, T v)
{
	pStream->write(&v, sizeof(T));
}

template <typename T> void MemReader::WriteArray(ofstream* pStream, const T* pVal, size_t iCount)
{
	pStream->write(pVal, iCount * sizeof(T));
}

void MemReader::Pad(ofstream* pStream, BYTE padVal, int iCount)
{
	BYTE* pPaddingVal = new BYTE[iCount];

	for (size_t i = 0; i < iCount; i++)
		pPaddingVal[i] = padVal;

	MemReader::WriteArray(pStream, pPaddingVal, iCount);

	delete[] pPaddingVal;
}

void MemReader::AlignStream(ofstream* pStream, UINT64 alignment)
{
	if (alignment == 0)
		return;

	streampos current_pos = pStream->tellp();
	UINT64 remainder = current_pos % alignment;
	UINT64 pad_amt = alignment - remainder;

	MemReader::Pad(pStream, 0xCD, pad_amt);
}