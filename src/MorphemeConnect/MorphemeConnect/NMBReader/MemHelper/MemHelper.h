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

namespace MemHelper
{
	void ReadByte(ifstream* pStream, LPVOID* pDst);
	void ReadWord(ifstream* pStream, LPVOID* pDst);
	void ReadDWord(ifstream* pStream, LPVOID* pDst);
	void ReadQWord(ifstream* pStream, LPVOID* pDst);
	void ReadByteArray(ifstream* pStream, LPVOID* pDst, int iSize);
	void ReadWordArray(ifstream* pStream, LPVOID* pDst, int iSize);
	void ReadDWordArray(ifstream* pStream, LPVOID* pDst, int iSize);
	void ReadQWordArray(ifstream* pStream, LPVOID* pDst, int iSize);

	void WriteByte(ofstream* pStream, LPVOID* pSrc);
	void WriteWord(ofstream* pStream, LPVOID* pSrc);
	void WriteDWord(ofstream* pStream, LPVOID* pSrc);
	void WriteQWord(ofstream* pStream, LPVOID* pSrc);
	void WriteByteArray(ofstream* pStream, LPVOID* pSrc, int iSize);
	void WriteWordArray(ofstream* pStream, LPVOID* pSrc, int iSize);
	void WriteDWordArray(ofstream* pStream, LPVOID* pSrc, int iSize);
	void WriteQWordArray(ofstream* pStream, LPVOID* pSrc, int iSize);
}