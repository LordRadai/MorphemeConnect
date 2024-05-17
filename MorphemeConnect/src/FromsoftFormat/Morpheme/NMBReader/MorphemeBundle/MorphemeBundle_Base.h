#pragma once
#include <iostream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cassert>
#include "../../../Utils/MemReader/MemReader.h"
#include "../../Morpheme.h"

namespace NMB
{
	enum AssetType
	{
		kAsset_Invalid = -1,
		kAsset_Rig = 1,
		kAsset_RigToAnimMap = 2,
		kAsset_EventTrackDiscrete = 3,
		kAsset_EventTrackDuration = 4,
		kAsset_EventTrackCurve = 5,
		kAsset_CharacterControllerDef = 7,
		kAsset_NetworkDef = 10,
		kAsset_Header = 12,
		kAsset_SimpleAnimruntimeIDtoFilenameLookup = 13
	};

	class MorphemeBundle_Base
	{
	public:
		UINT m_magic[2] = { 24, 10 };			//They must always be 24 and 10 in order for the 64 bit version
		AssetType m_assetType;					//Enumerator used to determine what kind of data the packet holds
		UINT m_signature;						//Signature that can be used by a packet to reference another one
		BYTE m_guid[16];
		UINT64 m_dataSize;
		UINT m_dataAlignment;					//I've only seen this be equal to 4 or 16
		UINT m_iVar2C;

		virtual void WriteBinary(ofstream* out) { return; }

		virtual UINT64 GetMemoryRequirements() { return this->m_dataSize; }

		std::string GetGUID()
		{
			std::stringstream guid;
			guid << std::hex << std::setfill('0');

			for (size_t i = 0; i < 16; i++)
			{
				if (i == 4 || i == 6 || i == 8 || i == 10)
					guid << '-';

				guid << std::setw(2) << static_cast<unsigned>(this->m_guid[i]);
			}

			return guid.str();
		}
	};
}