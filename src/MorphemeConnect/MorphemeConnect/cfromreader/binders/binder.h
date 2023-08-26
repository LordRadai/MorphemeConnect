#pragma once
#include "stdafx.hpp"

namespace cfr
{
	class File
	{
		public:
		std::string name;
		long size;
		void* data;
		std::vector<void*> parents; //null means no parent
		bool open;

		void open();
		void close();
		std::string getType();
	};
};
