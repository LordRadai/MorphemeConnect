#pragma once
#include <cassert>
#include "../../MemReader/MemReader.h"

enum eBundleType
{
	Bundle_Invalid = 0,
	Bundle_SkeletonMap = 1,
	Bundle_MessageIndices = 2,
	Bundle_DiscreteEventTrack = 3,
	Bundle_DurationEventTrack = 4,
	Bundle_CharacterControllerDef = 7,
	Bundle_Network = 10,
	Bundle_FileHeader = 12,
	Bundle_FileNameLookupTable = 13
};

class MorphemeBundle_Base
{
public:
	UINT m_magic[2] = { 24, 10 };			//They must always be 24 and 10 in order
	eBundleType m_bundleType;				//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;						//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;					//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;

	virtual void WriteBinary(ofstream* out) { return; }
	virtual int CalculateBundleSize() { return this->m_dataSize; }
};