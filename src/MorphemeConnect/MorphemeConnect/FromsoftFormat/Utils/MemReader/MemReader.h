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
	template <typename T> void Read(ifstream* pStream, T* pBuf);
	template <typename T> void ReadArray(ifstream* pStream, T* pBuf, size_t iCount);
	template <typename T> void Write(ofstream* pStream, T v);
	template <typename T> void WriteArray(ofstream* pStream, const T* pVal, size_t iCount);
	void Pad(ofstream* pStream, BYTE padVal, int iCount);
	void AlignStream(ofstream* pStream, UINT64 alignment);
}