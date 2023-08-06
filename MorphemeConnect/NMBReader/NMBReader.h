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

class NMBReader
{
public:
	PWSTR m_filePath = PWSTR("\0");
	uint64_t m_fileSize;

	NMBReader(PWSTR pszFilePath);
	~NMBReader();
};