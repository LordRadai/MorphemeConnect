#include "TimeActEventData.h"
#include "../../../MemReader/MemReader.h"
#include "../../../../Application/Application.h"

void TimeActEventData_NoArgs::GetData(ifstream* tae)
{
	this->m_size = 16;
	this->m_data = new BYTE[16];
	MemReader::ReadByteArray(tae, this->m_data, this->m_size);
}

void TimeActEventData_NoArgs::SaveData(ofstream* tae)
{
	MemReader::WriteByteArray(tae, this->m_data, this->m_size);
}

std::string TimeActEventData_NoArgs::GetArgumentAsString()
{
	return "\n";
}

void TimeActEventData_NoArgs::ImGuiEditSection()
{
}

void TimeActEventData_Sound201::GetData(ifstream* tae)
{
	this->m_size = 18;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_soundId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVar8);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVarA);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVarC);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVarE);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVar10);
}

void TimeActEventData_Sound201::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_soundId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar8);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVarA);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVarC);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVarE);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar10);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Sound201::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d, %d, %d, %d, %d)\n", this->m_soundId, this->m_iVar4, this->m_sVar8, this->m_sVarA, this->m_sVarC, this->m_sVarE, this->m_sVar10);
	return std::string(args);
}

void TimeActEventData_Sound201::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Sound ID", &this->m_soundId, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
	ImGui::InputShort("Unk08", &this->m_sVar8, 0, 0, 0);
	ImGui::InputShort("Unk0A", &this->m_sVarA, 0, 0, 0);
	ImGui::InputShort("Unk0C", &this->m_sVarC, 0, 0, 0);
	ImGui::InputShort("Unk0E", &this->m_sVarE, 0, 0, 0);
	ImGui::InputShort("Unk10", &this->m_sVar10, 0, 0, 0);
}

void TimeActEventData_Sound202::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_soundId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_Sound202::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_soundId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Sound202::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_soundId, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_Sound202::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Sound ID", &this->m_soundId, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Ai300::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Ai300::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Ai300::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Ai300::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Ai301::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_Ai301::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Ai301::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_iVar0, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_Ai301::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Damage2200::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_index);
}

void TimeActEventData_Damage2200::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_index);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Damage2200::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_index);
	return std::string(args);
}

void TimeActEventData_Damage2200::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Index", &this->m_index, 0, 0, 0);
}

void TimeActEventData_Damage2201::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Damage2201::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Damage2201::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Damage2201::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Damage2202::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_damageParamId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_Damage2202::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_damageParamId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Damage2202::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_damageParamId, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_Damage2202::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("DamageParam ID", &this->m_damageParamId, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Damage2203::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_damageParamId);
}

void TimeActEventData_Damage2203::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_damageParamId);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Damage2203::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_damageParamId);
	return std::string(args);
}

void TimeActEventData_Damage2203::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("DamageParam ID", &this->m_damageParamId, 0, 0, 0);
}

void TimeActEventData_Bullet2300::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_index);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_Bullet2300::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_index);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Bullet2300::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_index, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_Bullet2300::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Event Index", &this->m_index, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Bullet2301::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_bulletParamId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_damageParamId);
}

void TimeActEventData_Bullet2301::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_bulletParamId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_damageParamId);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Bullet2301::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_bulletParamId, this->m_damageParamId);
	return std::string(args);
}

void TimeActEventData_Bullet2301::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("BulletParam ID", &this->m_bulletParamId, 0, 0, 0);
	ImGui::InputInt("DamageParam ID", &this->m_damageParamId, 0, 0, 0);
}

void TimeActEventData_Camera1500::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Camera1500::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Camera1500::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Camera1500::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Camera1501::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Camera1501::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Camera1501::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Camera1501::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Camera1502::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Camera1502::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Camera1502::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Camera1502::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Camera1503::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Camera1503::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Camera1503::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Camera1503::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Camera1504::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_cameraExFollowImpactParamId);
}

void TimeActEventData_Camera1504::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_cameraExFollowImpactParamId);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Camera1504::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_cameraExFollowImpactParamId);
	return std::string(args);
}

void TimeActEventData_Camera1504::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("CameraExFollowImpactParam ID", &this->m_cameraExFollowImpactParamId, 0, 0, 0);
}

void TimeActEventData_Sfx2103::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_chrFullBodySfxId);
}

void TimeActEventData_Sfx2103::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_chrFullBodySfxId);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Sfx2103::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_chrFullBodySfxId);
	return std::string(args);
}

void TimeActEventData_Sfx2103::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("CameraExFollowImpactParam ID", &this->m_chrFullBodySfxId, 0, 0, 0);
}

void TimeActEventData_Sfx2104::GetData(ifstream* tae)
{
	this->m_size = 16;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_sfxId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVarC);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVarE);
}

void TimeActEventData_Sfx2104::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_sfxId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVarC);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVarE);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Sfx2104::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d, %d, %d)\n", this->m_iVar0, this->m_sfxId, this->m_dmyPolyId, this->m_sVarC, this->m_sVarE);
	return std::string(args);
}

void TimeActEventData_Sfx2104::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
	ImGui::InputInt("Sfx ID", &this->m_sfxId, 0, 0, 0);
	ImGui::InputInt("DmyPoly ID", &this->m_dmyPolyId, 0, 0, 0);
	ImGui::InputShort("Unk0C", &this->m_sVarC, 0, 0, 0);
	ImGui::InputShort("Unk0E", &this->m_sVarE, 0, 0, 0);
}

void TimeActEventData_Sfx2106::GetData(ifstream* tae)
{
	this->m_size = 16;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_sfxId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVarC);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar10);
}

void TimeActEventData_Sfx2106::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_sfxId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVarC);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar10);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Sfx2106::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d, %d, %d)\n", this->m_iVar0, this->m_sfxId, this->m_dmyPolyId, this->m_iVarC, this->m_iVar10);
	return std::string(args);
}

void TimeActEventData_Sfx2106::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
	ImGui::InputInt("Sfx ID", &this->m_sfxId, 0, 0, 0);
	ImGui::InputInt("DmyPoly ID", &this->m_dmyPolyId, 0, 0, 0);
	ImGui::InputInt("Unk0C", &this->m_iVarC, 0, 0, 0);
	ImGui::InputInt("Unk10", &this->m_iVar10, 0, 0, 0);
}

void TimeActEventData_FootEffect2402::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_id);
}

void TimeActEventData_FootEffect2402::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_id);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_FootEffect2402::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_id);
	return std::string(args);
}

void TimeActEventData_FootEffect2402::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("ID", &this->m_id, 0, 0, 0);
}

void TimeActEventData_Weapon2500::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadWord(tae, (WORD*)&this->m_sVar0);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVar2);
}

void TimeActEventData_Weapon2500::SaveData(ofstream* tae)
{
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar0);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar2);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Weapon2500::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_sVar0, this->m_sVar2);
	return std::string(args);
}

void TimeActEventData_Weapon2500::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputShort("Unk00", &this->m_sVar0, 0, 0, 0);
	ImGui::InputShort("Unk02", &this->m_sVar2, 0, 0, 0);
}

void TimeActEventData_Weapon2501::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadWord(tae, (WORD*)&this->m_sVar0);
	MemReader::ReadWord(tae, (WORD*)&this->m_sVar2);
}

void TimeActEventData_Weapon2501::SaveData(ofstream* tae)
{
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar0);
	MemReader::WriteWord(tae, (WORD*)&this->m_sVar2);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Weapon2501::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_sVar0, this->m_sVar2);
	return std::string(args);
}

void TimeActEventData_Weapon2501::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputShort("Unk00", &this->m_sVar0, 0, 0, 0);
	ImGui::InputShort("Unk02", &this->m_sVar2, 0, 0, 0);
}

void TimeActEventData_DamageAction111000::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_DamageAction111000::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_DamageAction111000::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_iVar0, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_DamageAction111000::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Item220200::GetData(ifstream* tae)
{
	this->m_size = 16;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_type);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_index);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar8);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVarC);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_fVar10);
}

void TimeActEventData_Item220200::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_type);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_index);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar8);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVarC);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fVar10);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Item220200::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d, %d, %.3f)\n", this->m_type, this->m_index, this->m_iVar8, this->m_iVarC, this->m_fVar10);
	return std::string(args);
}

void TimeActEventData_Item220200::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Type", &this->m_type, 0, 0, 0);
	ImGui::InputInt("Index", &this->m_index, 0, 0, 0);
	ImGui::InputInt("Unk08", &this->m_iVar8, 0, 0, 0);
	ImGui::InputInt("Unk0C", &this->m_iVarC, 0, 0, 0);
	ImGui::InputFloat("Unk10", &this->m_fVar10, 0, 0, 0);
}

void TimeActEventData_Model260001::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_type);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
}

void TimeActEventData_Model260001::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_type);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model260001::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d)\n", this->m_type, this->m_iVar4);
	return std::string(args);
}

void TimeActEventData_Model260001::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Type", &this->m_type, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
}

void TimeActEventData_Model260002::GetData(ifstream* tae)
{
	this->m_size = 12;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar4);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar8);
}

void TimeActEventData_Model260002::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar4);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar8);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model260002::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d)\n", this->m_iVar0, this->m_iVar4, this->m_iVar8);
	return std::string(args);
}

void TimeActEventData_Model260002::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Type", &this->m_iVar0, 0, 0, 0);
	ImGui::InputInt("Unk04", &this->m_iVar4, 0, 0, 0);
	ImGui::InputInt("Unk08", &this->m_iVar8, 0, 0, 0);
}

void TimeActEventData_Model260004::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_fVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_fVar4);
}

void TimeActEventData_Model260004::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model260004::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%.3f, %.3f)\n", this->m_fVar0, this->m_fVar4);
	return std::string(args);
}

void TimeActEventData_Model260004::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputFloat("Unk00", &this->m_fVar0, 0, 0, 0);
	ImGui::InputFloat("Unk04", &this->m_fVar4, 0, 0, 0);
}

void TimeActEventData_Model260005::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_fVar0);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_fVar4);
}

void TimeActEventData_Model260005::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fVar0);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_fVar4);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model260005::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%.3f, %.3f)\n", this->m_fVar0, this->m_fVar4);
	return std::string(args);
}

void TimeActEventData_Model260005::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputFloat("Unk00", &this->m_fVar0, 0, 0, 0);
	ImGui::InputFloat("Unk04", &this->m_fVar4, 0, 0, 0);
}

void TimeActEventData_Model260006::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Model260006::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model260006::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Model260006::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Model270000::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_partsId);
}

void TimeActEventData_Model270000::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_partsId);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Model270000::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_partsId);
	return std::string(args);
}

void TimeActEventData_Model270000::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Parts ID", &this->m_partsId, 0, 0, 0);
}

void TimeActEventData_Move280100::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_turnRate);
}

void TimeActEventData_Move280100::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_turnRate);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Move280100::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%.3f)\n", this->m_turnRate);
	return std::string(args);
}

void TimeActEventData_Move280100::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputFloat("Turn Rate", &this->m_turnRate, 0, 0, 0);
}

void TimeActEventData_Event300000::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Event300000::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Event300000::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Event300000::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Event300100::GetData(ifstream* tae)
{
	this->m_size = 12;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_padRumbleParamId);
	MemReader::ReadDWord(tae, (DWORD*)&this->m_intensity);
}

void TimeActEventData_Event300100::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_dmyPolyId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_padRumbleParamId);
	MemReader::WriteDWord(tae, (DWORD*)&this->m_intensity);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Event300100::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %.3f)\n", this->m_dmyPolyId, this->m_padRumbleParamId, this->m_intensity);
	return std::string(args);
}

void TimeActEventData_Event300100::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("DmyPoly ID", &this->m_dmyPolyId, 0, 0, 0);
	ImGui::InputInt("PadRumbleParam ID", &this->m_padRumbleParamId, 0, 0, 0);
	ImGui::InputFloat("Intensity", &this->m_intensity, 0, 0, 0);
}

void TimeActEventData_Event300200::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Event300200::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Event300200::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Event300200::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_Event300300::GetData(ifstream* tae)
{
	this->m_size = 4;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_iVar0);
}

void TimeActEventData_Event300300::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_iVar0);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_Event300300::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d)\n", this->m_iVar0);
	return std::string(args);
}

void TimeActEventData_Event300300::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("Unk00", &this->m_iVar0, 0, 0, 0);
}

void TimeActEventData_SpEffect310000::GetData(ifstream* tae)
{
	this->m_size = 8;

	MemReader::ReadDWord(tae, (DWORD*)&this->m_spEffectId);
	MemReader::ReadWord(tae, (WORD*)&this->m_type);
	MemReader::ReadWord(tae, (WORD*)&this->m_mode);
}

void TimeActEventData_SpEffect310000::SaveData(ofstream* tae)
{
	MemReader::WriteDWord(tae, (DWORD*)&this->m_spEffectId);
	MemReader::WriteWord(tae, (WORD*)&this->m_type);
	MemReader::WriteWord(tae, (WORD*)&this->m_mode);

	UINT64 pos = tae->tellp();
	int remainder = pos % 16;

	if (remainder != 0)
	{
		BYTE* padding = new BYTE[16 - remainder];

		MemReader::WriteByteArray(tae, padding, 16 - remainder);
	}
}

std::string TimeActEventData_SpEffect310000::GetArgumentAsString()
{
	char args[100];

	sprintf_s(args, "(%d, %d, %d)\n", this->m_spEffectId, this->m_type, this->m_mode);
	return std::string(args);
}

void TimeActEventData_SpEffect310000::ImGuiEditSection()
{
	ImGui::Text("Arguments");

	ImGui::InputInt("SpEffect ID", &this->m_spEffectId, 0, 0, 0);
	ImGui::InputShort("Type", &this->m_type, 0, 0, 0);
	ImGui::InputShort("Mode", &this->m_mode, 0, 0, 0);
}