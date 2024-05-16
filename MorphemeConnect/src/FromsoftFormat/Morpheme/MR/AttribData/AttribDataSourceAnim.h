#pragma once
#include "AttribData.h"

namespace MR
{
    class AttribDataSourceAnim : public AttribData
	{
	public:
		AttribDataSourceAnim();
        AttribDataSourceAnim(BYTE* pData);
		~AttribDataSourceAnim();

        int GetAnimID();
        int GetRigToAnimMapBundleID();
        float GetClipStart();
        float GetClipEnd();
        float GetAnimLen();

	private:
        UINT64 m_pAnimFile;     //The runtime module will put the referenced NSA pointer here
        UINT64 m_pVar8;
        float m_fVar10;
        float m_fVar14;
        UINT64 m_iVar18;
        UINT64 m_iVar20;
        float m_fVar28;
        float m_fVar2C;
        float m_fVar30;
        float m_fVar34;
        UINT64 m_iVar38;
        UINT64 m_iVar40;
        float m_fVar48;
        float m_fVar4C;
        UINT64 m_pVar50;
        int m_iVar5C;
        int m_animIdx;      //Used to access the FileNameLookupTable and get the NSA file pointer
        int m_rigToAnimMapBundleID;
        BYTE m_bVar6C;
        BYTE m_bVar6D;
        BYTE m_bVar6E;
        float m_clipStart;
        float m_clipEnd;
        float m_animLen;
        float m_fVar7C;
        BYTE m_bVar80;
    };
}