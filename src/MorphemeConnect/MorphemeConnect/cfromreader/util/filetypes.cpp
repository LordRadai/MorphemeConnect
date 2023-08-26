#include "filetypes.hpp"

namespace cfr
{
	//take in an 8 char array
	CfrFileType determineFormat(char* magicBytes)
	{
		printf("format: %s\n",magicBytes);

		//TODO: get analysis of most common files, and order this
		//list so it uses less checks

		if(memcmp(magicBytes,"BDF3",4) == 0 || memcmp(magicBytes,"BDF4",4) == 0)
		{
			return FROM_BDF;
		}
		else if(memcmp(magicBytes,"BHD5",4) == 0)
		{
			return FROM_BHD;
		}
		else if(memcmp(magicBytes,"BHF3",4) == 0 || memcmp(magicBytes,"BHF4",4) == 0)
		{
			return FROM_BHF;
		}
		else if(memcmp(magicBytes,"BND3",4) == 0 || memcmp(magicBytes,"BND4",4) == 0)
		{
			return FROM_BND;
		}
		else if(false)
		{
			return FROM_BTL;
		}
		else if(memcmp(magicBytes,"DCX",3) == 0)
		{
			return FROM_DCX;
		}
		else if(false)
		{
			return FROM_DRB;
		}
		else if(false)
		{
			return FROM_ENTRYFILELIST;
		}
		else if(false)
		{
			return FROM_ESD;
		}
		else if(false)
		{
			return FROM_EMEVD;
		}
		else if(false)
		{
			return FROM_FFX;
		}
		else if(memcmp(magicBytes,"FLVER",5) == 0)
		{
			return FROM_FLVER;
		}
		else if(false)
		{
			return FROM_FSB;
		}
		else if(false)
		{
			return FROM_FEV;
		}
		else if(false)
		{
			return FROM_ITL;
		}
		else if(false)
		{
			return FROM_GFX;
		}
		else if(false)
		{
			return FROM_GPARAM;
		}
		else if(false)
		{
			return FROM_LUA;
		}
		else if(memcmp(magicBytes,"MSB ",4) == 0)
		{
			return FROM_MSB;
		}
		else if(false)
		{
			return FROM_MTD;
		}
		else if(false)
		{
			return FROM_NGP;
		}
		else if(false)
		{
			return FROM_NVA;
		}
		else if(false)
		{
			return FROM_NVM;
		}
		else if(false)
		{
			return FROM_PARAM;
		}
		else if(false)
		{
			return FROM_SL2;
		}
		else if(memcmp(magicBytes,"TAE ",4) == 0)
		{
			return FROM_TAE;
		}
		else if(memcmp(magicBytes,"TPF\0",4) == 0)
		{
			return FROM_TPF;
		}
		else if(false)
		{
			return HAVOK_HKS;
		}
		else if(
			(magicBytes[4] == 'T') && 
			(magicBytes[5] == 'A') && 
			(magicBytes[6] == 'G') &&
			(magicBytes[7] == '0')
		)
		{
			return HAVOK_HKX;
		}
		else if(
			(magicBytes[0] == 1) && 
			(magicBytes[1] == 0) && 
			(magicBytes[2] == 0) &&
			(magicBytes[3] == 0) &&
			(magicBytes[4] == 0) &&
			(magicBytes[5] == 0) &&
			(magicBytes[6] != 0) &&
			(magicBytes[7] == 0)
		)
		{
			return HAVOK_HKXPWV;
		}
		else if(false)
		{
			return MS_DDS;
		}
		else
		{
			throw std::runtime_error("Unkown File Type!\n");
		}

		//return UNKOWN;
	};
};