#include "../MemReader/MemReader.h"

class File
{
public:
	UINT64 m_compressedSize;
	UINT64 m_uncompressedSize;
	int m_dataOffset;
	int m_id;
	int m_nameOffset;

	std::string m_name;
	BYTE* m_data;

	File();
	File(ifstream* dcx);
	~File();
};

class BNDReader 
{
public:
	PWSTR m_filePath;
	UINT64 m_fileSize;
	PWSTR m_outFilePath;
	UINT64 m_outFileSize;
	bool m_init = false;

	int m_fileCount;
	std::vector<File> m_files;

	BNDReader();
	BNDReader(PWSTR pszFilePath);
	~BNDReader();
};