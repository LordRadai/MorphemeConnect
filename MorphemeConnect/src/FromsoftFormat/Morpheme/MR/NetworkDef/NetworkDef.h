#pragma once
#include "../Common/Common.h"
#include "../NodeDef/NodeDef.h"

enum MessageType
{
    MessageType_Invalid = -1,
    MessageType_Request = 10,
    MessageType_RetargetOffset = 102,
    MessageType_RetargetCharacterScale = 103,
    MessageType_ScaleRig = 104,
};

namespace MR
{
    class NodeGroup
    {
    public:
        NodeGroup();
        NodeGroup(BYTE* pData);
        ~NodeGroup();

    private:
        int m_count;
        std::vector<short> m_nodes;
    };

    class UnkNodeData
    {
    public:
        UnkNodeData();
        UnkNodeData(BYTE* pData);
        ~UnkNodeData();

    private:
        UINT64 m_iVar0;
        UINT64 m_iVar1;
        std::vector<short> m_data;
        short m_sVar3;
        short m_count;
    };

    class FunctionDef
    {
    public:
        FunctionDef();
        FunctionDef(UINT64* pData, int count);
        ~FunctionDef();

    private:
        std::vector<UINT64> m_data;
    };

    class FunctionDefList
    {
    public:
        FunctionDefList();
        FunctionDefList(BYTE* pData);
        ~FunctionDefList();

    private:
        int m_numFunctions;
        int m_arraySize;
        std::vector<UINT64> m_offsets;
        std::vector<FunctionDef> m_functionDefs;
    };

    class MessageDef
    {
    public:
        MessageDef();
        MessageDef(BYTE* pData);
        ~MessageDef();

    private:
        int m_id;
        MessageType m_type;
        int m_validNodeCount;
        UINT64 m_iVar0;
        int m_iVar1;
        UINT64 m_pVar2;
        UINT64 m_pVar3;
        std::vector<short> m_validNodeIDs;
    };

    class NodeTypeDef
    {
    public:
        NodeTypeDef();
        NodeTypeDef(BYTE* pData);
        ~NodeTypeDef();

    private:
        NodeType m_typeID;
        bool m_bVar1;
        int m_size;
        std::vector<BYTE> m_data;
    };

    class RigIndices
    {
    public:
        RigIndices();
        RigIndices(int* pData, int count);
        ~RigIndices();

    private:
        std::vector<int> m_indices;
    };

    class RigData
    {
    public:
        RigData();
        RigData(BYTE* pBase, UINT64* pData, int rigCount, int boneCount);
        ~RigData();

    private:
        std::vector<UINT64> m_offsets;
        std::vector<RigIndices> m_rigIndices;
    };

    class NetworkDef
    {
    public:
        NetworkDef();
        NetworkDef(BYTE* pData);
        ~NetworkDef();

    private:
        NodeDef m_networkInstance;
        int m_numNodes;
        std::vector<NodeDef*> m_nodes;
        short m_numAnimSets;
        NodeGroup m_nodeGroup1;
        NodeGroup m_stateMachineNodeGroup;
        NodeGroup m_emitRequestNodeGroup;
        NodeGroup m_nodeGroup2;
        StringTable m_nodeIDNamesTable;
        StringTable m_requestIDNamesTable;
        StringTable m_eventTrackIDNamesTable;
        UnkNodeData m_unkNodeData;
        FunctionDefList m_functionDefList1;
        FunctionDefList m_functionDefList2;
        int m_numRequests;
        std::vector<MessageDef*> m_messageDefs;
        int m_numNodeTypes;
        std::vector<NodeTypeDef*> m_nodeTypeDefs;
        int m_boneCount;
        int m_iVar19;
        short m_sVar20;
        int m_iVar21;
        UINT64 m_pVar22;
        RigData* m_rigData;
        RigData* m_mirroredRigData;
    };
}