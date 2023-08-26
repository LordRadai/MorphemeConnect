#pragma once
#include "stdafx.hpp"

//common structus for MSB format

namespace cfr
{
	enum ShapeType
	{
		ShapeTypeNone = -1,
		ShapeTypePoint = 0,
		ShapeTypeCircle = 1,
		ShapeTypeSphere = 2,
		ShapeTypeCylinder = 3,
		ShapeTypeRect = 4,
		ShapeTypeBox = 5,
		ShapeTypeComposite = 6
	};

	struct MSB_Header
	{
		char magic[4];
		int32_t unk04;
		int32_t headerSize;
		char isBigEndian;
		char isBitBigEndian;
		char textEncoding;
		char is64BitOffset;

		void(*MSB_ShapeRect)(MSB_Header* temp, FILE* src);
	};

	void init(MSB_Header* temp, FILE* src)
	{
		fread(&temp->magic,16,1,src);
	};

	struct MSB_Param
	{
		int32_t version;

		//if varint_long false, reverse order!
		int32_t count;
		int64_t nameOffset;

		//quad if varint_long, otherwise int
		int64_t* offsets; //[count -1]
		int64_t nextParamOffset;

		void(*MSB_Param)(MSB_Header* temp, FILE* src, bool varIntLong);
	};

	void init(MSB_Param* temp, FILE* src, bool varIntLong)
	{
		fread(&temp->version,4,1,src);

		if(varIntLong)
		{
			fread(&temp->nameOffset,4,1,src);
			fread(&temp->count,     4,1,src);
		}
		else
		{
			fread(&temp->count,      4,1,src);
			fread(&temp->nameOffset ,4,1,src);
		}

		temp->offsets = (int64_t*)malloc(temp->count*8-1);

		if(varIntLong)
		{
			fread(temp->offsets,8,temp->count-1,src);
			fread(&temp->nextParamOffset,8,1,src);
		}
		else
		{
			for(int i = 0; i < temp->count-1; i++)
			{
				fread(&temp->offsets[i],4,temp->count-1,src);
			}

			fread(&temp->nextParamOffset,4,1,src);
		}		
	};

	struct MSB_ShapeCircle
	{
		float radius;

		void(*MSB_ShapeRect)(MSB_ShapeCircle* temp, FILE* src);
	};

	void init(MSB_ShapeCircle* temp, FILE* src)
	{
		fread(&temp->radius,4,1,src);
	};

	struct MSB_ShapeShpere
	{
		float radius;

		void(*MSB_ShapeRect)(MSB_ShapeShpere* temp, FILE* src);
	};

	void init(MSB_ShapeShpere* temp, FILE* src)
	{
		fread(&temp->radius,4,1,src);
	};

	struct MSB_ShapeCylinder
	{
		float radius;
		float height;

		void(*MSB_ShapeRect)(MSB_ShapeCylinder* temp, FILE* src);
	};

	void init(MSB_ShapeCylinder* temp, FILE* src)
	{
		fread(&temp->radius,4,2,src);
	};

	struct MSB_ShapeRect
	{
		float width;
		float height;

		void(*MSB_ShapeRect)(MSB_ShapeRect* temp, FILE* src);
	};

	void init(MSB_ShapeRect* temp, FILE* src)
	{
		fread(&temp->width,4,2,src);
	};

	struct MSB_ShapeBox
	{
		float width;
		float depth;
		float height;

		void(*MSB_ShapeBox)(MSB_ShapeBox* temp, FILE* src);
	};

	void init(MSB_ShapeBox* temp, FILE* src)
	{
		fread(&temp->width,4,3,src);
	};

	struct MSB_ShapeComposite
	{
		//each "pair" must be read sequentially
		int32_t pointIndex[8];
		int32_t unk04[8];

		void(*MSB_ShapeComposite)(MSB_ShapeComposite* temp, FILE* src);
	};

	void init(MSB_ShapeComposite* temp, FILE* src)
	{
		for(int i = 0; i < 8; i++)
		{
			fread(&temp->pointIndex[i],4,1,src);
			fread(&temp->unk04[i],4,1,src);
		}
	}
};