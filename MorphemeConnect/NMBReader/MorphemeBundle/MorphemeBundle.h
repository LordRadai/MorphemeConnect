#pragma once
#include <cassert>

#include "../MemHelper/MemHelper.h"

using namespace std;

enum eBundleType
{
	Bundle_Invalid = 0,
	Bundle_SkeletonMap = 1,
	Bundle_MessageIndices = 2,
	Bundle_DiscreteEventTrack = 3,
	Bundle_DurationEventTrack = 4,
	Bundle_UnkParameters = 7,
	Bundle_Network = 10,
	Bundle_FileHeader = 12,
	Bundle_FileNameLookupTable = 13
};

struct MorphemeBundle
{
	UINT m_magic[2];			//They must always be 24 and 10 in order
	eBundleType m_bundleType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	byte* m_data;				//Pointer in which memory will be allocated

	MorphemeBundle();
	MorphemeBundle(ifstream* pFile);
};