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
	void ReadByte(ifstream* pStream, BYTE* pDst);
	void ReadWord(ifstream* pStream, WORD* pDst);
	void ReadDWord(ifstream* pStream, DWORD* pDst);
	void ReadQWord(ifstream* pStream, UINT64* pDst);
	void ReadByteArray(ifstream* pStream, BYTE* pDst, int iSize);
	void ReadWordArray(ifstream* pStream, WORD* pDst, int iSize);
	void ReadDWordArray(ifstream* pStream, DWORD* pDst, int iSize);
	void ReadQWordArray(ifstream* pStream, UINT64* pDst, int iSize);

	void WriteByte(ofstream* pStream, BYTE pSrc);
	void WriteWord(ofstream* pStream, WORD pSrc);
	void WriteDWord(ofstream* pStream, DWORD pSrc);
	void WriteQWord(ofstream* pStream, UINT64 pSrc);
	void WriteByteArray(ofstream* pStream, BYTE* pSrc, int iSize);
	void WriteWordArray(ofstream* pStream, WORD* pSrc, int iSize);
	void WriteDWordArray(ofstream* pStream, DWORD* pSrc, int iSize);
	void WriteQWordArray(ofstream* pStream, UINT64* pSrc, int iSize);
}