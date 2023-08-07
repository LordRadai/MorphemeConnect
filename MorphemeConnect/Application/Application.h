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
	bool style_editor = false;
	bool load_file = false;
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