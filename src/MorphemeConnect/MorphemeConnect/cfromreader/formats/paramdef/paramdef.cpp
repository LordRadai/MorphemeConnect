#include "paramdef.h"

namespace cfr
{
	PARAMDEF::Header::Header(){};

	PARAMDEF::Header::Header(MEM* src)
	{
		long start = mtell(src);
		mread(&this->version,sizeof(short),1,src);
		mread(&this->fileSize,sizeof(int),1,src);
		mread(&this->headerSize,sizeof(short),1,src);
		mread(&this->dataVersion,sizeof(short),1,src);
		mread(&this->fieldCount,sizeof(short),1,src);
		mread(&this->fieldSize,sizeof(short),1,src);
		
		if(this->formatVersion >= 202)
		{
			mread(&this->typePad1,sizeof(int),1,src);
			long offset = 0;
			mread(&offset,sizeof(long),1,src);
			long pos = mtell(src);
			mseek(src,offset-start,SEEK_CUR);
			this->paramType = readString(src);
			mseek(src,pos+start,SEEK_SET);
			mread(&this->typePad2,sizeof(long),1,src);
			mread(&this->typePad3,sizeof(long),1,src);
			mread(&this->typePad4,sizeof(int),1,src);
		}
		else
		{
			mread(&this->paramID,1,32,src);
		}
		mread(&this->bigEndian,1,1,src);
		mread(&this->unicode,1,1,src);
		mread(&this->formatVersion,sizeof(short),1,src);

		if(formatVersion >= 201)
		{
			mread(&this->fieldsOffset,sizeof(long),1,src);
		}
	};

	PARAMDEF::Field::Field(){};

	PARAMDEF::Field::Field(MEM* src, Header header)
	{
		if(header.version >= 202)
		{
			mread(&this->displayNameOffset,sizeof(long),1,src);
		}
		else if(header.unicode == true)
		{
			wchar_t tempName[32];
			mread(&tempName,sizeof(wchar_t),32,src);
			this->displayName = wstringFromWchar(tempName,32);
		}
		else
		{
			char tempName[64];
			mread(&tempName,sizeof(char),64,src);
			this->displayName = wstringFromChar(tempName,64);
		}

		mread(&this->displayType,sizeof(char),8,src);
		mread(&this->displayFormat,sizeof(char),8,src);
		mread(&this->defaultValue,sizeof(float),1,src);
		mread(&this->minValue,sizeof(float),1,src);
		mread(&this->maxValue,sizeof(float),1,src);
		mread(&this->increment,sizeof(float),1,src);
		mread(&this->editFlags,sizeof(int),1,src);
		mread(&this->byteCount,sizeof(int),1,src);



		if(header.version >= 200)
		{
			long offset;
			mread(&offset,sizeof(long),1,src);
			long pos = mtell(src);
			mseek(src,offset,SEEK_CUR);

			if(header.unicode == true)
				this->description = readWstring(src);
			else
				this->description = shortToWideString(readString(src));

			mseek(src,pos,SEEK_SET);
		}
		else
		{
			int offset;
			mread(&offset,sizeof(int),1,src);
			long pos = mtell(src);
			mseek(src,offset,SEEK_CUR);

			if(header.unicode == true)
				this->description = readWstring(src);
			else
				this->description = shortToWideString(readString(src));

			mseek(src,pos,SEEK_SET);
		}

		if(header.version >= 202)
		{
			long offset;
			mread(&offset,sizeof(long),1,src);
			long pos = mtell(src);
			mseek(src,offset,SEEK_CUR);
			this->internalType = readString(src);
			mseek(src,pos,SEEK_SET);
		}
		else
		{
			char temp[32];
			mread(&temp,sizeof(char),32,src);
			this->internalType = stringFromChar(temp,32);
		}

		if(header.version >= 202)
		{
			long offset;
			mread(&offset,sizeof(long),1,src);
			long pos = mtell(src);
			mseek(src,offset,SEEK_CUR);
			this->internalName = readString(src);
			mseek(src,pos,SEEK_SET);
		}
		else if(header.version >= 102)
		{
			char temp[32];
			mread(&temp,sizeof(char),32,src);
			this->internalName = stringFromChar(temp,32);
		}

		if(header.version >= 104)
			mread(&this->sortId,sizeof(int),1,src);

		if(header.version >= 201)
		{
			mread(&this->unkB4,sizeof(int),1,src);
			mread(&this->offsetB8,sizeof(long),1,src);
			mread(&this->offsetC0,sizeof(long),1,src);
			mread(&this->offsetC8,sizeof(long),1,src);
		}

		//it effectively ends here. 
	};

	PARAMDEF::PARAMDEF(){};

	PARAMDEF::PARAMDEF(MEM* src)
	{
		this->header = Header(src);

		this->fields.resize(this->header.fieldCount);

		for(int i = 0; i < this->header.fieldCount; i++)
		{
			this->fields[i] = Field(src,this->header);
		}
	};
};