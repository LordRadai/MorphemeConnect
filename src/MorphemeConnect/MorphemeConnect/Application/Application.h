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
#include <vector>

#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

#include "../framework.h"
#include "../imsequencer/ImSequencer.h"
#include "../FromsoftFormat/NMBReader/NMBReader.h"
#include "../FromsoftFormat/TimeActReader/TimeActReader.h"
#include "../FromsoftFormat/BNDReader/BNDReader.h"
#include "../FromsoftFormat/FlverReader/FlverReader.h"
#include "../fromloader/fromloader.h"

using namespace cfr;

struct FlverModel
{
	struct Settings
	{
		bool m_xray = false;
	} m_settings;

	bool m_loaded = false;

	DirectX::SimpleMath::Vector3 m_position = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 m_focusPoint = DirectX::SimpleMath::Vector3::Zero;

	FLVER2* m_flver = nullptr;
	std::vector<DirectX::VertexPositionColor> verts;

	FlverModel()
	{
		this->m_position = DirectX::SimpleMath::Vector3::Zero;
	}

	FlverModel(UMEM* umem)
	{
		this->m_loaded = false;
		this->verts.clear();

		if (this->m_loaded)
			delete this->m_flver;

		this->m_position = DirectX::SimpleMath::Vector3::Zero;
		this->m_flver = new FLVER2(umem);

		float focus_y = (this->m_flver->header.boundingBoxMax.y + this->m_flver->header.boundingBoxMin.y) / 2;

		this->m_focusPoint = this->m_position + DirectX::SimpleMath::Vector3(0, focus_y, 0);

		this->GetModelVertices();

		this->m_loaded = true;
	}

	~FlverModel()
	{
	}

	void GetModelVertices()
	{
		if (m_flver == nullptr)
			return;

		constexpr float scale = 2.f;

		DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 1.f);

		DirectX::XMMATRIX translation = DirectX::XMMatrixTranslationFromVector(this->m_position);
		DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationX(-DirectX::XM_PIDIV2) * DirectX::XMMatrixRotationY(DirectX::XM_PI);
		DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(scale, scale, scale);
		DirectX::XMMATRIX world = rotation * translation * scaling;

		for (int i = 0; i < m_flver->header.meshCount; i++)
		{
			cfr::FLVER2::Mesh* mesh = &m_flver->meshes[i];

			int vertexCount = 0;

			for (int vbi = 0; vbi < mesh->header.vertexBufferCount; vbi++)
			{
				int vb_index = m_flver->meshes[i].vertexBufferIndices[vbi];
				vertexCount += m_flver->vertexBuffers[vb_index].header.vertexCount;
			}

			int uvCount = 0;
			int colorCount = 0;
			int tanCount = 0;

			m_flver->getVertexData(i, &uvCount, &colorCount, &tanCount);

			uint64_t lowest_flags = LLONG_MAX;
			cfr::FLVER2::Faceset* facesetp = nullptr;

			for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
			{
				int fsindex = mesh->facesetIndices[mfsi];
				if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
				{
					facesetp = &this->m_flver->facesets[fsindex];
					lowest_flags = facesetp->header.flags;
				}
			}

			facesetp->triangulate();

			if (facesetp != nullptr)
			{
				for (size_t j = 0; j < facesetp->triCount; j += 3)
				{
					int vertexIndex = facesetp->triList[j];

					float x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
					float y = mesh->vertexData->positions[(vertexIndex * 3) + 1];
					float z = mesh->vertexData->positions[(vertexIndex * 3) + 2];

					DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(x, y, z);
					pos = DirectX::SimpleMath::Vector3::Transform(pos, world);

					DirectX::VertexPositionColor v1 = DirectX::VertexPositionColor(pos, color);

					this->verts.push_back(v1);

					vertexIndex = facesetp->triList[j + 1];

					x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
					y = mesh->vertexData->positions[(vertexIndex * 3) + 1];
					z = mesh->vertexData->positions[(vertexIndex * 3) + 2];

					pos = DirectX::SimpleMath::Vector3(x, y, z);
					pos = DirectX::SimpleMath::Vector3::Transform(pos, world);

					DirectX::VertexPositionColor v2 = DirectX::VertexPositionColor(pos, color);
					this->verts.push_back(v2);

					vertexIndex = facesetp->triList[j + 2];

					x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
					y = mesh->vertexData->positions[(vertexIndex * 3) + 1];
					z = mesh->vertexData->positions[(vertexIndex * 3) + 2];

					pos = DirectX::SimpleMath::Vector3(x, y, z);
					pos = DirectX::SimpleMath::Vector3::Transform(pos, world);

					DirectX::VertexPositionColor v3 = DirectX::VertexPositionColor(pos, color);
					this->verts.push_back(v3);
				}
			}
		}
	}

	void UpdateModel()
	{
		if (m_flver == nullptr)
			return;

		DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 1.f);

		if (this->m_settings.m_xray)
			color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 0.f);

		for (int i = 0; i < this->verts.size(); i++)
			verts[i].color = color;
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
		bool m_saveAll = false;
	} m_flags;

	struct TimeActFlags
	{
		bool m_addTimeAct = false;
		bool m_deleteTimeAct = false;
		int m_addTimeActId = 0;
		int m_deleteTimeActId = -1;
	} m_timeActFlags;

	struct EventTrackEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_selectedAnimIdx = -1;
		std::vector<BYTE> m_edited;

		int m_targetAnimIdx = -1;
		float m_lenMult = 1.f;
		bool m_loadTae = false;
		std::vector<std::wstring> m_taeList;
		int chr_id;
	} m_eventTrackEditorFlags;

	struct TimeActEditorFlags
	{
		bool m_load = false;
		bool m_save = false;
		int m_selectedTimeActIdx = -1;
		std::vector<BYTE> m_edited;
		int m_taeId = -1;
		float m_eventTrackActionTimeActStart = 0.f;
		float m_eventTrackActionTimeActDuration = 0.f;
		int m_eventTrackActionTimeActValue = 0;
	} m_timeActEditorFlags;

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
	std::wstring GetObjIdFromTaeFileName(std::wstring name);
};