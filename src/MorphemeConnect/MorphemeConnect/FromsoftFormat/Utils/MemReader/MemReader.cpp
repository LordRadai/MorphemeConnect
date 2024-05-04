#include "MemReader.h"

template <typename T> void MemReader::Read(ifstream* pStream, T* pBuf)
{
	pStream->read(pDst, sizeof(T));
}

template <typename T> void MemReader::ReadArray(ifstream* pStream, T* pBuf, size_t iCount)
{
	pStream->read(pDst, iCount * sizeof(T));
}

template <typename T> void MemReader::Write(ofstream* pStream, T v)
{
	pStream->write(v, sizeof(T));
}

template <typename T> void MemReader::WriteArray(ofstream* pStream, T* pVal, size_t iCount)
{
	pStream->write(pVal, iCount * sizeof(T));
}

void MemReader::Pad(ofstream* pStream, BYTE padVal, int iCount)
{
	BYTE* pPaddingVal = new BYTE[iCount];

	for (size_t i = 0; i < iCount; i++)
		pPaddingVal[i] = padVal;

	MemReader::WriteArray<BYTE>(pStream, pPaddingVal, iCount);

	delete[] pPaddingVal;
}

void MemReader::AlignStream(ofstream* pStream, UINT64 alignment)
{
	if (alignment == 0)
		return;

	streampos current_pos = pStream->tellp();
	UINT64 remainder = current_pos % alignment;
	UINT64 pad_amt = alignment - remainder;

	if (pad_amt > 0)
	{
		BYTE* pad = new BYTE[pad_amt];

		for (size_t i = 0; i < pad_amt; i++)
			pad[i] = 0xCD;

		MemReader::WriteArray<BYTE>(pStream, pad, pad_amt);

		delete[] pad;
	}
}