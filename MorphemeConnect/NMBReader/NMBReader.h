#pragma once
#include <cassert>

#include "MemHelper/MemHelper.h"

using namespace std;

enum ePacketType
{
	Packet_SkeletonMap = 1,
	Packet_MessageIndices = 2,
	Packet_DiscreteEventTrack = 3,
	Packet_DurationEventTrack = 4,
	Packet_UnkParameters = 7,
	Packet_Network = 10,
	Packet_FileHeader = 12,
	Packet_FileNameLookupTable = 13
};

struct NmbPacket
{
	UINT m_magic[2];			//They must always be 24 and 10 in order
	ePacketType m_packetType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];			
	UINT64 m_dataSize;			
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	byte* m_data;				//Pointer in which memory will be allocated

	NmbPacket(ifstream* pFile);
};

class NMBReader
{
public:
	PWSTR m_filePath;
	UINT64 m_fileSize;

	std::vector<NmbPacket> m_packets;

	NMBReader(PWSTR pszFilePath);
	~NMBReader();
};