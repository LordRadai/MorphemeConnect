#include <fstream>
#include <Windows.h>
#pragma once

using namespace std;

class TimeActEventData
{
public:
	int m_size;

	virtual void GetData(ifstream* tae) { return; }
	virtual void SaveData(ofstream* tae) { return; }
	virtual std::string GetArgumentAsString() { return ""; }
	virtual void ImGuiEditSection() { return; }
};

class TimeActEventData_NoArgs : public TimeActEventData
{
public:
	BYTE* m_data;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Sound201 : public TimeActEventData
{
public:
	int m_soundId;
	int m_iVar4;
	short m_sVar8;
	short m_sVarA;
	short m_sVarC;
	short m_sVarE;
	short m_sVar10;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Sound202 : public TimeActEventData
{
public:
	int m_soundId;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Ai300 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Ai301 : public TimeActEventData
{
public:
	int m_iVar0;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Damage2200 : public TimeActEventData
{
public:
	int m_index;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Damage2201 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Damage2202: public TimeActEventData
{
public:
	int m_damageParamId;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Damage2203 : public TimeActEventData
{
public:
	int m_damageParamId;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Bullet2300 : public TimeActEventData
{
public:
	int m_index;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Bullet2301 : public TimeActEventData
{
public:
	int m_bulletParamId;
	int m_damageParamId;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Camera1500 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Camera1501 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Camera1502 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Camera1503 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Camera1504 : public TimeActEventData
{
public:
	int m_cameraExFollowImpactParamId;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Sfx2103 : public TimeActEventData
{
public:
	int m_chrFullBodySfxId;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Sfx2104 : public TimeActEventData
{
public:
	int m_iVar0;
	int m_sfxId;
	int m_dmyPolyId;
	short m_sVarC;
	short m_sVarE;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Sfx2106 : public TimeActEventData
{
public:
	int m_iVar0;
	int m_sfxId;
	int m_dmyPolyId;
	int m_iVarC;
	int m_iVar10;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_FootEffect2402 : public TimeActEventData
{
public:
	int m_id;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Weapon2500 : public TimeActEventData
{
public:
	short m_sVar0;
	short m_sVar2;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Weapon2501 : public TimeActEventData
{
public:
	short m_sVar0;
	short m_sVar2;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_DamageAction111000 : public TimeActEventData
{
public:
	int m_iVar0;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Item220200 : public TimeActEventData
{
public:
	int m_type;
	int m_index;
	int m_iVar8;
	int m_iVarC;
	float m_fVar10;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model260001 : public TimeActEventData
{
public:
	int m_type;
	int m_iVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model260002 : public TimeActEventData
{
public:
	int m_iVar0;
	int m_iVar4;
	int m_iVar8;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model260004 : public TimeActEventData
{
public:
	float m_fVar0;
	float m_fVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model260005 : public TimeActEventData
{
public:
	float m_fVar0;
	float m_fVar4;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model260006 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Model270000 : public TimeActEventData
{
public:
	int m_partsId;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Move280100 : public TimeActEventData
{
public:
	float m_turnRate;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Event300000 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Event300100 : public TimeActEventData
{
public:
	int m_dmyPolyId;
	int m_padRumbleParamId;
	float m_intensity;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Event300200 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_Event300300 : public TimeActEventData
{
public:
	int m_iVar0;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};

class TimeActEventData_SpEffect310000 : public TimeActEventData
{
public:
	int m_spEffectId;
	short m_type;
	short m_mode;

	void GetData(ifstream* tae);
	void SaveData(ofstream* tae);
	std::string GetArgumentAsString();
	void ImGuiEditSection();
};