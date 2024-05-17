#include "NodeDef.h"
#include "../../../Utils/MemReader/MemReader.h"

using namespace MR;

Attribute::Attribute()
{
	this->m_data = nullptr;
	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar0 = 0;
}

Attribute::Attribute(BYTE* pData, UINT64 pBase)
{
	BYTE* pOffset = *(BYTE**)(pData) + pBase;

	if (pOffset != nullptr)
		this->m_data = AttribDataFactory(pOffset);

	this->m_dataSize = *(UINT64*)(pData + 0x8);
	this->m_dataAlignment = *(int*)(pData + 0x10);
	this->m_iVar0 = *(int*)(pData + 0x14);
}

Attribute::~Attribute()
{
}

AttribData* Attribute::GetAttribData()
{
	return this->m_data;
}

AttribData* Attribute::AttribDataFactory(BYTE* pData)
{
	this->m_data = new AttribData(pData);

	switch (this->m_data->GetAttribType())
	{
	case ATTRIB_TYPE_BOOL:
		return new AttribDataBool(pData);
	case ATTRIB_TYPE_UINT:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_INT:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_FLOAT:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_VECTOR3:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_VECTOR4:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BOOL_ARRAY:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_UINT_ARRAY:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_INT_ARRAY:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_FLOAT_ARRAY:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_UPDATE_PLAYBACK_POS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PLAYBACK_POS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_UPDATE_SYNC_EVENT_PLAYBACK_POS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRANSFORM_BUFFER:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRAJECTORY_DELTA_TRANSFORM:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRANSFORM:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_VELOCITY:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SYNC_EVENT_TRACK:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SAMPLED_EVENTS_BUFFER:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_DURATION_EVENT_TRACK_SET:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RIG:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SOURCE_ANIM:
		return new AttribDataSourceAnim(pData);
	case ATTRIB_TYPE_SOURCE_EVENT_TRACKS:
		return new AttribDataSourceEventTrack(pData);
	case ATTRIB_TYPE_HEAD_LOOK_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_HEAD_LOOK_CHAIN:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_GUN_AIM_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_GUN_AIM_IK_CHAIN:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TWO_BONE_IK_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TWO_BONE_IK_CHAIN:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_LOCK_FOOT_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_LOCK_FOOT_CHAIN:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_LOCK_FOOT_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_HIPS_IK_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_HIPS_IK_ANIM_SET_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_CLOSEST_ANIM_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_CLOSEST_ANIM_DEF_ANIM_SET:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_CLOSEST_ANIM_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_STATE_MACHINE_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_STATE_MACHINE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_CHARACTER_PROPERTIES:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_CHARACTER_CONTROLLER_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_SETUP_ANIM_SET:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_INITIALISATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_GROUPER_CONFIG:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_FLOAT_OPERATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_2_FLOAT_OPERATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SMOOTH_FLOAT_OPERATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RATE_OF_CHANGE_OPERATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RANDOM_FLOAT_OPERATION:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RANDOM_FLOAT_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_NOISE_GEN_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SWITCH_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RAY_CAST_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRANSIT_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRANSIT_SYNC_EVENTS_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_TRANSIT_SYNC_EVENTS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_DEAD_BLEND_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_DEAD_BLEND_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BLEND_NXM_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_ANIM_MIRRORED_MAPPING:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PLAYBACK_POS_INIT:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_EMITTED_MESSAGE_MAP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_SETUP:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_FOOT_LIFTING_TARGET:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_CHAIN:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_IK_PREDICTION_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_FOOT_LIFTING_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_PREDICTION_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SCATTER_BLEND_ANALYSIS_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SCATTER_BLEND_1D_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SCATTER_BLEND_2D_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_EMIT_MESSAGE_ON_CP_VALUE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_PHYSICS_INFO_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_JOINT_LIMITS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BLEND_FLAGS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_BLEND_WEIGHTS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_FEATHER_BLEND2_CHANNEL_ALPHAS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RETARGET_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RIG_RETARGET_MAPPING:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_SCALECHARACTER_STATE:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_RETARGET_STORAGE_STATS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_C_C_OVERRIDE_PROPERTIES_DEF:
		return new AttribDataUnknown(pData, this->m_dataSize);
	case ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS:
		return new AttribDataUnknown(pData, this->m_dataSize);
	default:
		return new AttribDataUnknown(pData, this->m_dataSize);
	}
}

NodeDef::NodeDef()
{
	this->m_typeID = NodeType_Invalid;
	this->m_flags = 0;
	this->m_nodeID = 0;
	this->m_parentID = -1;
	this->m_numChildNodeIDs = 0;
	this->m_sVar5 = 0;
	this->m_numControlParamAndOpNodeIDs = 0;
	this->m_bVar7 = 0;
	this->m_numAttributes = 0;
	this->m_sVar9 = 0;
	this->m_pOwningNetworkNode = 0;
	this->m_sVar14 = 0;
	this->m_sVar15 = 0;
	this->m_pVar16 = 0;
	this->m_pDeleteFn = 0;
	this->m_pUpdateFn = 0;
	this->m_pUnkFn = 0;
	this->m_pTransitFn = 0;
	this->m_pNodeTypeDef = 0;
	this->m_pVar24 = 0;
	this->m_bVar25 = 0;
	this->m_pVar26 = 0;
}

NodeDef::NodeDef(BYTE* pData)
{
	this->m_typeID = *(NodeType*)(pData);
	this->m_flags = *(short*)(pData + 0x4);
	this->m_nodeID = *(short*)(pData + 0x6);
	this->m_parentID = *(short*)(pData + 0x8);
	this->m_numChildNodeIDs = *(short*)(pData + 0xA);
	this->m_sVar5 = *(short*)(pData + 0xC);
	this->m_numControlParamAndOpNodeIDs = *(BYTE*)(pData + 0xE);
	this->m_bVar7 = *(BYTE*)(pData + 0xF);
	this->m_numAttributes = *(short*)(pData + 0x10);
	this->m_sVar9 = *(short*)(pData + 0x12);
	this->m_pOwningNetworkNode = *(UINT64*)(pData + 0x18); assert(this->m_pOwningNetworkNode == 0);

	if (this->m_numChildNodeIDs > 0)
	{
		this->m_childNodeIDs.reserve(this->m_numChildNodeIDs);

		UINT64 offset = *(UINT64*)(pData + 0x20);
		short* pChildNodes = (short*)(pData + offset);

		for (size_t i = 0; i < this->m_numChildNodeIDs; i++)
			this->m_childNodeIDs.push_back(pChildNodes[i]);
	}

	if (this->m_numControlParamAndOpNodeIDs > 0)
	{
		this->m_controlParamAndOpNodeIDs.reserve(this->m_numControlParamAndOpNodeIDs);

		UINT64 offset = *(UINT64*)(pData + 0x28);
		int* pInputNodes = (int*)(pData + offset);

		for (size_t i = 0; i < this->m_numControlParamAndOpNodeIDs; i++)
			this->m_controlParamAndOpNodeIDs.push_back(pInputNodes[i]);
	}

	if (this->m_numAttributes > 0)
	{
		this->m_attributes.reserve(this->m_numAttributes);
		UINT64 offset = *(UINT64*)(pData + 0x30);
		Attribute* pAttribList = (Attribute*)(pData + offset);

		for (size_t i = 0; i < this->m_numAttributes; i++)
			this->m_attributes.push_back(new Attribute((BYTE*)&pAttribList[i], (UINT64)pData));
	}

	this->m_sVar14 = *(short*)(pData + 0x38);
	this->m_sVar15 = *(short*)(pData + 0x3A);
	this->m_pVar16 = *(UINT64*)(pData + 0x40);
	this->m_pDeleteFn = *(UINT64*)(pData + 0x48);
	this->m_pUpdateFn = *(UINT64*)(pData + 0x50);
	this->m_pUnkFn = *(UINT64*)(pData + 0x58);
	this->m_pInitFn = *(UINT64*)(pData + 0x60);
	this->m_pTransitFn = *(UINT64*)(pData + 0x68);
	this->m_pNodeTypeDef = *(UINT64*)(pData + 0x70);
	this->m_pVar24 = *(UINT64*)(pData + 0x78);
	this->m_bVar25 = *(bool*)(pData + 0x80);
	this->m_pVar26 = *(UINT64*)(pData + 0x88);
}

NodeDef::~NodeDef()
{
}