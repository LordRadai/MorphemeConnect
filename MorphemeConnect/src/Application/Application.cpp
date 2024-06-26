#include "Application.h"
#include "../extern.h"
#include "../framework.h"
#include "../Scene/Scene.h"

#include <Shlwapi.h>
#include <filesystem>

std::vector<std::wstring> getTaeFileListFromChrId(std::wstring tae_path, std::wstring m_chrId)
{
	std::vector<std::wstring> files;

	for (const auto& entry : std::filesystem::directory_iterator(tae_path))
	{
		if (entry.path().extension().compare(".tae") == 0)
		{
			std::wstring filename = entry.path().filename();
			std::wstring file_chr_id_str = filename.substr(1, 4);

			if (file_chr_id_str.compare(m_chrId) == 0)
			{
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "\t%ws\n", filename.c_str());
				files.push_back(entry.path());
			}
		}
	}

	if (files.size() == 0)
		RDebug::SystemAlert(g_logLevel, MsgLevel_Debug, "Application.cpp", "Could not find any TimeAct files belonging to c%d in %ws\n", m_chrId, tae_path);

	return files;
}

std::wstring getModelNameFromChrId(std::wstring model_path, std::wstring m_chrId)
{
	for (const auto& entry : std::filesystem::directory_iterator(model_path))
	{
		if (entry.path().extension().compare(".bnd") == 0)
		{
			std::wstring filename = entry.path().filename();
			std::wstring file_chr_id_str = filename.substr(1, 4);

			if (file_chr_id_str.compare(m_chrId) == 0)
				return entry.path();
		}
	}

	return L"";
}

std::wstring getModelNameFromObjId(std::wstring model_path, std::wstring obj_id)
{
	for (const auto& entry : std::filesystem::directory_iterator(model_path))
	{
		std::wstring filename = entry.path().filename();
		std::wstring file_chr_id_str = filename.substr(0, 8);

		if ((file_chr_id_str.compare(obj_id) == 0) && (entry.path().extension() == ".bnd"))
			return entry.path();
	}

	return L"";
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::GUIStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowBorderSize = 1;
	style->FrameBorderSize = 0;
	style->PopupBorderSize = 1;
	style->FrameBorderSize = 0;
	style->TabBorderSize = 0;

	style->WindowRounding = 0;
	style->ChildRounding = 0;
	style->FrameRounding = 0;
	style->PopupRounding = 0;
	style->ScrollbarRounding = 12;
	style->GrabRounding = 0;
	style->TabRounding = 0;
	style->WindowMenuButtonPosition = ImGuiDir_Left;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.51f, 0.51f, 0.59f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.47f, 0.47f, 0.47f, 0.39f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.39f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void Application::Update()
{
	this->m_model.UpdateModel();
	this->CheckFlags();
	this->RenderGUI("MorphemeConnect");
}

std::string getTaeCategoryTooltip(int category)
{
	INIReader reader(".//MorphemeConnect//res//tooltip//timeact//group.ini");
	
	char default_info[255];
	sprintf_s(default_info, "No specific information is known for this category\n");

	if (reader.ParseError() < 0)
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Failed to load group.ini\n");
		return std::string(default_info);
	}

	std::string category_str = std::to_string(category);

	return reader.GetString(category_str, "tooltip", std::string(default_info));
}

std::string getTaeEventTooltip(int event_id)
{
	INIReader reader(".//MorphemeConnect//res//tooltip//timeact//event.ini");

	char default_info[255];
	sprintf_s(default_info, "No specific information is known for this event\n");

	if (reader.ParseError() < 0)
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to load event.ini\n");
		return std::string(default_info);
	}

	std::string category_str = std::to_string(event_id);

	return reader.GetString(category_str, "tooltip", std::string(default_info));
}

std::string getEventTrackCategoryTooltip(int category)
{
	INIReader reader(".//MorphemeConnect//res//tooltip//eventrack//group.ini");

	char default_info[255];
	sprintf_s(default_info, "No specific information is known for this category\n");

	if (reader.ParseError() < 0)
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to load group.ini\n");
		return std::string(default_info);
	}

	std::string category_str = std::to_string(category);

	return reader.GetString(category_str, "tooltip", std::string(default_info));
}

std::string getEventTrackEventTooltip(int event_id)
{
	INIReader reader(".//MorphemeConnect//res//tooltip//eventrack//event.ini");

	char default_info[255];
	sprintf_s(default_info, "No specific information is known for this event\n");

	if (reader.ParseError() < 0)
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to load event.ini\n");
		return std::string(default_info);
	}

	std::string category_str = std::to_string(event_id);

	return reader.GetString(category_str, "tooltip", std::string(default_info));
}

void Application::RenderGUI(const char* title)
{
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin(title, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::PopStyleVar(1);

	ImGuiID dockSpace = ImGui::GetID("MainWindowDockspace");
	ImGui::DockSpace(dockSpace, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	//Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open...", NULL, &this->m_flags.m_loadFile)) { this->m_flags.m_loadFile = true; }

			ImGui::Separator();

			if (ImGui::BeginMenu("Save"))
			{
				if (ImGui::MenuItem("Save NMB", NULL, &this->m_flags.m_saveNmb)) { this->m_flags.m_saveNmb = true; }
				if (ImGui::MenuItem("Save TAE", NULL, &this->m_flags.m_saveTae)) { this->m_flags.m_saveTae = true; }
				if (ImGui::MenuItem("Save All", NULL, &this->m_flags.m_saveAll)) { this->m_flags.m_saveAll = true; }

				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Export"))
			{
#ifdef _DEBUG
				if (ImGui::MenuItem("Export All", NULL, &this->m_flags.m_exportAll)) { this->m_flags.m_exportAll = true; }
#endif
				if (ImGui::MenuItem("Export Model", NULL, &this->m_flags.m_exportModel)) { this->m_flags.m_exportModel = true; }

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Settings", NULL, &this->m_windowStates.m_settingWindow)) { this->m_windowStates.m_settingWindow != this->m_windowStates.m_settingWindow; }
			
#ifdef _DEBUG
			ImGui::Separator();

			if (ImGui::MenuItem("Find TimeAct", NULL, &this->m_windowStates.m_queryTae)) { this->m_windowStates.m_queryTae != this->m_windowStates.m_queryTae; }
			if (ImGui::MenuItem("Find EventTrack", NULL, &this->m_windowStates.m_queryEventTrack)) { this->m_windowStates.m_queryEventTrack != this->m_windowStates.m_queryEventTrack; }
#endif
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_Appearing);
	this->ModelPreviewWindow();

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);

	this->AssetsWindow();

	static int firstFrame = 0;
	static bool expanded = true;
	static int currentFrame = 0;
	static float zoomLevel = 5.f;

	if (this->m_eventTrackEditorFlags.m_load)
		this->ResetEventTrackEditor();

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);

	this->EventTrackWindow(&currentFrame, &firstFrame, &zoomLevel, &expanded);

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);

	this->EventTrackInfoWindow();

	static int firstFrameTae = 0;
	static bool expandedTae = true;
	static int currentFrameTae = 0;
	static float zoomLevelTae = 10.f;

	if (this->m_eventTrackEditorFlags.m_load)
		this->ResetTimeActEditor();

	zoomLevelTae = 2 * zoomLevel;

	this->SetTimeActCurrentFrameFromEventTrack(&currentFrameTae, currentFrame);

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);

	this->TimeActWindow(&currentFrameTae, &firstFrameTae, &zoomLevelTae, &expandedTae);

	zoomLevel = zoomLevelTae * 0.5f;

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);

	this->TimeActInfoWindow();
}

void Application::ModelPreviewWindow()
{
	ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar);

	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Settings", NULL, &this->m_windowStates.m_previewSettings)) { this->m_windowStates.m_previewSettings != this->m_windowStates.m_previewSettings; }

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Xray", NULL, &this->m_model.m_settings.m_xray)) { this->m_model.m_settings.m_xray != this->m_model.m_settings.m_xray; }

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImVec2 pos = ImGui::GetWindowPos();

		int	width = ImGui::GetWindowSize().x;
		int	height = ImGui::GetWindowSize().y;

		ImGui::InvisibleButton("viewport_preview", ImVec2(width, height));

		if (ImGui::IsItemFocused() && ImGui::IsItemHovered())
		{
			g_preview.m_camera.m_registerInput = true;

			if (ImGui::IsMouseDown(0))
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

			if (ImGui::IsMouseDown(1))
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
		}

		g_preview.SetRenderResolution(width, height);

		ImGui::GetWindowDrawList()->AddImage(g_preview.m_shaderResourceViewViewport, pos, ImVec2(pos.x + width, pos.y + height));
	}

	ImGui::End();
}

void Application::AssetsWindow()
{
	ImGui::Begin("Assets");

	{
		static int selected_tae_file_idx = -1;
		char chr_id_str[50];
		sprintf_s(chr_id_str, "%04d", this->m_chrId);

		std::string tae_popup = "Load TimeAct (c" + std::string(chr_id_str) + ")";

		if (this->m_eventTrackEditorFlags.m_loadTae && this->m_eventTrackEditorFlags.m_taeList.size() > 0)
		{
			ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Appearing);

			ImGui::OpenPopup(tae_popup.c_str());
		}

		ImGui::SetNextWindowPos(ImGui::GetCurrentWindow()->Pos, ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Appearing);
		if (ImGui::BeginPopupModal(tae_popup.c_str()))
		{
			static std::wstring filepath;

			if (ImGui::Button("Load") && selected_tae_file_idx != -1)
			{
				m_tae.m_init = false;
				m_tae = TimeActReader(PWSTR(filepath.c_str()));

				this->m_timeActEditorFlags.m_selectedTimeActIdx = -1;

				this->m_timeActEditorFlags.m_edited.clear();

				if (m_tae.m_init)
				{
					this->m_timeActEditorFlags.m_edited.reserve(m_tae.m_tae.size());

					for (int i = 0; i < m_tae.m_tae.size(); i++)
						this->m_timeActEditorFlags.m_edited.push_back(false);

					RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

					this->m_eventTrackEditorFlags.m_loadTae = false;
				}

				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				this->m_eventTrackEditorFlags.m_loadTae = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::BeginChild("file_list");
			for (int i = 0; i < this->m_eventTrackEditorFlags.m_taeList.size(); i++)
			{
				std::filesystem::path path = this->m_eventTrackEditorFlags.m_taeList[i];
				std::string tae_file = RString::ToNarrow(path.filename().c_str());

				bool selected = (selected_tae_file_idx == i);
				ImGui::Selectable(tae_file.c_str(), selected);

				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
				{
					selected_tae_file_idx = i;
					filepath = path.c_str();

					if (ImGui::IsMouseDoubleClicked(0))
					{
						RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Selected TimeAct %s\n", tae_file.c_str());

						m_tae.m_init = false;
						m_tae = TimeActReader(PWSTR(filepath.c_str()));

						this->m_timeActEditorFlags.m_selectedTimeActIdx = -1;

						this->m_timeActEditorFlags.m_edited.clear();

						if (m_tae.m_init)
						{
							this->m_timeActEditorFlags.m_edited.reserve(m_tae.m_tae.size());

							for (int i = 0; i < m_tae.m_tae.size(); i++)
								this->m_timeActEditorFlags.m_edited.push_back(false);

							RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

							this->m_eventTrackEditorFlags.m_loadTae = false;
						}
						else
							RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Failed to load file %s\n", tae_file.c_str());

						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndChild();

			ImGui::EndPopup();
		}
		else
			selected_tae_file_idx = -1;

		ImGui::BeginTabBar("assets tab bar");
		if (ImGui::BeginTabItem("NSA"))
		{
			if (this->m_nmb.IsInitialised())
				ImGui::Text(RString::ToNarrow(this->m_nmb.GetFileName().c_str()).c_str());

			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (this->m_nmb.IsInitialised())
			{
				ImGui::BeginChild("NSA");
				{
					for (int i = 0; i < m_nmb.GetFilenameLookupTable()->m_data->m_animTable->GetNumEntries(); i++)
					{
						std::string anim_name = "";

						if (this->m_eventTrackEditorFlags.m_edited[i])
							anim_name += "*";

						anim_name += m_nmb.GetAnimationInterface(i)->m_name;

						bool selected = (this->m_eventTrackEditorFlags.m_selectedAnimIdx == m_nmb.GetAnimationInterface(i)->m_id);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							ImGui::Selectable(anim_name.c_str(), &selected);

							if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
							{
								this->m_eventTrackEditorFlags.m_targetAnimIdx = m_nmb.GetAnimationInterface(i)->m_id;
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = m_nmb.GetAnimationInterface(i)->m_id;

								if (ImGui::IsMouseDoubleClicked(0))
									this->m_eventTrackEditorFlags.m_load = true;
							}
							ImGui::PopID();
						}
					}
				}
				ImGui::EndChild();
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Source XMD"))
		{
			if (this->m_nmb.IsInitialised())
				ImGui::Text(RString::ToNarrow(this->m_nmb.GetFileName().c_str()).c_str());

			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (this->m_nmb.IsInitialised())
			{
				ImGui::BeginChild("XMD");
				{
					for (int i = 0; i < m_nmb.GetFilenameLookupTable()->m_data->m_sourceXmdTable->GetNumEntries(); i++)
					{
						std::string anim_name = m_nmb.GetAnimationInterface(i)->m_sourceName;

						bool selected = (this->m_eventTrackEditorFlags.m_selectedAnimIdx == m_nmb.GetAnimationInterface(i)->m_id);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							ImGui::Selectable(anim_name.c_str(), &selected);

							if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
							{
								this->m_eventTrackEditorFlags.m_targetAnimIdx = m_nmb.GetAnimationInterface(i)->m_id;
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = m_nmb.GetAnimationInterface(i)->m_id;

								if (ImGui::IsMouseDoubleClicked(0))
									this->m_eventTrackEditorFlags.m_load = true;
							}

							ImGui::PopID();
						}
					}
				}
				ImGui::EndChild();
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("TimeAct"))
		{
			if (this->m_timeActFlags.m_addTimeAct)
			{
				this->m_timeActFlags.m_addTimeAct = false;

				ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Appearing);

				ImGui::OpenPopup("Add TimeAct");
			}

			if (this->m_timeActFlags.m_deleteTimeAct)
			{
				this->m_timeActFlags.m_deleteTimeAct = false;

				ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Appearing);

				ImGui::OpenPopup("Delete TimeAct");
			}

			ImGui::SetNextWindowPos(ImGui::GetCurrentWindow()->Pos, ImGuiCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Appearing);
			if (ImGui::BeginPopup("Add TimeAct"))
			{
				ImGui::Text("Add TimeAct");
				ImGui::Separator();

				ImGui::InputInt("ID", &this->m_timeActFlags.m_addTimeActId, 0, 0);
				ImGui::InputFloat("Lenght", &this->m_timeActFlags.m_addTimeActLenght, 0, 0);

				if (ImGui::Button("Add"))
				{
					if (this->m_tae.AddTimeAct(this->m_timeActFlags.m_addTimeActId, this->m_timeActFlags.m_addTimeActLenght) == false)
						RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "TimeActReader.cpp", "TimeAct %d already exists\n", this->m_timeActFlags.m_addTimeActId);
					else
					{
						this->m_timeActEditorFlags.m_edited.clear();

						if (m_tae.m_init)
						{
							this->m_timeActEditorFlags.m_edited.reserve(m_tae.m_tae.size());

							for (int i = 0; i < m_tae.m_tae.size(); i++)
								this->m_timeActEditorFlags.m_edited.push_back(false);
						}
					}

					this->m_eventTrackEditorFlags.m_load = true;
					this->m_timeActFlags.m_addTimeAct = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue != -1)
				{
					if (ImGui::Button("Add Selected"))
					{
						this->m_timeActFlags.m_addTimeActId = this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue;
						this->m_timeActFlags.m_addTimeActLenght = RMath::FrameToTime(this->m_eventTrackEditor.m_frameMax);

						if (this->m_tae.AddTimeAct(this->m_timeActFlags.m_addTimeActId, this->m_timeActFlags.m_addTimeActLenght) == false)
							RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "TimeActReader.cpp", "TimeAct %d already exists\n", this->m_timeActFlags.m_addTimeActId);
						else
						{
							this->m_timeActEditorFlags.m_edited.clear();

							if (m_tae.m_init)
							{
								this->m_timeActEditorFlags.m_edited.reserve(m_tae.m_tae.size());

								for (int i = 0; i < m_tae.m_tae.size(); i++)
									this->m_timeActEditorFlags.m_edited.push_back(false);
							}
						}

						this->m_eventTrackEditorFlags.m_load = true;
						this->m_timeActFlags.m_addTimeAct = false;
						ImGui::CloseCurrentPopup();
					}
				}

				ImGui::EndPopup();
			}
			else
				this->m_timeActFlags.m_addTimeAct = false;

			ImGui::SetNextWindowPos(ImGui::GetCurrentWindow()->Pos, ImGuiCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Appearing);
			if (ImGui::BeginPopup("Delete TimeAct"))
			{
				std::string label = "Delete TimeAct (" + std::to_string(this->m_timeActFlags.m_deleteTimeActId) + ")";

				ImGui::Text(label.c_str());
				ImGui::Separator();

				if (ImGui::Button("Delete"))
				{
					if (this->m_tae.DeleteTimeAct(this->m_timeActFlags.m_deleteTimeActId) == false)
						RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "TimeActReader.cpp", "Failed to delete TimeAct %d\n", this->m_timeActFlags.m_deleteTimeActId);

					this->m_eventTrackEditorFlags.m_load = true;
					this->m_timeActFlags.m_deleteTimeAct = false;

					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
			else
				this->m_timeActFlags.m_deleteTimeAct = false;

			if (this->m_tae.m_init)
			{
				ImGui::Text(RString::ToNarrow(this->m_tae.m_fileName.c_str()).c_str());

				if (ImGui::Button("Add"))
					this->m_timeActFlags.m_addTimeAct = true;

				if (this->m_timeActEditorFlags.m_taeId != -1)
				{
					ImGui::SameLine();

					this->m_timeActFlags.m_deleteTimeActId = this->m_timeActEditorFlags.m_taeId;

					if (ImGui::Button("Delete"))
						this->m_timeActFlags.m_deleteTimeAct = true;
				}
			}

			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (this->m_tae.m_init && !this->m_timeActEditorFlags.m_load)
			{
				ImGui::BeginChild("TAE");
				{
					for (int i = 0; i < m_tae.m_header.m_taeCount; i++)
					{
						bool selected = (this->m_timeActEditorFlags.m_selectedTimeActIdx == i);

						std::string anim_name = "";

						if (this->m_timeActEditorFlags.m_edited[i])
							anim_name += "*";

						anim_name += std::to_string(m_tae.m_tae[i].m_id);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);

							ImGui::Selectable(anim_name.c_str(), &selected);

							if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
							{
								this->m_timeActEditorFlags.m_taeId = this->m_tae.m_tae[i].m_id;
								this->m_timeActEditorFlags.m_selectedTimeActIdx = i;

								if (ImGui::IsMouseDoubleClicked(0))
									this->m_timeActEditorFlags.m_load = true;
							}

							ImGui::PopID();
						}
					}
				}
				ImGui::EndChild();
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabItem();
	}

	ImGui::End();
}

void Application::EventTrackWindow(int* current_frame, int* first_frame, float* zoom_level, bool* is_expanded)
{
	ImGui::Begin("EventTrack");
	{
		bool focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

		if (this->m_nmb.IsInitialised())
		{
			if (ImGui::Button("Load"))
			{
				if (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1)
				{
					this->m_eventTrackEditorFlags.m_load = true;
					this->ResetEventTrackEditor();
				}
				else
					RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "No animation is selected\n");
			}

			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				if (this->m_eventTrackEditor.GetTrackCount() > 0)
					this->m_eventTrackEditorFlags.m_save = true;
				else
					RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "No Event Tracks are loaded\n");
			}

			if (this->m_eventTrackEditor.m_animIdx > -1)
				ImGui::Text(RString::RemoveExtension(m_nmb.GetAnimationInterface(this->m_eventTrackEditor.m_animIdx)->m_sourceName).c_str());
			else
				ImGui::Text("");

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_eventTrackEditor, current_frame, &this->m_eventTrackEditorFlags.m_selectedTrack, &this->m_eventTrackEditorFlags.m_selectedEvent, is_expanded, focused, first_frame, zoom_level, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_TRACK_RENAME | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
			ImGui::EndChild();
		}
	}

	ImGui::End();
}

void Application::EventTrackInfoWindow()
{
	ImGui::Begin("Event Data");
	{
		if ((this->m_eventTrackEditor.m_eventTracks.size() > 0) && (this->m_eventTrackEditorFlags.m_selectedTrack != -1 && this->m_eventTrackEditorFlags.m_selectedTrack < this->m_eventTrackEditor.m_eventTracks.size()) && (this->m_eventTrackEditorFlags.m_selectedEvent != -1 && this->m_eventTrackEditor.m_eventTracks[this->m_eventTrackEditorFlags.m_selectedTrack].m_numEvents))
		{
			EventTrackEditor::EventTrack* track = &this->m_eventTrackEditor.m_eventTracks[this->m_eventTrackEditorFlags.m_selectedTrack];
			float startTime = RMath::FrameToTime(track->m_event[this->m_eventTrackEditorFlags.m_selectedEvent].m_frameStart);
			float endTime = RMath::FrameToTime(track->m_event[this->m_eventTrackEditorFlags.m_selectedEvent].m_duration + track->m_event[this->m_eventTrackEditorFlags.m_selectedEvent].m_frameStart);

			ImGui::Text(track->m_name.c_str());
			ImGui::PushItemWidth(100);
			ImGui::InputInt("Event ID", &track->m_eventId, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::SeparatorText("Info");

				ImGui::PushTextWrapPos(ImGui::GetWindowContentWidth());
				ImGui::Text(getEventTrackCategoryTooltip(track->m_eventId).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputInt("Event Value", &track->m_event[this->m_eventTrackEditorFlags.m_selectedEvent].m_value, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::SeparatorText("Info");

				ImGui::PushTextWrapPos(ImGui::GetWindowContentWidth());
				ImGui::Text(getEventTrackEventTooltip(track->m_event[this->m_eventTrackEditorFlags.m_selectedEvent].m_value).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputFloat("Start Time", &startTime, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat("End Time", &endTime, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::PopItemWidth();

			if (this->m_eventTrackEditorFlags.m_save)
			{
				this->m_eventTrackEditorFlags.m_save = false;
				this->m_eventTrackEditor.SetEditedState(false);

				for (int i = 0; i < this->m_eventTrackEditor.GetTrackCount(); i++)
					this->m_eventTrackEditor.m_eventTracks[i].SaveEventTrackData(this->m_eventTrackEditorFlags.m_lenMult);
			}
		}
	}

	ImGui::End();
}

void Application::TimeActWindow(int* current_frame, int* first_frame, float* zoom_level, bool* is_expanded)
{
	ImGui::Begin("TimeAct");

	{
		bool focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

		if (this->m_tae.m_init)
		{
			if (ImGui::Button("Load"))
			{
				if (this->m_tae.m_init)
				{
					this->m_timeActEditorFlags.m_load = true;
					this->ResetTimeActEditor();
				}
				else
					RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "No TimeAct file is currently loaded\n");
			}

			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				if (this->m_tae.m_init)
					this->m_timeActEditorFlags.m_save = true;
				else
					RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "No TimeAct track is currently loaded\n");
			}

			if (this->m_timeActEditorFlags.m_taeId > -1)
				ImGui::Text(std::to_string(this->m_timeActEditorFlags.m_taeId).c_str());
			else
				ImGui::Text("");

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_timeActEditor, current_frame, &this->m_timeActEditorFlags.m_selectedTrack, &this->m_timeActEditorFlags.m_selectedEvent, is_expanded, focused, first_frame, zoom_level, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_TRACK_ADD | ImSequencer::EDITOR_TRACK_RENAME | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
			ImGui::EndChild();
		}
	}

	ImGui::End();
}

void Application::TimeActInfoWindow()
{
	ImGui::Begin("TimeAct Data");
	{
		if ((this->m_timeActEditor.GetTrackCount() > 0) && (this->m_timeActEditorFlags.m_selectedTrack != -1 && this->m_timeActEditorFlags.m_selectedTrack < this->m_timeActEditor.GetTrackCount()) && (this->m_timeActEditorFlags.m_selectedEvent != -1 && this->m_timeActEditor.m_tracks[this->m_timeActEditorFlags.m_selectedTrack].m_count))
		{
			TimeActEditor::TimeActTrack* track = &this->m_timeActEditor.m_tracks[this->m_timeActEditorFlags.m_selectedTrack];
			float startTime = RMath::FrameToTime(track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_frameStart, 30);
			float endTime = RMath::FrameToTime(track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_duration + track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_frameStart, 30);

			ImGui::Text(m_timeActEditor.GetEventLabel(this->m_timeActEditorFlags.m_selectedTrack, this->m_timeActEditorFlags.m_selectedEvent, false).c_str());
			ImGui::PushItemWidth(100);
			ImGui::InputInt("Event Group", &track->m_eventGroup, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::SeparatorText("Info");

				ImGui::PushTextWrapPos(ImGui::GetWindowContentWidth());
				ImGui::Text(getTaeCategoryTooltip(track->m_eventGroup).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputInt("Event ID", &track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_value, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::SeparatorText("Info");

				ImGui::PushTextWrapPos(ImGui::GetWindowContentWidth());
				ImGui::Text(getTaeEventTooltip(track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_value).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputFloat("Start Time", &startTime, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat("End Time", &endTime, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			track->m_event[this->m_timeActEditorFlags.m_selectedEvent].m_args->ImGuiEdit();

			if (this->m_timeActEditorFlags.m_save)
			{
				this->m_timeActEditorFlags.m_save = false;
				this->m_timeActEditor.SetEditedState(false);

				for (int i = 0; i < this->m_timeActEditor.GetTrackCount(); i++)
					this->m_timeActEditor.m_tracks[i].SaveTimeActTrack();
			}

			ImGui::PopItemWidth();
		}
	}

	ImGui::End();
}

void Application::SettingsWindow()
{
	ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Appearing);
	ImGui::Begin("Settings##gui", &this->m_windowStates.m_settingWindow);

	ImGui::BeginTabBar("settings");

#ifdef _DEBUG
	if (ImGui::BeginTabItem("Style"))
	{
		ImGui::ShowStyleEditor();

		ImGui::EndTabItem();
	}
#endif

	if (ImGui::BeginTabItem("Export Settings"))
	{
		ImGui::Checkbox("Export morpheme rig with flver model", &this->m_fbxExportFlags.m_exportMorphemeRigWithModel);

#ifdef _DEBUG
		ImGui::Checkbox("Export model with animations", &this->m_fbxExportFlags.m_exportModelWithAnims);
#endif
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("EventTrack Editor Colors"))
	{
		ImGui::ColorEdit4("Track", (float*)&this->m_eventTrackEditor.m_colors.m_trackColor);
		ImGui::ColorEdit4("Track Inactive", (float*)&this->m_eventTrackEditor.m_colors.m_trackColorInactive);
		ImGui::ColorEdit4("Track Active", (float*)&this->m_eventTrackEditor.m_colors.m_trackColorActive);
		ImGui::ColorEdit4("Track Bounding Box", (float*)&this->m_eventTrackEditor.m_colors.m_trackBoundingBox);
		ImGui::ColorEdit4("Track Bounding Box Active", (float*)&this->m_eventTrackEditor.m_colors.m_trackBoundingBoxActive);
		ImGui::ColorEdit4("Track Text Color", (float*)&this->m_eventTrackEditor.m_colors.m_trackTextColor);
		ImGui::ColorEdit4("Cursor Color", (float*)&this->m_eventTrackEditor.m_colors.m_cursorColor);

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("TimeAct Editor Colors"))
	{
		ImGui::ColorEdit4("Track", (float*)&this->m_timeActEditor.m_colors.m_trackColor);
		ImGui::ColorEdit4("Track Inactive", (float*)&this->m_timeActEditor.m_colors.m_trackColorInactive);
		ImGui::ColorEdit4("Track Active", (float*)&this->m_timeActEditor.m_colors.m_trackColorActive);
		ImGui::ColorEdit4("Track Bounding Box", (float*)&this->m_timeActEditor.m_colors.m_trackBoundingBox);
		ImGui::ColorEdit4("Track Bounding Box Active", (float*)&this->m_timeActEditor.m_colors.m_trackBoundingBoxActive);
		ImGui::ColorEdit4("Track Text Color", (float*)&this->m_timeActEditor.m_colors.m_trackTextColor);
		ImGui::ColorEdit4("Cursor Color", (float*)&this->m_timeActEditor.m_colors.m_cursorColor);

		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void Application::PreviewDebugManagerWindow()
{
	ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Appearing);
	ImGui::Begin("Settings##preview", &this->m_windowStates.m_previewSettings);

	ImGui::DragFloat("Grid Scale", &g_preview.m_settings.m_gridScale, 0.1f, 0.f, FLT_MAX);

	ImGui::BeginTabBar("preview_settings");
	if (ImGui::BeginTabItem("Camera"))
	{
		ImGui::SeparatorText("Parameters");

		ImGui::DragFloat("Target Distance", &g_preview.m_camera.m_radius, 0.1f, 0.1f, 10.f);
		ImGui::InputFloat3("Target Offset", &g_preview.m_camera.m_offsets.x);
		ImGui::InputFloat3("Camera Position", &g_preview.m_camera.m_position.x);
		ImGui::InputFloat3("Camera Angles", &g_preview.m_camera.m_angles.x);
		ImGui::DragFloat("FOV", &g_preview.m_camera.m_fov, 0.1f, 0.1f, DirectX::XM_PI);
		ImGui::InputFloat("Near Plane", &g_preview.m_camera.m_nearZ);
		ImGui::InputFloat("Far Plane", &g_preview.m_camera.m_farZ);

		ImGui::InputFloat("Width", &g_preview.m_camera.m_width, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Height", &g_preview.m_camera.m_height, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Aspect Ratio", &g_preview.m_camera.m_aspectRatio, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::SeparatorText("Input");

		ImGui::Checkbox("Invert X Drag", &g_preview.m_camera.m_settings.m_dragInvertX);
		ImGui::Checkbox("Invert Y Drag", &g_preview.m_camera.m_settings.m_dragInvertY);

		ImGui::Checkbox("Invert X Rotation", &g_preview.m_camera.m_settings.m_rotInvertX);
		ImGui::Checkbox("Invert Y Rotation", &g_preview.m_camera.m_settings.m_rotInvertY);

		ImGui::SeparatorText("Speed Settings");

		ImGui::DragFloat("Drag Speed", &g_preview.m_camera.m_settings.m_speedParams.m_dragSpeed, 0.1f, 0.f, 10.f);
		ImGui::DragFloat("Zoom Speed", &g_preview.m_camera.m_settings.m_speedParams.m_zoomSpeed, 0.1f, 0.f, 100.f);
	
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Background"))
	{
		ImGui::ColorEdit4("Background Color", &g_preview.m_settings.m_backgroundColor.x);

		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	
	ImGui::End();
}

void Application::CheckFlags()
{
	if (this->m_windowStates.m_settingWindow)
	{
		this->SettingsWindow();
	}

	if (this->m_windowStates.m_previewSettings)
	{
		this->PreviewDebugManagerWindow();
	}

	if (this->m_windowStates.m_queryEventTrack)
	{

	}

	if (this->m_windowStates.m_queryTae)
	{

	}

	if (this->m_flags.m_loadFile)
	{
		this->m_flags.m_loadFile = false;

		m_eventTrackEditorFlags.m_load = false;
		m_timeActEditorFlags.m_load = false;

		this->m_eventTrackEditor.Clear();
		this->m_timeActEditor.Clear();

		this->LoadFile();
	}

	if (this->m_flags.m_saveNmb)
	{
		this->m_flags.m_saveNmb = false;

		if (this->m_nmb.IsInitialised())
			this->SaveNmbFile();
		else
			RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Application.cpp", "No NMB file is loaded\n");
	}

	if (this->m_flags.m_saveTae)
	{
		this->m_flags.m_saveTae = false;

		if (this->m_tae.m_init)
			this->SaveTaeFile();
		else
			RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Application.cpp", "No TAE file is loaded\n");
	}

	if (this->m_flags.m_saveAll)
	{
		this->m_flags.m_saveAll = false;

		if (this->m_nmb.IsInitialised())
		{
			bool status = m_nmb.SaveToFile(this->m_nmb.GetFilePath());

			if (status)
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.GetOutFilePath(), m_nmb.GetBundleCount(), m_nmb.GetOutFileSize());
			else
				RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Failed to generate file\n", "NMBReader.cpp");
		}

		if (this->m_tae.m_init)
		{
			bool status = m_tae.SaveFile(this->m_tae.m_filePath);

			if (status)
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
			else
				RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Failed to generate file\n", "TimeActReader.cpp");
		}
	}

	if (this->m_flags.m_exportAll)
	{
		this->m_flags.m_exportAll = false;

		if (this->m_animFiles.size() == 0)
			RDebug::SystemAlert(g_logLevel, MsgLevel_Warn, "Application.cpp", "No animations are loaded");

		std::wstring out_path = L".//Export";

		wchar_t chr_id_str[50];
		swprintf_s(chr_id_str, L"c%04d", this->m_chrId);

		out_path += L"//" + std::wstring(chr_id_str) + L"//";

		std::filesystem::create_directories(out_path);

		PWSTR export_path = (wchar_t*)out_path.c_str();

		if (!this->ExportModelToFbx(export_path))
			RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Application.cpp", "Failed to export FBX model (chrId=c%04d)\n", this->m_chrId);

		for (int i = 0; i < this->m_animFiles.size(); i++)
		{
			std::filesystem::path anim_out = std::filesystem::path(RString::ToNarrow(export_path) + "//Animations//" + this->m_nmb.GetSourceAnimName(i)).replace_extension(".fbx");
			std::filesystem::create_directories(anim_out.parent_path());

			if (!this->ExportAnimationToFbx(anim_out, i))
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to export animation %d\n", i);

			if (!this->m_nmb.ExportEventTrackToXML(export_path, i))
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to export event track to XML for animation %d\n", i);
		}
	}

	if (this->m_flags.m_exportModel)
	{
		this->m_flags.m_exportModel = false;

		std::wstring out_path = L".//Export";

		wchar_t chr_id_str[50];
		swprintf_s(chr_id_str, L"c%04d", this->m_chrId);

		out_path += L"//" + std::wstring(chr_id_str) + L"//";

		std::filesystem::create_directories(out_path);

		PWSTR export_path = (wchar_t*)out_path.c_str();

		this->ExportModelToFbx(export_path);
	}

	if (this->m_nmb.IsInitialised() == false)
	{
		this->m_eventTrackEditor.Clear();

		m_eventTrackEditorFlags.m_load = false;
		m_eventTrackEditorFlags.m_selectedAnimIdx = -1;
	}

	if (this->m_eventTrackEditor.m_reload)
		this->m_eventTrackEditor.ReloadTracks();

	if (this->m_eventTrackEditorFlags.m_load)
	{
		this->m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();

		if ((this->m_nmb.IsInitialised() == true) && (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1))
		{
			bool found_et = false;
			bool found_anim = false;

			this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue = -1;
			this->m_eventTrackEditorFlags.m_eventTrackActionTimeActStart = 0.f;
			this->m_eventTrackEditorFlags.m_eventTrackActionTimeActDuration = 0.f;

			RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Performing lookup for animation ID %d\n", this->m_eventTrackEditorFlags.m_targetAnimIdx);

			for (int idx = 0; idx < this->m_nmb.GetNetworkDef()->m_data->m_numNodes; idx++)
			{
				MorphemeBundle_NetworkDef* networkDef = this->m_nmb.GetNetworkDef();

				NodeDef* node = networkDef->m_data->m_nodes[idx];

				if (node->m_typeID == NodeType_NodeAnimSyncEvents)
				{
					if (networkDef->m_data->m_nodes[idx]->m_attributes[1] != NULL)
					{
						MR::AttribDataSourceAnim* source_anim = (MR::AttribDataSourceAnim*)networkDef->m_data->m_nodes[idx]->m_attributes[1]->GetAttribData();
						MR::AttribDataSourceEventTrack* event_track = (MR::AttribDataSourceEventTrack*)networkDef->m_data->m_nodes[idx]->m_attributes[2]->GetAttribData();

						if (source_anim->GetAnimID() == this->m_eventTrackEditorFlags.m_targetAnimIdx)
						{
							found_anim = true;

							RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Animation found after %d steps\n", idx);

							this->m_eventTrackEditor.m_nodeSource = node;
							this->m_eventTrackEditor.m_frameMin = RMath::TimeToFrame(source_anim->GetClipStart() * source_anim->GetAnimLen());
							this->m_eventTrackEditor.m_frameMax = RMath::TimeToFrame(source_anim->GetClipEnd() * source_anim->GetAnimLen());

							this->m_eventTrackEditor.m_animIdx = -1;

							for (int i = 0; i < this->m_nmb.GetAnimationCount(); i++)
							{
								if (this->m_nmb.GetAnimationInterface(i)->m_id == source_anim->GetAnimID())
									this->m_eventTrackEditor.m_animIdx = i;
							}

							this->m_eventTrackEditorFlags.m_lenMult = source_anim->GetAnimLen() / (source_anim->GetClipEnd() - source_anim->GetClipStart());

							int track_count = event_track->GetDiscreteEventTrackSet().m_trackCount + event_track->GetCurveEventTrackSet().m_trackCount + event_track->GetDurationEventTrackSet().m_trackCount;

							this->m_eventTrackEditor.m_eventTracks.reserve(track_count);

							if (track_count > 0)
							{
								found_et = true;

								for (int i = 0; i < event_track->GetDiscreteEventTrackSet().m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->GetDiscreteEventTrackSet().m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, true));
								}

								for (int i = 0; i < event_track->GetCurveEventTrackSet().m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->GetCurveEventTrackSet().m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								for (int i = 0; i < event_track->GetDurationEventTrackSet().m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->GetDurationEventTrackSet().m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								this->m_eventTrackEditor.SetEditedState(false);

								if (this->m_tae.m_init)
								{
									for (size_t i = 0; i < this->m_eventTrackEditor.m_eventTracks.size(); i++)
									{
										if (this->m_eventTrackEditor.m_eventTracks[i].m_eventId == 1000)
										{
											this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue = this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_value;
											this->m_eventTrackEditorFlags.m_eventTrackActionTimeActStart = RMath::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_frameStart);
											this->m_eventTrackEditorFlags.m_eventTrackActionTimeActDuration = RMath::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_duration);

											this->m_timeActEditorFlags.m_taeId = this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue;

											for (size_t j = 0; j < this->m_tae.m_tae.size(); j++)
											{
												if (this->m_tae.m_tae[j].m_id == this->m_timeActEditorFlags.m_taeId)
													this->m_timeActEditorFlags.m_selectedTimeActIdx = j;
											}

											this->m_timeActEditorFlags.m_load = true;

											break;
										}
									}
								}

								break;
							}
							else
							{
								RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Animation %d has no event tracks associated to it\n", source_anim->GetAnimID());
							}
						}
					}
				}
			}

			if (!found_anim)
				RDebug::DebuggerOut(g_logLevel, MsgLevel_Warn, "Animation ID %d not found\n", this->m_eventTrackEditorFlags.m_targetAnimIdx);

			RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "\n");
		}
	}

	if (this->m_tae.m_init == false)
	{
		this->m_timeActEditor.Clear();

		m_timeActEditorFlags.m_load = false;
		m_timeActEditorFlags.m_selectedTimeActIdx = -1;
	}

	if (this->m_timeActEditor.m_reload)
		this->m_timeActEditor.ReloadTracks();

	if (this->m_timeActEditorFlags.m_load)
	{
		this->m_timeActEditorFlags.m_load = false;
		this->m_timeActEditor.Clear();

		this->m_timeActEditor.m_taeIdx = this->m_timeActEditorFlags.m_selectedTimeActIdx;

		if (this->m_tae.m_init && this->m_timeActEditorFlags.m_taeId > -1)
		{
			if (m_tae.m_tae.size() > 0)
			{
				TimeAct* timeact = this->m_tae.TimeActLookup(this->m_timeActEditorFlags.m_taeId);
				this->m_timeActEditor.m_source = timeact;

				if (timeact)
				{
					float trackLen = (float)timeact->m_taeData->m_animData->m_lenght / (float)timeact->m_taeData->m_animData->m_fps;

					this->m_timeActEditor.m_frameMax = RMath::TimeToFrame(trackLen, 30);
					this->m_timeActEditor.m_frameMin = 0;

					this->m_timeActEditor.SetEditedState(false);

					if (timeact->m_taeData->m_eventGroupCount > 0)
					{
						for (int j = 0; j < timeact->m_taeData->m_eventGroupCount; j++)
							this->m_timeActEditor.m_tracks.push_back(&timeact->m_taeData->m_groups[j]);
					}
				}
				else
					RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "TimeAct %d not found\n", this->m_timeActEditorFlags.m_taeId);
			}
			else
				RDebug::SystemAlert(g_logLevel, MsgLevel_Info, "Application.cpp", "No TimeAct is loaded\n");			
		}
	}
}

int Application::GetChrIdFromNmbFileName(std::wstring name)
{
	std::wstring chr_id_str;
	int m_chrId = -1;

	int lastCPos = name.find_last_of(L"\\");

	if (name.substr(lastCPos + 1, 1).compare(L"c") != 0)
		return -1;

	chr_id_str = name.substr(lastCPos + 2, 4);

	m_chrId = stoi(chr_id_str);

	RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Chr ID: %d\n", m_chrId);

	return m_chrId;
}

std::wstring Application::GetObjIdFromTaeFileName(std::wstring name)
{
	std::wstring obj_id;

	int lastCPos = name.find_last_of(L"\\");

	obj_id = name.substr(lastCPos + 1, 8);

	if (obj_id.substr(0, 1).compare(L"o") != 0)
		return L"";

	RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Obj ID: %s\n", obj_id);

	return obj_id;
}

void Application::LoadFile()
{
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"Morpheme Network Binary", L"*.nmb"}, {L"TimeAct", L"*.tae"}, {L"All Files",L"*.*"} };

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen = NULL;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			pFileOpen->SetFileTypes(3, ComDlgFS);

			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::filesystem::path filepath = std::wstring(pszFilePath);

						if (filepath.extension() == ".nmb")
						{
							m_nmb = NMBReader(pszFilePath);
							
							if (m_nmb.IsInitialised())
							{
								RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Open file %ls (bundles=%d, len=%d)\n", m_nmb.GetFilePath(), m_nmb.GetBundleCount(), m_nmb.GetFileSize());

								this->m_animFiles.clear();
								this->m_animFiles.reserve(this->m_nmb.GetFilenameLookupTable()->m_data->m_animTable->GetNumEntries());

								for (int i = 0; i < this->m_nmb.GetFilenameLookupTable()->m_data->m_animTable->GetNumEntries(); i++)
								{
									std::filesystem::path gamepath = pszFilePath;
									std::wstring parent_path = gamepath.parent_path();

									std::wstring anim_name = RString::ToWide(this->m_nmb.GetFilenameLookupTable()->GetAnimName(i));

									std::wstring anim_path_str = parent_path + L"\\" + anim_name;

									PWSTR anim_path = (wchar_t*)anim_path_str.c_str();

									this->m_animFiles.push_back(NSAReader(anim_path));
								}

								this->m_eventTrackEditorFlags.m_targetAnimIdx = -1;
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = -1;

								this->m_eventTrackEditorFlags.m_edited.clear();
								this->m_eventTrackEditorFlags.m_edited.reserve(m_nmb.GetFilenameLookupTable()->m_data->m_animTable->GetNumEntries());

								for (int i = 0; i < m_nmb.GetFilenameLookupTable()->m_data->m_animTable->GetNumEntries(); i++)
									this->m_eventTrackEditorFlags.m_edited.push_back(false);

								this->m_chrId = GetChrIdFromNmbFileName(m_nmb.GetFilePath());

								if (this->m_chrId != -1)
								{
									bool found = false;

									std::filesystem::path gamepath = pszFilePath;
									std::filesystem::path filepath_tae;
									std::filesystem::path filepath_dcx;
									do
									{
										std::wstring parent_path = gamepath.parent_path();
										gamepath = parent_path;

										int lastDirPos = parent_path.find_last_of(L"\\");

										std::wstring folder = parent_path.substr(lastDirPos, parent_path.length());

										if (folder.compare(L"\\") == 0)
											break;

										if (folder.compare(L"\\Game") == 0)
										{
											found = true;
											break;
										}
									} while (true);

									if (found)
									{
										filepath_tae = gamepath;
										filepath_dcx = gamepath;

										filepath_tae += "\\timeact\\chr";
										filepath_dcx += "\\model\\chr";

										wchar_t chr_id_str[50];
										swprintf_s(chr_id_str, L"%04d", this->m_chrId);

										std::wstring string = std::wstring(chr_id_str);

										this->m_eventTrackEditorFlags.m_taeList = getTaeFileListFromChrId(filepath_tae, chr_id_str);
										this->m_eventTrackEditorFlags.m_loadTae = true;

										m_bnd.m_init = false;
										std::wstring path_tmp = getModelNameFromChrId(filepath_dcx, chr_id_str);

										if (path_tmp.compare(L"") != 0)
										{
											PWSTR dcx_path = (wchar_t*)path_tmp.c_str();

											m_bnd = BNDReader(dcx_path);

											std::string filename = "c" + RString::ToNarrow(string.c_str()) + ".flv";

											bool found_model = false;

											for (size_t i = 0; i < m_bnd.m_fileCount; i++)
											{
												if (m_bnd.m_files[i].m_name == filename)
												{
													UMEM* umem = uopenMem(m_bnd.m_files[i].m_data, m_bnd.m_files[i].m_uncompressedSize);
													FLVER2 flver_model = FLVER2(umem);

													this->m_model = FlverModel(umem);

													RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Loaded model %s\n", filename.c_str());

													this->CreateMorphemeRigBoneToFlverBoneMap(this->m_nmb.GetRig(0)->m_data, &this->m_model);

													found_model = true;
													break;
												}
											}

											if (!found_model)
												RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Could not find model for c%04d\n", this->m_chrId);
										}
									}
									else
										RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Could not find Game folder\n");
								}
							}
						}
						else if (filepath.extension() == ".tae")
						{
							m_tae.m_init = false;
							m_tae = TimeActReader(pszFilePath);

							if (m_tae.m_init)
							{
								this->m_timeActEditorFlags.m_selectedTimeActIdx = -1;

								this->m_timeActEditorFlags.m_edited.clear();
								this->m_timeActEditorFlags.m_edited.reserve(m_tae.m_tae.size());

								for (int i = 0; i < m_tae.m_tae.size(); i++)
									this->m_timeActEditorFlags.m_edited.push_back(false);

								RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

								bool found = false;

								std::wstring obj_id = GetObjIdFromTaeFileName(pszFilePath);

								if (obj_id.compare(L"") != 0)
								{
									std::filesystem::path gamepath = pszFilePath;
									std::filesystem::path filepath_dcx;
									do
									{
										std::wstring parent_path = gamepath.parent_path();
										gamepath = parent_path;

										int lastDirPos = parent_path.find_last_of(L"\\");

										std::wstring folder = parent_path.substr(lastDirPos, parent_path.length());

										if (folder.compare(L"\\") == 0)
											break;

										if (folder.compare(L"\\Game") == 0)
										{
											found = true;
											break;
										}
									} while (true);

									if (found)
									{
										filepath_dcx = gamepath;

										filepath_dcx += "\\model\\obj";

										m_bnd.m_init = false;
										std::wstring obj_path = getModelNameFromObjId(filepath_dcx, obj_id);

										if (obj_path.compare(L"") != 0)
										{
											PWSTR dcx_path = (wchar_t*)obj_path.c_str();

											m_bnd = BNDReader(dcx_path);

											std::string filename = RString::ToNarrow(obj_id.c_str()) + ".flv";

											bool found_model = false;

											for (size_t i = 0; i < m_bnd.m_fileCount; i++)
											{
												if (m_bnd.m_files[i].m_name == filename)
												{
													UMEM* umem = uopenMem(m_bnd.m_files[i].m_data, m_bnd.m_files[i].m_uncompressedSize);
													FLVER2 flver_model = FLVER2(umem);

													this->m_model = FlverModel(umem);

													RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Loaded model %s\n", filename.c_str());

													found_model = true;

													this->CreateMorphemeRigBoneToFlverBoneMap(this->m_nmb.GetRig(0)->m_data, &this->m_model);

													break;
												}
											}

											if (!found_model)
												RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Could not find model for c%04d\n", this->m_chrId);
										}
									}
									else
										RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Could not find Game folder\n");
								}
							}						
						}
					}
					pItem->Release();
				}
				else
					MessageBoxW(NULL, L"Failed to open file", L"Application.cpp", MB_ICONERROR);
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
}

void Application::SaveFile()
{
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"Morpheme Network Binary", L"*.nmb"}, {L"TimeAct", L"*.tae"}, {L"All Files",L"*.*"} };

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileSave = NULL;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		if (SUCCEEDED(hr))
		{
			pFileSave->SetFileTypes(3, ComDlgFS);

			// Show the Open dialog box.
			hr = pFileSave->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszOutFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszOutFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::filesystem::path filepath = std::wstring(pszOutFilePath);

						if (filepath.extension() == ".nmb")
						{
							bool status = m_nmb.SaveToFile(pszOutFilePath);

							if (status)
								RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.GetOutFilePath(), m_nmb.GetBundleCount(), m_nmb.GetOutFileSize());
							else
								RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "NMBReader.cpp", "Failed to generate NMB file\n");
						}
						else if (filepath.extension() == ".tae")
						{
							bool status = m_tae.SaveFile(pszOutFilePath);

							if (status)
								RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
							else
								RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "TimeActReader.cpp", "Failed to generate TAE file\n");
						}
					}
					pItem->Release();
				}
				else
					MessageBoxW(NULL, L"Failed to save file", L"Application.cpp", MB_ICONERROR);
			}
			pFileSave->Release();
		}
		CoUninitialize();
	}
}

void Application::SaveNmbFile()
{
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"Morpheme Network Binary", L"*.nmb"}, {L"All Files",L"*.*"} };

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileSave = NULL;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		if (SUCCEEDED(hr))
		{
			pFileSave->SetFileTypes(2, ComDlgFS);

			// Show the Open dialog box.
			hr = pFileSave->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszOutFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszOutFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::filesystem::path filepath = std::wstring(pszOutFilePath);

						bool status = m_nmb.SaveToFile(pszOutFilePath);

						if (status)
							RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.GetOutFilePath(), m_nmb.GetBundleCount(), m_nmb.GetOutFileSize());
						else
							RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "NMBReader.cpp", "Failed to generate NMB file\n");
					}
					pItem->Release();
				}
				else
					MessageBoxW(NULL, L"Failed to save file", L"Application.cpp", MB_ICONERROR);
			}
			pFileSave->Release();
		}
		CoUninitialize();
	}
}

void Application::SaveTaeFile()
{
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"TimeAct", L"*.tae"}, {L"All Files",L"*.*"} };

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileSave = NULL;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		if (SUCCEEDED(hr))
		{
			pFileSave->SetFileTypes(2, ComDlgFS);

			// Show the Open dialog box.
			hr = pFileSave->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszOutFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszOutFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::filesystem::path filepath = std::wstring(pszOutFilePath);

						bool status = m_tae.SaveFile(pszOutFilePath);

						if (status)
							RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
						else
							RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "TimeActReader.cpp", "Failed to generate TAE file\n");
					}
					pItem->Release();
				}
				else
					MessageBoxW(NULL, L"Failed to save file", L"Application.cpp", MB_ICONERROR);
			}
			pFileSave->Release();
		}
		CoUninitialize();
	}
}

void Application::ResetEventTrackEditor()
{
	this->m_eventTrackEditorFlags.m_selectedEvent = -1;
	this->m_eventTrackEditorFlags.m_selectedTrack = -1;
}

void Application::ResetTimeActEditor()
{
	this->m_timeActEditorFlags.m_selectedEvent = -1;
	this->m_timeActEditorFlags.m_selectedTrack = -1;
}

void Application::SetTimeActCurrentFrameFromEventTrack(int* current_frame_tae, int current_frame)
{
	if (this->m_timeActEditor.m_source == nullptr)
		return;

	if (this->m_eventTrackEditor.GetTrackCount() > 0)
	{
		for (int i = 0; i < this->m_eventTrackEditor.GetTrackCount(); i++)
		{
			if (this->m_eventTrackEditor.m_eventTracks[i].m_eventId == 1000)
			{
				this->m_eventTrackEditorFlags.m_eventTrackActionTimeActStart = RMath::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_frameStart);
				this->m_eventTrackEditorFlags.m_eventTrackActionTimeActDuration = RMath::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_duration);
				this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue = this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_value;
			}
		}

		if (this->m_eventTrackEditorFlags.m_eventTrackActionTimeActValue == this->m_timeActEditorFlags.m_taeId)
			*current_frame_tae = RMath::TimeToFrame(m_timeActEditor.m_source->CalculatePlaybackPosFromMorphemeEventTrack(this->m_eventTrackEditorFlags.m_eventTrackActionTimeActStart, this->m_eventTrackEditorFlags.m_eventTrackActionTimeActDuration, RMath::FrameToTime(current_frame)), 30, false);
	}
}

inline int GetMorphemeRigBoneIndexByFlverBoneIndex(MR::Rig* pRig, FlverModel* pFlverModel, int idx)
{
	std::string boneName = RString::ToNarrow(pFlverModel->m_flver->bones[idx].name);
	int boneIdx = pRig->GetBoneIndex(boneName);

	if (boneIdx == -1)
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Bone %s does not exist in the morpheme rig\n", boneName.c_str());

	return boneIdx;
}

//Creates an anim map from the flver model bone to the morpheme rig and saves it in m_flverToMorphemeBoneMap
void Application::CreateMorphemeRigBoneToFlverBoneMap(MR::Rig* pMorphemeRig, FlverModel* pFlverModel)
{
	this->m_flverToMorphemeBoneMap.clear();
	this->m_flverToMorphemeBoneMap.reserve(pFlverModel->m_flver->header.boneCount);

	for (int i = 0; i < pFlverModel->m_flver->header.boneCount; i++)
		this->m_flverToMorphemeBoneMap.push_back(GetMorphemeRigBoneIndexByFlverBoneIndex(pMorphemeRig, pFlverModel, i));
}

//Adds flver meshes to the scene
bool CreateFbxModel(Application* pApplication, FbxScene* pScene, FbxPose* pBindPoses, std::vector<FbxNode*> pBoneList, std::filesystem::path export_path, MorphemeBundle_Rig* pMorphemeRig, bool useMorphemeRig)
{
	std::string model_node_name = "c" + std::to_string(pApplication->m_chrId) + "_model";

	FbxNode* pModelNode = FbxNode::Create(pScene, model_node_name.c_str());
	pScene->GetRootNode()->AddChild(pModelNode);

	std::vector<FbxNode*> pMeshNodesList;

	pMeshNodesList.reserve(pApplication->m_model.m_flver->header.meshCount);

	for (int i = 0; i < pApplication->m_model.m_flver->header.meshCount; i++)
	{
		FbxNode* pMeshNode = nullptr;

		if (!useMorphemeRig || pMorphemeRig == nullptr)
			pMeshNode = pApplication->m_model.CreateModelFbxMesh(pScene, pBoneList, i);
		else
			pMeshNode = pApplication->m_model.CreateModelFbxMesh(pScene, pBoneList, pMorphemeRig, pApplication->m_flverToMorphemeBoneMap, i);

		if (pMeshNode != nullptr)
		{
			pModelNode->AddChild(pMeshNode);
			pBindPoses->Add(pMeshNode, FbxAMatrix());

			pMeshNodesList.push_back(pMeshNode);
		}
		else
			RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to create MeshNode object for mesh %d (file=%s)\n", i, export_path.filename().c_str());
	}
	
	return true;
}

inline double GetTimeByAnimFrame(float animLenght, float fps, int frameNum)
{
	return (animLenght / fps) * frameNum;
}

//Creates FBX animation take from an NSA file input
bool CreateFbxTake(FbxScene* pScene, std::vector<FbxNode*> pSkeleton, NSAReader* pAnimFile, std::string name)
{
	if (!pAnimFile->m_init)
		return false;

	const char* cStrName = name.c_str();

	FbxAnimStack* pAnimStack = FbxAnimStack::Create(pScene, cStrName);
	FbxAnimLayer* pAnimBaseLayer = FbxAnimLayer::Create(pScene, cStrName);

	pAnimStack->AddMember(pAnimBaseLayer);

	FbxTime start;
	start.SetSecondDouble(0.0);

	float animSampleRate = pAnimFile->m_header.m_fps;
	float animDuration = pAnimFile->m_header.m_duration;

	FbxTime end;
	end.SetSecondDouble(animDuration);

	FbxTimeSpan timeSpan = FbxTimeSpan(start, end);
	pAnimStack->SetLocalTimeSpan(timeSpan);

	int keyframeCount = pAnimFile->m_header.m_fps * animDuration;
	int boneCount = std::min<int>(pSkeleton.size(), pAnimFile->m_header.m_boneCount);

	for (int boneIdx = 0; boneIdx < boneCount; boneIdx++)
	{
		FbxNode* pBone = pSkeleton[boneIdx];

		FbxAnimCurve* curveTX = pBone->LclTranslation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_X, true);
		FbxAnimCurve* curveTY = pBone->LclTranslation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Y, true);
		FbxAnimCurve* curveTZ = pBone->LclTranslation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Z, true);

		FbxAnimCurve* curveRX = pBone->LclRotation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_X, true);
		FbxAnimCurve* curveRY = pBone->LclRotation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Y, true);
		FbxAnimCurve* curveRZ = pBone->LclRotation.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Z, true);

		FbxAnimCurve* curveSX = pBone->LclScaling.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_X, true);
		FbxAnimCurve* curveSY = pBone->LclScaling.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Y, true);
		FbxAnimCurve* curveSZ = pBone->LclScaling.GetCurve(pAnimBaseLayer, FBXSDK_CURVENODE_COMPONENT_Z, true);

		curveTX->KeyModifyBegin();
		curveTY->KeyModifyBegin();
		curveTZ->KeyModifyBegin();

		curveRX->KeyModifyBegin();
		curveRY->KeyModifyBegin();
		curveRZ->KeyModifyBegin();

		curveSX->KeyModifyBegin();
		curveSY->KeyModifyBegin();
		curveSZ->KeyModifyBegin();

		for (int frame = 0; frame < keyframeCount; frame++)
		{
			int keyIndex;

			FbxTime keyTime;
			keyTime.SetSecondDouble(GetTimeByAnimFrame(animDuration, animSampleRate, frame));

			DirectX::SimpleMath::Vector3 translation = pAnimFile->m_boneKeyframes[boneIdx].m_frames[frame].m_translation;

			keyIndex = curveTX->KeyAdd(keyTime);
			curveTX->KeySetValue(keyIndex, translation.x);
			curveTX->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveTY->KeyAdd(keyTime);
			curveTY->KeySetValue(keyIndex, translation.y);
			curveTY->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveTZ->KeyAdd(keyTime);
			curveTZ->KeySetValue(keyIndex, translation.z);
			curveTZ->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			DirectX::SimpleMath::Vector3 rotationEuler = RMath::ConvertQuatToEulerAngles(pAnimFile->m_boneKeyframes[boneIdx].m_frames[frame].m_rotation);

			keyIndex = curveRX->KeyAdd(keyTime);
			curveRX->KeySetValue(keyIndex, rotationEuler.x);
			curveRX->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveRY->KeyAdd(keyTime);
			curveRY->KeySetValue(keyIndex, rotationEuler.y);
			curveRY->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveRZ->KeyAdd(keyTime);
			curveRZ->KeySetValue(keyIndex, rotationEuler.z);
			curveRZ->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			DirectX::SimpleMath::Vector3 scale = pAnimFile->m_boneKeyframes[boneIdx].m_frames[frame].m_scale;

			keyIndex = curveSX->KeyAdd(keyTime);
			curveSX->KeySetValue(keyIndex, scale.x);
			curveSX->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveSY->KeyAdd(keyTime);
			curveSY->KeySetValue(keyIndex, scale.y);
			curveSY->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);

			keyIndex = curveSZ->KeyAdd(keyTime);
			curveSZ->KeySetValue(keyIndex, scale.z);
			curveSZ->KeySetInterpolation(keyIndex, FbxAnimCurveDef::eInterpolationLinear);
		}

		curveTX->KeyModifyEnd();
		curveTY->KeyModifyEnd();
		curveTZ->KeyModifyEnd();

		curveRX->KeyModifyEnd();
		curveRY->KeyModifyEnd();
		curveRZ->KeyModifyEnd();

		curveSX->KeyModifyEnd();
		curveSY->KeyModifyEnd();
		curveSZ->KeyModifyEnd();
	}

	return true;
}

bool Application::ExportAnimationToFbx(std::filesystem::path export_path, int anim_id)
{
	bool status = true;

	RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Exporting animation %d (%s)\n", anim_id, export_path.filename().string().c_str());

	FbxExporter* pExporter = FbxExporter::Create(g_pFbxManager, "");
	pExporter->SetFileExportVersion(FBX_2014_00_COMPATIBLE);

	if (!pExporter->Initialize(export_path.string().c_str(), g_pFbxManager->GetIOPluginRegistry()->GetNativeWriterFormat(), g_pFbxManager->GetIOSettings()))
	{
		RDebug::SystemPanic("Application.cpp", "Failed to initialise FBX exporter (file=%s)\n", export_path.string().c_str());

		return false;
	}

	FbxScene* pScene = FbxScene::Create(g_pFbxManager, export_path.string().c_str());
	pScene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::OpenGL);
	pScene->GetGlobalSettings().SetSystemUnit(FbxSystemUnit::m);

	FbxPose* pBindPoses = FbxPose::Create(pScene, "BindPoses");
	pBindPoses->SetIsBindPose(true);

	std::vector<FbxNode*> pMorphemeRig = this->m_model.CreateFbxMorphemeSkeleton(pScene, pBindPoses, this->m_nmb.GetRig(0));

	if (this->m_fbxExportFlags.m_exportModelWithAnims)
	{
		if (!CreateFbxModel(this, pScene, pBindPoses, pMorphemeRig, export_path, this->m_nmb.GetRig(0), true))
		{
			RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to create FBX model/skeleton (animId=%d, chrId=c%04d)\n", anim_id, this->m_chrId);
			status = false;
		}
	}

	if (!CreateFbxTake(pScene, pMorphemeRig, &this->m_animFiles[anim_id], this->m_nmb.GetFilenameLookupTable()->GetAnimTake(anim_id)))
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to create FBX anim take (animId=%d, chrId=c%04d)\n", anim_id, this->m_chrId);
		status = false;
	}

	pScene->AddPose(pBindPoses);

	pExporter->Export(pScene);
	pScene->Destroy(true);
	pExporter->Destroy(true);

	return status;
}

bool Application::ExportModelToFbx(std::filesystem::path export_path)
{
	bool status = true;

	RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Exporting model to FBX for c%04d\n", this->m_chrId);

	FbxExporter* pExporter = FbxExporter::Create(g_pFbxManager, "");
	pExporter->SetFileExportVersion(FBX_2014_00_COMPATIBLE);

	char chr_id_str[20];
	sprintf(chr_id_str, "c%04d", this->m_chrId);

	std::string model_out = export_path.string() + std::string(chr_id_str) + ".fbx";

	if (!pExporter->Initialize(model_out.c_str(), g_pFbxManager->GetIOPluginRegistry()->GetNativeWriterFormat(), g_pFbxManager->GetIOSettings()))
	{
		RDebug::SystemPanic("Application.cpp", "Failed to initialise FBX exporter (file=%s)\n", model_out);

		return false;
	}

	FbxScene* pScene = FbxScene::Create(g_pFbxManager, chr_id_str);
	pScene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::OpenGL);
	pScene->GetGlobalSettings().SetSystemUnit(FbxSystemUnit::m);

	FbxPose* pBindPoses = FbxPose::Create(pScene, "BindPoses");
	pBindPoses->SetIsBindPose(true);

	if (this->m_fbxExportFlags.m_exportMorphemeRigWithModel)
	{
		std::vector<FbxNode*> pMorphemeRig = this->m_model.CreateFbxMorphemeSkeleton(pScene, pBindPoses, this->m_nmb.GetRig(0));

		if (!CreateFbxModel(this, pScene, pBindPoses, pMorphemeRig, model_out, this->m_nmb.GetRig(0), true))
		{
			RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to create FBX model/skeleton (chrId=c%04d)\n", this->m_chrId);

			status = false;
		}
	}
	else
	{
		std::vector<FbxNode*> pFlverSkeleton = this->m_model.CreateFbxFlverSkeleton(pScene, pBindPoses);

		if (!CreateFbxModel(this, pScene, pBindPoses, pFlverSkeleton, model_out, nullptr, false))
		{
			RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to create FBX model/skeleton (chrId=c%04d)\n", this->m_chrId);

			status = false;
		}
	}

	pScene->AddPose(pBindPoses);

	pExporter->Export(pScene);
	pScene->Destroy(true);
	pExporter->Destroy(true);

	return status;
}

bool Application::ExportToXMD(PWSTR export_path)
{
	RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "XMD export not yet implemented\n");

	return false;
}

bool Application::ExportToFbxTest(PWSTR export_path)
{
	FbxScene* pScene = FbxScene::Create(g_pFbxManager, "testScene");

	FbxNode* pMeshNode = FbxNode::Create(pScene, "meshNode");
	int i, j;
	FbxMesh* lMesh = FbxMesh::Create(pScene, "mesh");

	FbxVector4 lControlPoint0(-50, 0, 50);
	FbxVector4 lControlPoint1(50, 0, 50);
	FbxVector4 lControlPoint2(50, 100, 50);
	FbxVector4 lControlPoint3(-50, 100, 50);
	FbxVector4 lControlPoint4(-50, 0, -50);
	FbxVector4 lControlPoint5(50, 0, -50);
	FbxVector4 lControlPoint6(50, 100, -50);
	FbxVector4 lControlPoint7(-50, 100, -50);

	FbxVector4 lNormalXPos(1, 0, 0);
	FbxVector4 lNormalXNeg(-1, 0, 0);
	FbxVector4 lNormalYPos(0, 1, 0);
	FbxVector4 lNormalYNeg(0, -1, 0);
	FbxVector4 lNormalZPos(0, 0, 1);
	FbxVector4 lNormalZNeg(0, 0, -1);

	// Create control points.
	lMesh->InitControlPoints(24);
	FbxVector4* lControlPoints = lMesh->GetControlPoints();

	lControlPoints[0] = lControlPoint0;
	lControlPoints[1] = lControlPoint1;
	lControlPoints[2] = lControlPoint2;
	lControlPoints[3] = lControlPoint3;
	lControlPoints[4] = lControlPoint1;
	lControlPoints[5] = lControlPoint5;
	lControlPoints[6] = lControlPoint6;
	lControlPoints[7] = lControlPoint2;
	lControlPoints[8] = lControlPoint5;
	lControlPoints[9] = lControlPoint4;
	lControlPoints[10] = lControlPoint7;
	lControlPoints[11] = lControlPoint6;
	lControlPoints[12] = lControlPoint4;
	lControlPoints[13] = lControlPoint0;
	lControlPoints[14] = lControlPoint3;
	lControlPoints[15] = lControlPoint7;
	lControlPoints[16] = lControlPoint3;
	lControlPoints[17] = lControlPoint2;
	lControlPoints[18] = lControlPoint6;
	lControlPoints[19] = lControlPoint7;
	lControlPoints[20] = lControlPoint1;
	lControlPoints[21] = lControlPoint0;
	lControlPoints[22] = lControlPoint4;
	lControlPoints[23] = lControlPoint5;

	// Array of polygon vertices.
	int lPolygonVertices[] = { 0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15,
		16, 17, 18, 19,
		20, 21, 22, 23 };

	// Create polygons. Assign texture and texture UV indices.
	for (i = 0; i < 6; i++)
	{
		//we won't use the default way of assigning textures, as we have
		//textures on more than just the default (diffuse) channel.
		lMesh->BeginPolygon(-1, -1, false);

		for (j = 0; j < 4; j++)
		{
			//this function points 
			lMesh->AddPolygon(lPolygonVertices[i * 4 + j] // Control point index. 
			);
		}

		lMesh->EndPolygon();
	}

	pMeshNode->SetNodeAttribute(lMesh);
	pScene->GetRootNode()->AddChild(pMeshNode);

	FbxExporter* pExporter = FbxExporter::Create(g_pFbxManager, "");

	bool export_status = pExporter->Initialize("test.fbx", -1, g_pFbxManager->GetIOSettings());

	if (!export_status)
	{
		RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "Application.cpp", "Failed to initialise FBXExporter object\n");
		return false;
	}

	pExporter->Export(pScene);
	pExporter->Destroy();

	return true;
}