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

class Application
{
public:
	struct Flags
	{
		bool style_editor = false;
		bool load_file = false;
		bool save_file = false;
	} m_flags;

	struct EventTrackEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_targetAnimIdx = -1;
		float m_lenMult = 1.f;

	} m_eventTrackEditorFlags;

	NMBReader nmb;
	EventTrackEditor m_eventTrackEditor;

	Application();
	~Application();
	void GUIStyle();
	void Update();
	void RenderGUI(const char* title);
	void ProcessVariables();
	void LoadFile();
	void SaveFile();
	void NetworkCleanup();
};