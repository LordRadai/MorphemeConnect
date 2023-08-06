#include "NMBReader.h"
//define PACKET_DEBUG to log to console the read packets. Not recommended unless you think you're getting invalid results
//#define PACKET_DEBUG 

NmbPacket::NmbPacket(ifstream* pFile)
{
	streampos offset = 0;
	streampos pStart = pFile->tellg();

	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_magic[0]); assert(this->m_magic[0] == 24);
	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_magic[1]); assert(this->m_magic[1] == 10);
	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_packetType);
	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_signature);
	MemHelper::ReadByteArray(pFile, (LPVOID*)&this->m_header, 16);
	MemHelper::ReadQWord(pFile, (LPVOID*)&this->m_dataSize);
	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_dataAlignment);
	MemHelper::ReadDWord(pFile, (LPVOID*)&this->m_iVar2C);

	streampos pDataStart = pFile->tellg();

	if (this->m_dataSize != 0)
	{
		this->m_data = new byte[this->m_dataSize];
		MemHelper::ReadByteArray(pFile, (LPVOID*)this->m_data, 16);
	}
	else
		this->m_data = NULL;

	if (this->m_packetType == Packet_SkeletonMap)
		offset = 4; //This packet is always off by 4 bytes

	streampos pNext = ((streampos)this->m_dataSize + (streampos)3 + pDataStart) & 0xfffffffffffffffcLL; //Align the next section to 32 bits. The NMB file is compiled in 32 bits and then padded for 64
	pFile->seekg(pNext + offset);

#ifdef PACKET_DEBUG
	printf_s("Packet {\n");
	printf_s("\tm_magic=(%d, %d)\n", this->m_magic[0], this->m_magic[1]);
	printf_s("\tm_packetType=%d\n", this->m_packetType);
	printf_s("\tm_signature=%x\n", this->m_signature);
	printf_s("\tm_header={");

	for (size_t i = 0; i < 16; i++)
	{
		printf_s("%x", this->m_header[i]);

		if (i != 15)
			printf_s(" ");
	}
	printf_s("}\n");

	printf_s("\tm_dataSize=%ld\n", this->m_dataSize);
	printf_s("\tm_dataAlignment=%d\n", this->m_dataAlignment);
	printf_s("\tm_iVar2C=%d\n", this->m_iVar2C);

	printf_s("\tm_data={");

	for (size_t i = 0; i < this->m_dataSize; i++)
	{
		printf_s("%x", this->m_data[i]);

		if (i != (this->m_dataSize - 1))
			printf_s(" ");
	}
	printf_s("}\n");

	printf_s("}\n");
#endif
}

NMBReader::NMBReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	ifstream nmb;

	nmb.open(this->m_filePath, ios::binary | ios::ate);
	this->m_fileSize = nmb.tellg();
	nmb.close();

	nmb.open(this->m_filePath, ios::binary);

	int iPacketType = 0;
	while ((nmb.eof() == false) && (iPacketType < Packet_FileNameLookupTable))
	{
		this->m_packets.push_back(NmbPacket(&nmb));
		iPacketType = this->m_packets.back().m_packetType;
	}
}

NMBReader::~NMBReader()
{
}