#pragma once
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <commdlg.h>
#include <shobjidl.h> 
#include <iostream>
#include <fstream>

using namespace std;

namespace MemReader
{
	template <typename T> void Read(ifstream* pStream, T* pBuf)
	{
		pStream->read(pBuf, sizeof(T));
	}

	template <typename T> void ReadArray(ifstream* pStream, T* pBuf, size_t iCount)
	{
		pStream->read(pBuf, iCount * sizeof(T));
	}

	template <typename T> void Write(ofstream* pStream, T v)
	{
		pStream->write(&v, sizeof(T));
	}

	template <typename T> void WriteArray(ofstream* pStream, const T* pVal, size_t iCount)
	{
		pStream->write((const char*)pVal, iCount * sizeof(T));
	}

	void Pad(ofstream* pStream, BYTE padVal, int iCount)
	{
		BYTE* pPaddingVal = new BYTE[iCount];

		for (size_t i = 0; i < iCount; i++)
			pPaddingVal[i] = padVal;

		WriteArray(pStream, pPaddingVal, iCount);

		delete[] pPaddingVal;
	}

	void AlignStream(ofstream* pStream, UINT64 alignment)
	{
		if (alignment == 0)
			return;

		streampos current_pos = pStream->tellp();
		UINT64 remainder = current_pos % alignment;
		UINT64 pad_amt = alignment - remainder;

		Pad(pStream, 0xCD, pad_amt);
	}
}