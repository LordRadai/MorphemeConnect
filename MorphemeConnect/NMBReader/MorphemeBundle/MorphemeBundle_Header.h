#pragma once
#include "MorphemeBundle.h"

struct MorphemeBundle_Header
{
	struct BundleData_Header
	{
		INT64 m_iVar0;
		INT64 m_iVar1;
		INT64 m_iVar2;
		INT64 m_iVar3;
	};

	UINT m_magic[2];			//They must always be 24 and 10 in order
	eBundleType m_bundleType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	BundleData_Header* m_data;

	MorphemeBundle_Header();
	MorphemeBundle_Header(MorphemeBundle* bundle);
};