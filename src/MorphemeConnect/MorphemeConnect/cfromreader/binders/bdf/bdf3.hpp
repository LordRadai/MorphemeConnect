#pragma once
#include "../stdafx.hpp"

namespace cfr
{
    class BDF3
    {
		public:
        char version[8];
        FILE** data;
        int size;

        BDF3(FILE* src);
    };
};