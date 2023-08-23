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
#include "../NMBReader/NMBReader.h"
#include "../TimeActReader/TimeActReader.h"

class Application
{
public:
	struct WindowStates
	{
		bool m_settingWindow = false;
		bool m_previewDebugManager = false;
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

	NMBReader nmb;
	TimeActReader tae;
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