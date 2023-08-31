#include "FlverReader.h"

FlverHeader::FlverHeader()
{
}

FlverHeader::FlverHeader(ifstream* flver)
{
	MemReader::ReadByteArray(flver, (BYTE*)this->m_magic, 6);
	MemReader::ReadByteArray(flver, (BYTE*)this->m_endian, 2);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_version);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_dataOffset);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_dataSize);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_dummyCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_materialCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_boneCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_meshCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_vertexBufferCount);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_bbMin, 3);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_bbMax, 3);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_trueFaceCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_totalFaceCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_vertexIndexSize);
	MemReader::ReadByte(flver, (BYTE*)&this->m_unicode);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar4A);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar4B);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_primitiveRestartCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_faceSetCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_bufferLayoutCount);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_textureCount);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar5C);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar5D);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar5E);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar5F);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_iVar60);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_iVar64);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_iVar68);
}

FlverHeader::~FlverHeader()
{
}

Dummy::Dummy()
{
}

Dummy::Dummy(ifstream* flver)
{
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_position, 3);
	MemReader::ReadByteArray(flver, this->m_color, 4);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_forward, 3);
	MemReader::ReadWord(flver, (WORD*)&this->m_referenceId);
	MemReader::ReadWord(flver, (WORD*)&this->m_dummyBoneIndex);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_up, 3);
	MemReader::ReadWord(flver, (WORD*)&this->m_attackBoneIndex);
	MemReader::ReadByte(flver, (BYTE*)&this->m_bVar2E);
	MemReader::ReadByte(flver, (BYTE*)&this->m_useUpVector);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_iVar30);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_iVar34);
}

Dummy::~Dummy()
{
}

Bone::Bone()
{
}

Bone::Bone(ifstream* flver)
{
	UINT64 pos_bak;
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_position, 3);

	pos_bak = flver->tellg();
	UINT nameOffset;

	MemReader::ReadDWord(flver, (DWORD*)&nameOffset);
	wchar_t name[50];

	flver->seekg(nameOffset);
	MemReader::ReadWordArray(flver, (WORD*)name, 50);

	flver->seekg(pos_bak + 0x4);

	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_rotation, 3);
	MemReader::ReadWord(flver, (WORD*)&this->m_parentIdx);
	MemReader::ReadWord(flver, (WORD*)&this->m_childIdx);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_scale, 3);
	MemReader::ReadWord(flver, (WORD*)&this->m_nextSiblingIndex);
	MemReader::ReadWord(flver, (WORD*)&this->m_previousSiblingIndex);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_bbMin, 3);
	MemReader::ReadDWord(flver, (DWORD*)&this->m_pad);
	MemReader::ReadDWordArray(flver, (DWORD*)&this->m_bbMax, 3);
}

Bone::~Bone()
{
}

Mesh::Mesh()
{
}

Mesh::Mesh(ifstream* flver)
{

}

Mesh::~Mesh()
{
}

FaceSet::FaceSet()
{
}

FaceSet::FaceSet(ifstream* flver)
{

}

FaceSet::~FaceSet()
{
}

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::VertexBuffer(ifstream* flver)
{

}

VertexBuffer::~VertexBuffer()
{
}

BufferLayout::BufferLayout()
{
}

BufferLayout::~BufferLayout()
{
}

FlverReader::FlverReader()
{
}

FlverReader::FlverReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	ifstream flver;

	flver.open(this->m_filePath, ios::binary | ios::ate);
	this->m_fileSize = flver.tellg();
	flver.close();

	flver.open(this->m_filePath, ios::binary);
}

FlverReader::~FlverReader()
{
}