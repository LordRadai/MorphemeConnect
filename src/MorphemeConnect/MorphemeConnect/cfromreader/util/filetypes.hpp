#pragma once
#include <stdio.h>
#include <cstring>
#include <stdexcept>

#ifndef CFR_FILE_TYPES__
#define CFR_FILE_TYPES__

namespace cfr
{
	//only for formats we need to support
	enum CfrFileType
	{
		UNKOWN,
		FROM_BDF,
		FROM_BHD,
		FROM_BHF,
		FROM_BND,
		FROM_BTL,
		FROM_DCX,
		FROM_DRB,
		FROM_ENTRYFILELIST,
		FROM_ESD,
		FROM_EMEVD,
		FROM_FFX,
		FROM_FLVER,
		FROM_FMG,
		FROM_FSB,
		FROM_FEV,
		FROM_ITL,
		FROM_GFX,
		FROM_GPARAM,
		FROM_LUA,
		FROM_MSB,
		FROM_MTD,
		FROM_NGP,
		FROM_NVA,
		FROM_NVM,
		FROM_PARAM,
		FROM_SL2,
		FROM_TAE,
		FROM_TPF,
		HAVOK_HKS,
		HAVOK_HKX,
		HAVOK_HKXPWV,
		MS_DDS,
	};

	//take in an 8 char array
	CfrFileType determineFormat(char* magicBytes);
};

#endif