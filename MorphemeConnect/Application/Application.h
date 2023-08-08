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

#include "../Timeline/Timeline.h"
#include "../TimeAct/TimeAct.h"
#include "../NMBReader/NMBReader.h"

class Application
{
public:
	struct Flags
	{
		bool style_editor = false;
		bool load_file = false;
	} m_flags;

	struct EventTrackEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_targetAnimIdx = 0;
		float m_lenMult = 1.f;

	} m_eventTrackEditorFlags;

	MorphemeEventTrackList m_eventTrackList;
	EventTrackEditor m_eventTrackEditor;

	NMBReader nmb;

	Application();
	~Application();
	void GUIStyle();
	void Update();
	void RenderGUI(const char* title);
	void ProcessVariables();
	void LoadFile();
	void Dockspace(ImGuiID dockSpace);
	void NetworkCleanup();
};