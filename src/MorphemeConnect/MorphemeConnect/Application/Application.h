#pragma once
#include <windows.h>
#include <thread>
#include <io.h>
#include <stdarg.h>
#include <strsafe.h>
#include <d3d11.h>
#include <dxgi.h>
#include <XInput.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <DirectXMath.h>
#include <vector>

#include "../framework.h"
#include "../imsequencer/ImSequencer.h"
#include "../FromsoftFormat/NMBReader/NMBReader.h"
#include "../FromsoftFormat/TimeActReader/TimeActReader.h"
#include "../FromsoftFormat/BNDReader/BNDReader.h"
#include "../FromsoftFormat/FlverReader/FlverReader.h"
#include "../cfromreader/formats/flver/flver2.hpp"
#include "../cfromreader/binders/bnd/bnd3.hpp"

using namespace cfr;

struct FlverModel
{
	DirectX::SimpleMath::Vector3 m_position;
	cfr::FLVER2* m_flver;

	FlverModel()
	{
		this->m_position = DirectX::SimpleMath::Vector3::Zero;
		this->m_flver = nullptr;
	}

	FlverModel(cfr::FLVER2* flver)
	{
		this->m_position = DirectX::SimpleMath::Vector3::Zero;
		this->m_flver = flver;
	}
};

class Application
{
public:
	struct WindowStates
	{
		bool m_settingWindow = false;
		bool m_previewSettings = false;
	} m_windowStates;

	struct Flags
	{
		bool m_loadFile = false;
		bool m_saveFile = false;
	} m_flags;

	struct EventTrackEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_targetAnimIdx = -1;
		float m_lenMult = 1.f;
		bool load_tae = false;
		std::vector<std::wstring> tae_list;
		int chr_id;

	} m_eventTrackEditorFlags;

	struct TimeActEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_taeId = -1;
		float m_lenght = 0.f;

	} m_timeActEditorFlags;

	struct ModelFlags
	{
		bool m_loaded = false;
	} m_flverModelFlags;

	NMBReader m_nmb;
	TimeActReader m_tae;
	BNDReader m_bnd;
	FlverModel m_model;

	EventTrackEditor m_eventTrackEditor;
	TimeActEditor m_timeActEditor;

	Application();
	~Application();
	void GUIStyle();
	void Update();
	void RenderGUI(const char* title);
	void RenderPopups();
	void SettingsWindow();
	void PreviewDebugManagerWindow();
	void ProcessVariables();
	void LoadFile();
	void SaveFile();
	void NetworkCleanup();
	int GetChrIdFromNmbFileName(std::wstring name);
};