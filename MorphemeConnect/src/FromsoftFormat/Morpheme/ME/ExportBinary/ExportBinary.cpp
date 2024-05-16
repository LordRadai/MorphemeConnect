#include "ExportBinary.h"
#include "../../../Utils/MemReader/MemReader.h"
#include "../../../../RMath/RMath.h"

using namespace ME;

void ME::ExportEvent(ofstream* out, int alignment, EventTrack::Event* event)
{
	MemReader::Write(out, event->m_start);
	MemReader::Write(out, event->m_duration);
	MemReader::Write(out, event->m_userData);
}

void ME::ExportAttribute(ofstream* out, int alignment, Attribute* attribute)
{

}

void ME::ExportNodeDef(ofstream* out, int alignment, NodeDef* nodeDef)
{

}

void ME::ExportNetworkDef(ofstream* out, int alignment, NetworkDef* networkDef)
{

}

void ME::ExportEventTrack(ofstream* out, int alignment, EventTrack* eventTrack)
{
	MemReader::Write(out, eventTrack->GetNumEvents());
	MemReader::Write(out, eventTrack->GetIndex());

	MemReader::Write(out, (UINT64)(32 + 12 * eventTrack->GetNumEvents()));

	MemReader::Write(out, eventTrack->GetUserData());
	MemReader::Write(out, eventTrack->GetChannelID());
	MemReader::Write(out, (UINT64)32);

	for (size_t i = 0; i < eventTrack->GetNumEvents(); i++)
		ME::ExportEvent(out, alignment, eventTrack->GetEvent(i));

	int str_len = eventTrack->GetTrackName().length() + 1;

	MemReader::WriteArray(out, eventTrack->GetTrackName().c_str(), str_len);
}

void ME::ExportStringTable(ofstream* out, int alignment, StringTable* table)
{
	MemReader::Write(out, table->GetNumEntries());
	MemReader::Write(out, table->GetDataLenght());
	MemReader::Write(out, (UINT64)32);
	MemReader::Write(out, (UINT64)(32 + table->GetNumEntries() * 4));
	MemReader::Write(out, (UINT64)(32 + table->GetNumEntries() * 8));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::Write(out, table->GetID(i));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::Write(out, table->GetOffset(i));

	for (size_t i = 0; i < table->GetNumEntries(); i++)
		MemReader::WriteArray(out, table->GetString(i).c_str(), table->GetString(i).length() + 1);
}

void ME::ExportRig(ofstream* out, int alignment, Rig* rig)
{
	UINT64 offset = 64;

	MemReader::Write(out, (UINT64)0);
	MemReader::Write(out, 0);
	MemReader::Write(out, 1.f);
	MemReader::Write(out, 0);
	MemReader::Write(out, 0);
	MemReader::Write(out, 0);
	MemReader::Write(out, 0);
	MemReader::Write(out, offset);
	MemReader::Write(out, rig->GetTrajectoryBoneID());
	MemReader::Write(out, rig->GetRootBoneID());

	Rig::Hierarchy* hierarchy = rig->GetHierarchy();
	offset += hierarchy->GetMemoryRequirements();
	MemReader::Write(out, offset);

	StringTable* stringTable = rig->GetBoneIDNamesTable();
	offset += stringTable->GetMemoryRequirements();
	offset = RMath::AlignValue(offset, alignment);

	MemReader::Write(out, offset);

	MemReader::Write(out, hierarchy->m_boneCount);
	MemReader::AlignStream(out, 8);
	MemReader::Write(out, hierarchy->m_pVar1);
	MemReader::WriteArray(out, hierarchy->m_parentIDs.data(), hierarchy->m_boneCount);

	ME::ExportStringTable(out, alignment, stringTable);

	MemReader::AlignStream(out, alignment);

	ME::ExportRigBindPose(out, alignment, rig->GetBindPose());
}

void ME::ExportRigBindPose(ofstream* out, int alignment, BindPose* bindPose)
{
	MemReader::Pad(out, 0xCD, 8);
	MemReader::Write(out, bindPose->GetFlags());
	MemReader::AlignStream(out, alignment);
	MemReader::Write(out, (UINT64)32);
	MemReader::AlignStream(out, alignment);

	UINT64 startPos = out->tellp();

	UINT64 dataSize = bindPose->GetMemoryRequirements() + 7;
	
	dataSize = RMath::AlignValue(startPos + dataSize, 16) - startPos;

	dataSize += bindPose->GetOrientation()->GetMemoryRequirements();

	MemReader::Write(out, dataSize);
	MemReader::Write(out, (UINT64)16);
	MemReader::Write(out, bindPose->GetBoneCount());
	MemReader::Write(out, bindPose->GetIsFull());
	MemReader::AlignStream(out, 4);
	MemReader::Write(out, bindPose->GetElemType());
	MemReader::AlignStream(out, 8);

	UINT64 deformationOffset = 56;
	UINT64 unkRigOffset = deformationOffset + bindPose->GetDeformationInfo()->GetMemoryRequirements();
	UINT64 orientationOffset = unkRigOffset + bindPose->GetUnkRigData()->GetMemoryRequirements();

	MemReader::Write(out, unkRigOffset);
	MemReader::Write(out, orientationOffset);
	MemReader::Write(out, deformationOffset);

	BindPose::DeformationInfo* deformationInfo = bindPose->GetDeformationInfo();

	MemReader::Write(out, deformationInfo->m_boneCount);
	MemReader::Write(out, deformationInfo->m_bitsetSize);
	MemReader::WriteArray(out, deformationInfo->m_flags.data(), deformationInfo->m_bitsetSize);

	BindPose::UnkRigData* unkRigData = bindPose->GetUnkRigData();

	MemReader::Write(out, unkRigData->m_iVar0);
	MemReader::Write(out, unkRigData->m_iVar1);
	MemReader::Write(out, unkRigData->m_iVar2);
	MemReader::Write(out, unkRigData->m_iVar3);
	MemReader::Write(out, unkRigData->m_iVar4);
	MemReader::Write(out, unkRigData->m_iVar5);

	UINT64 positionOffset = orientationOffset + 16;

	positionOffset = RMath::AlignValue(startPos + positionOffset, 16) - startPos;

	MemReader::Write(out, positionOffset);

	UINT64 rotationOffset = positionOffset + 48 + bindPose->GetOrientation()->m_position.size() * 16;

	MemReader::Write(out, rotationOffset);

	MemReader::WriteArray(out, bindPose->GetOrientation()->m_position.data(), bindPose->GetBoneCount());

	out->seekp(out->tellp() + (streampos)48);

	MemReader::WriteArray(out, bindPose->GetOrientation()->m_rotation.data(), bindPose->GetBoneCount());

	out->seekp(out->tellp() + (streampos)48);
}