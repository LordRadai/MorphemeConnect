#include "../../../util/stdafx.hpp"
#include "../stdafx.hpp"

namespace cfr
{
	struct HKX
	{
		struct Header
		{
			long magic;
			int userTag;
			int version;
		};

		struct ClassSection
		{

		};

		struct TypeSection
		{

		};

		struct DataSection
		{

		};
	};

	HKX* openHKX(MEM* src);
};