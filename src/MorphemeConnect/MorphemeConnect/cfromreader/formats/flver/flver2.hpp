#pragma once
#include "../../util/stdafx.hpp"
#include "../stdafx.hpp"
//welcome to FLVER-town

//standard fromsoft model format from DSPTDE onwards
//as usual, built using SoulsTemplates! :)
//to help shorten this for now, it won't support non souls games

namespace cfr {
	enum VertexSemantic
	{
		//FLVER2_VERTEX_SEMANTIC
		FVS_POSITION     =  0,
		FVS_BONE_WEIGHTS =  1,
		FVS_BONE_INDICES =  2,
		FVS_NORMAL       =  3,
		FVS_UV           =  5,
		FVS_TANGENT      =  6,
		FVS_BITANGENT    =  7,
		FVS_VERTEX_COLOR = 10
	};

	enum VertexType
	{
		FVT_VEC2               = 0x01, //two floats
		FVT_VEC3               = 0x02, //three floats
		FVT_VEC4               = 0x03, //four floats
		FVT_UNK0               = 0x10, //unknown
		FVT_4_BYTE_0           = 0x11, //four bytes
		FVT_SHORT2             = 0x12, //two shorts
		FVT_4_BYTE_1           = 0x13, //four bytes
		FVT_UV                 = 0x15, //two shorts
		FVT_UV_PAIR            = 0x16, //four shorts
		FVT_SHORT_BONE_INDICES = 0x18, //four shorts
		FVT_4_SHORT_0          = 0x1A, //four shorts
		FVT_UNK1               = 0x2E, //unknown
		FVT_UNK2               = 0x2F, //unknown
		FVT_UNK3               = 0xF0, //unknown
	};

	struct FLVER2
	{
		struct Header
		{
			char magic[6]; //this was working with size 4 somehow. it shouldn't
			char endian[2];
			uint32_t version;

			uint32_t dataOffset = 0;
			uint32_t dataLength;

			int32_t dummyCount;
			int32_t materialCount;
			int32_t boneCount;
			int32_t meshCount;
			int32_t vertexBufferCount;

			float boundingBoxMin_x;
			float boundingBoxMin_y;
			float boundingBoxMin_z;

			float boundingBoxMax_x;
			float boundingBoxMax_y;
			float boundingBoxMax_z;

			int32_t trueFaceCount; // Does not include shadow meshes or degenerate faces
			int32_t totalFaceCount;

			char vertexIndexSize;
			char unicode;

			char unk4A;
			char unk4B;

			int32_t primitiveRestartConstant; //guess, needs confirmation
			int32_t faceSetCount;
			int32_t bufferLayoutCount;
			int32_t textureCount;

			char unk5C;
			char unk5D;
			char unk5E; //assert(0)
			char unk5F; //assert(0)

			int32_t unk60; //assert(0)
			int32_t unk64; //assert(0)
			int32_t unk68;
			int32_t unk6C; //assert(0)
			int32_t unk70; //assert(0)
			int32_t unk74; //assert(0)
			int32_t unk78; //assert(0)
			int32_t unk7C; //assert(0)
		};

		struct Dummy
		{
			float pos_x;
			float pos_y;
			float pos_z;

			uint8_t color[4];

			float forward_x;
			float forward_y;
			float forward_z;

			int16_t referenceID;
			int16_t dummyBoneIndex;

			float upward_x;
			float upward_y;
			float upward_z;

			int16_t attachBoneIndex;
			char unk2E;
			char useUpwardVector;

			int32_t unk30;
			int32_t unk34;
			int32_t unk38; //assert(0)
			int32_t unk3C; //assert(0)
		};

		struct Material //unclear on how safe this is '_>', specifically gxOffset
		{
			struct Header
			{
				uint32_t nameOffset = 0;
				uint32_t mtdOffset = 0;

				int32_t textureCount;
				int32_t textureIndex;

				uint32_t flags;
				uint32_t gxOffset = 0;

				int32_t unk18;
				int32_t unk1C; //assert(0)
			};
			
			struct GxItem //length INCLUDES this struct!
			{
				uint32_t id;
				int32_t unk04; //maybe assert(100)? if header.version < 0x20010
				int32_t length;

				char data[];
			};

			Header* header;
			GxItem** gxItems;
		};

		struct Bone
		{
			float translation_x;
			float translation_y;
			float translation_z;

			uint32_t nameOffset;

			float rot_x;
			float rot_y;
			float rot_z;

			int16_t parentIndex;
			int16_t childIndex;

			float scale_x;
			float scale_y;
			float scale_z;

			int16_t nextSiblingIndex;
			int16_t previousSiblingIndex;

			float boundingBoxMin_x;
			float boundingBoxMin_y;
			float boundingBoxMin_z;
			
			int32_t unk3C;

			float boundingBoxMax_x;
			float boundingBoxMax_y;
			float boundingBoxMax_z;
			
			char emptyJunk[52]; //potentially needed for spacing :/
		};

		struct Mesh
		{
			struct Header
			{
				bool dynamic; 
		
				char unk01; //assert(0)
				char unk02; //assert(0)
				char unk03; //assert(0)
				
				int32_t materialIndex;
				
				int32_t unk08; //assert(0)
				int32_t unk0C; //assert(0)
				
				int32_t defaultBoneIndex;
				int32_t boneCount;
				uint32_t boundingBoxOffset = 0;
				uint32_t boneIndicesOffset = 0;
				
				int32_t faceSetCount;
				uint32_t faceSetIndicesOffset;

				int32_t vertexBufferCount;
				uint32_t vertexBufferIndicesOffset;
			};

			//only if boundingBoxOffset != 0
			struct BoundingBoxData
			{
				float boundingBoxMin_x;
				float boundingBoxMin_y;
				float boundingBoxMin_z;

				float boundingBoxMax_x;
				float boundingBoxMax_y;
				float boundingBoxMax_z;
			};

			//only if header.version >= 0x2001A
			struct BoundingBoxDataUnk
			{
				float boundingBoxUnk_x; 
				float boundingBoxUnk_y;
				float boundingBoxUnk_z;
			};
			
			Header* header = NULL;
			BoundingBoxData* boundingBoxData = NULL;
			BoundingBoxDataUnk* boundingBoxDataUnk = NULL;
			int32_t** boneIndices; //size of boneCount
			int32_t** faceSetIndices; //size of faceSetCount
			int32_t** vertexBufferIndices; //size of vertexBufferCount
		};

		struct Member
		{
			struct Header
			{
				int32_t dataLength;
				int32_t dataOffset;

				int32_t unk08; //assert(0)
				int32_t unk0C; //assert(0)
				int16_t unk10;
				int16_t unk12;

				int16_t baseIndex;

				int16_t unk16;
				int32_t unk18;
				int32_t unk1C;
				int32_t unk20; //assert(0)
				int32_t unk24; //assert(0)
				int32_t unk28; //assert(0)
				int32_t unk2C; //assert(0)

				//edgeGeomSpuConfigInfo? not sure what this means
				int16_t unk30;
				int16_t unk32;
				int16_t unk34;
				int16_t unk36;
				int16_t unk38;

				int16_t indexCount;

				int32_t unk3C; //assert(-1)
			};

			Header* header;
			uint8_t* data; //size of dataLength
		};

		struct EdgeIndices
		{
			struct Header
			{
				int16_t memberCount;
				int16_t unk02;
				int32_t unk04;
				int32_t unk08; //assert(0)
				int32_t unk0C;
			};

			Header* header;
			Member* members; //size of memberCount
		};

		struct FaceSet
		{
			struct Header
			{
				uint32_t flags;
				bool triangleStrip;
				bool cullBackFaces;
				char unk06;
				char unk07;
				int32_t vertexIndexCount; //number of indices
				uint32_t vertexIndicesOffset;
			};

			//only if header.version >= 0x20009
			struct VertInfo
			{
				int32_t vertexIndicesLength; //i don't know
				int32_t unk14; //assert(0)
				int32_t vertexIndexSize; //byte size of indices
				int32_t unk1C; //assert(0)
			};
			
			Header* header;
			VertInfo* vertInfo;
			EdgeIndices* vertexIndicesEdge = NULL;
			uint16_t* vertexIndicesShort = NULL; //vertexindexcount
			uint32_t* vertexIndicesInt = NULL; //vertexindexcount
			int vertexSize = 0; //more accurate
		};

		struct VertexBuffer
		{
			struct Header
			{
				int32_t bufferIndex;
				int32_t layoutIndex;
				int32_t vertexSize;
				int32_t vertexCount;

				int32_t unk10; //assert(0)
				int32_t unk14; //assert(0)

				uint32_t verticesLength; //0 in version 20005, non 0 in 20008
				uint32_t bufferOffset;
			};

			struct Vertex
			{
				char* data; //vertexSize blocks
			};
			
			Header* header;
			Vertex* vertices; //vertexCount * vertexSize
		};

		struct LayoutMember
		{
			int32_t unk00; //0, 1, or 2
			int32_t structOffset; //unused?
			uint32_t type;
			uint32_t semantic;
			int32_t index;
		};

		struct BufferLayout
		{
			struct Header
			{
				int32_t memberCount;

				int32_t unk04; //assert(0)
				int32_t unk08; //assert(0)

				uint32_t membersOffset;
			};

			Header* header;
			LayoutMember** members; //size of memberCount
		};

		struct Texture
		{
			uint32_t pathOffset;
			uint32_t typeOffset;

			float scale_x;
			float scale_y;

			char unk10;
			char unk11;
			int16_t unk12; //assert(0)

			float unk14;
			float unk18;
			float unk1C;
		};

		struct VertexBoneWeights
		{
			float a,b,c,d;
			int32_t length; //always 4
		};

		struct VertexBoneIndices
		{
			int32_t a,b,c,d;
			int32_t length; //always 4
		};

		struct VertexColor
		{
			float a,r,g,b;
		};

		Header* header;
		Dummy* dummies;
		Material* materials;
		Bone* bones;
		Mesh* meshes;
		FaceSet* faceSets;
		VertexBuffer* vertexBuffers;
		BufferLayout* bufferLayouts;
		Texture* textures;
	};

	//Init FLVER2 from MEM, pos assumed to be at start of FLVER
	FLVER2* openFLVER2(MEM* src);

	//Init FLVER2 from a pointer
	FLVER2* openFLVER2(void* src, size_t size);

	//Init FLVER2 from a file
	FLVER2* openFLVER2(const char* path);

	//Export data from FLVER2 for validation.
	void exportFLVER2(FLVER2 flver, const char* path);

	//Print FLVER2 data to console.
	void printFLVER2(FLVER2* flver);
};