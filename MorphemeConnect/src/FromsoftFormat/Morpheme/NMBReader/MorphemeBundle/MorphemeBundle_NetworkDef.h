#pragma once
#include "MorphemeBundle.h"
#include "NodeAttrib/NodeAttribUnknown.h"
#include "NodeAttrib/NodeAttribBool.h"
#include "NodeAttrib/NodeAttribSourceAnim.h"
#include "NodeAttrib/NodeAttribSourceEventTrack.h"

enum NodeType
{
    NodeType_NetworkInstance = 9,
    NodeType_StateMachine = 10,
    NodeType_ControlParameterFloat = 20,
    NodeType_ControlParameterVector3 = 21,
    NodeType_ControlParameterBool = 23,
    NodeType_ControlParameterInt = 24,
    NodeType_NodeAnimSyncEvents = 104,
    Nodetype_ShareChildren_105 = 105,
    NodeType_Blend2SyncEvents = 107,
    NodeType_Blend2Additive = 108,
    NodeType_Share1Child1InputCP_109,
    NodeType_ShareCreateFloatOutputAttribute_110 = 110,
    NodeType_ShareCreateFloatOutputAttribute_112 = 112,
    NodeType_Blend2Additive_2 = 114,
    NodeType_TwoBoneIK = 120,
    NodeType_LockFoot = 121,
    NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_120 = 122,
    NodeType_Share1Child1InputCP = 125,
    NodeType_Freeze = 126,
    NodeType_ShareChildrenOptionalInputCPs = 129,
    NodeType_Switch = 131,
    NodeType_ShareChildren = 134,
    NodeType_ShareChildren_2 = 135,
    NodeType_ShareUpdateConnections1Child2OptionalInputCP = 136,
    NodeType_PredictiveUnevenTerrain = 138,
    NodeType_OperatorSmoothDamp = 142,
    NodeType_ShareCreateVector3OutputAttribute = 144,
    NodeType_OperatorRandomFloat = 146,
    NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_150 = 150,
    NodeType_ShareChild1InputCP_151 = 151,
    NodeType_ShareChildren_153 = 153,
    NodeType_SubtractiveBlend = 170,
    NodeType_TransitSyncEvents = 400,
    NodeType_Transit = 402,
    NodeType_Share1Child1OptionalInputCP = 500,
    Unk550 = 550,
};

struct sSmStateList {
    uint32_t m_numStateMachinesNodes;
    int field1_0x4;
    short* m_stateMachineNodeIDs;
};

struct StringTable {
    uint32_t m_NumEntries;
    uint32_t m_DataLenght;
    uint32_t* m_IDs;
    uint32_t* m_Offsets;
    char* m_Data;
};

struct sMorphemeNodeDef {
    int node_type;
    BYTE field1_0x4;
    BYTE field2_0x5;
    short field3_0x6;
    BYTE* array;
};

struct sMessageDef {
    int message_id;
    int field1_0x4;
    int node_count;
    int field3_0xc;
    short* node_array;
};

struct NodeDataSet
{
    NodeAttribBase* m_attrib;
    UINT64 m_size;
    int m_alignment;
    int m_iVar0;

    void SaveToFile(ofstream* out);
};

struct NodeDef {
    NodeType m_nodeTypeID = NodeType_NetworkInstance;
    BYTE m_flags1 = 0;
    BYTE m_flags2 = 0;
    short m_nodeID = 0;
    short m_parentNodeID = 0;
    uint16_t m_numChildNodeIDs = 0;
    uint16_t field7_0xc = 0;
    BYTE m_numControlParamAndOpNodeIDs = 0;
    BYTE field8_0xf = 0;
    uint16_t m_numDataSet = 0;
    uint16_t field10_0x12 = 0;
    int padding = 0;
    UINT64 m_owningNetworkDef = 0; //Always 0
    std::vector<short> m_childNodeIDs;
    std::vector<int> m_controlParamAndOpNodeIDs;
    NodeDataSet* m_nodeData;
    short field16_0x38 = 0;
    short field17_0x3a = 0;
    int field18_0x3c = 0;
    uint64_t field19_0x40 = 0;
    uint64_t field20_0x48 = 0;
    UINT64 deleteFn = NULL;
    UINT64 updateFn = NULL;
    UINT64 unknownFn = NULL;
    UINT64 initFn = NULL;
    UINT64 transitFn = NULL;
    sMorphemeNodeDef* node_def = NULL;
    BYTE field27_0x80 = 0;
    BYTE padding1[7];
    uint64_t field35_0x88 = 0;
    uint64_t field36_0x8C = 0;

    NodeDef() {}
    NodeDef(BYTE* data);

    bool LoadNodeData(NodeType type, NodeDataSet* dst, BYTE* srcNodeData, int setCount);
    void SaveToFile(ofstream* out);
    int CalculateNodeSize();
};

class MorphemeBundle_NetworkDef : public MorphemeBundle_Base
{
public:
	struct BundleData_NetworkDef
	{
        NodeDef network_node_def;
        uint32_t m_numNodes;
        uint32_t field2_0x94;
        NodeDef** m_nodes;
        short field4_0xa0;
        short field5_0xa2;
        int field6_0xa4;
        uint64_t field7_0xa8;
        sSmStateList* sm_state_list;
        uint64_t field9_0xb8;
        sSmStateList* sm_unk_list;
        StringTable* m_nodeIDNamesTable;
        StringTable* m_requestIDNamesTable;
        StringTable* m_eventTrackIDNamesTable;
        uint64_t field14_0xe0;
        uint64_t field15_0xe8;
        uint64_t field16_0xf0;
        int message_count;
        int field18_0xfc;
        sMessageDef** message_def;
        int node_type_count;
        int field21_0x10c;
        sMorphemeNodeDef** node_def_list;
        int field23_0x118;
        int field24_0x11c;
        int field25_0x120;
        int field26_0x124;
        int field27_0x128;
        int field28_0x12c;
        uint64_t field29_0x130;
        uint64_t field30_0x138;

        BundleData_NetworkDef(BYTE* data);
	};

    BundleData_NetworkDef* m_data;

    MorphemeBundle_NetworkDef();
    MorphemeBundle_NetworkDef(MorphemeBundle* bundle);
    ~MorphemeBundle_NetworkDef();

    void WriteBinary(ofstream* out);
    int CalculateBundleSize();
};