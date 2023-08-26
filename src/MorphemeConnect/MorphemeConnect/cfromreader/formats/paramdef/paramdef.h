#pragma once
#include "../stdafx.hpp"
#include <string>

namespace cfr {
	enum EditEnum
	{
		EDIT_WRAP = 1,
		EDIT_LOCK = 4,
	};

	class PARAMDEF
	{
		public:
		class Header
		{
			public:
			short version;
			int fileSize;
			short headerSize;
			short dataVersion;
			short fieldCount;
			short fieldSize;
			int typePad1;
			std::string paramType; //verify this
			long typePad2;
			long typePad3;
			int typePad4;
			char paramID[32];
			char bigEndian;
			char unicode;
			short formatVersion;
			long fieldsOffset;

			Header();

			Header(MEM* src);
		};

		class Field
		{
			public:
			long displayNameOffset;
			//std::string displayName;
			char displayType[8];
			char displayFormat[8];
			float defaultValue;
			float minValue;
			float maxValue;
			float increment;
			int editFlags;
			int byteCount;
			//these should be internal to the reader
			/*long descriptionOffset;
			long internalTypeOffset;
			char internalType[32];
			long internalNameOffset;
			char internalName[32];*/
			int sortId;
			int unkB4;
			long offsetB8;
			long offsetC0;
			long offsetC8;
			std::wstring description;
			std::string unkB8;
			std::string unkC0;
			std::string unkC8;
			std::wstring displayName;
			std::string internalType;
			std::string internalName;

			Field();

			Field(MEM* src, Header header);
		};

		Header header;
		std::vector<Field> fields;

		PARAMDEF();

		PARAMDEF(MEM* src);
	};
};