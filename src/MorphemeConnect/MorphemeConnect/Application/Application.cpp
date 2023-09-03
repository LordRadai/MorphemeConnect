#include "Application.h"
#include "../extern.h"
#include "../MathHelper/MathHelper.h"
#include "../StringHelper/StringHelper.h"
#include "../Scene/Scene.h"

#include <Shlwapi.h>
#include <filesystem>

Application::Application()
{
	this->m_windowStates.m_settingWindow = false;
	this->m_windowStates.m_previewSettings = false;
}

Application::~Application()
{
	this->m_windowStates.m_settingWindow = false;
	this->m_windowStates.m_previewSettings = false;
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
	ProcessVariables();
	RenderGUI("MorphemeConnect");
}

std::string getTaeCategoryTooltip(int category)
{
	INIReader reader(".//MorphemeConnect//res//tooltip//timeact//group.ini");
	
	char default_info[255];
	sprintf_s(default_info, "No specific information is known for this category\n");

	if (reader.ParseError() < 0)
	{
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Failed to load group.ini\n");
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
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Failed to load event.ini\n");
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
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Failed to load group.ini\n");
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
		Debug::DebuggerMessage(Debug::LVL_ERROR, "Failed to load event.ini\n");
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

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", NULL, &this->m_flags.m_loadFile)) { this->m_flags.m_loadFile = true; }
			if (ImGui::MenuItem("Save", NULL, &this->m_flags.m_saveFile)) { this->m_flags.m_saveFile = true; }
			if (ImGui::MenuItem("Save All", NULL, &this->m_flags.m_saveAll)) { this->m_flags.m_saveAll = true; }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Settings", NULL, &this->m_windowStates.m_settingWindow)) { this->m_windowStates.m_settingWindow != this->m_windowStates.m_settingWindow; }

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_Appearing);
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

			if (ImGui::IsMouseDown(0) || ImGui::IsMouseDown(1))
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
		}

		g_preview.SetRenderResolution(width, height);

		ImGui::GetWindowDrawList()->AddImage(g_preview.m_shaderResourceViewViewport, pos, ImVec2(pos.x + width, pos.y + height));
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("Assets");
	{
		static int selected_tae_file_idx = -1;
		char chr_id_str[50];
		sprintf_s(chr_id_str, "%04d", this->m_eventTrackEditorFlags.chr_id);

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

					Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

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
				std::string tae_file = StringHelper::ToNarrow(path.filename().c_str());

				if (ImGui::Selectable(tae_file.c_str()))
				{
					selected_tae_file_idx = i;
					filepath = path.c_str();
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
			if (this->m_nmb.m_init)
				ImGui::Text(StringHelper::ToNarrow(this->m_nmb.m_fileName.c_str()).c_str());

			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (this->m_nmb.m_init)
			{
				ImGui::BeginChild("NSA");
				{
					for (int i = 0; i < m_nmb.m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
					{
						std::string anim_name = "";

						if (this->m_eventTrackEditorFlags.m_edited[i])
							anim_name += "*";

						anim_name += m_nmb.GetAnimFileName(i);

						bool selected = (this->m_eventTrackEditorFlags.m_selectedAnimIdx == i);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							ImGui::Selectable(anim_name.c_str(), &selected);

							if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
							{
								this->m_eventTrackEditorFlags.m_targetAnimIdx = i;
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = i;

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
			if (this->m_nmb.m_init)
				ImGui::Text(StringHelper::ToNarrow(this->m_nmb.m_fileName.c_str()).c_str());

			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (this->m_nmb.m_init)
			{
				ImGui::BeginChild("XMD");
				{
					for (int i = 0; i < m_nmb.m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount; i++)
					{
						std::string anim_name = m_nmb.GetXmdSourceAnimFileName(i);
						bool selected = (this->m_timeActEditorFlags.m_selectedTimeActIdx == i);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							ImGui::Selectable(anim_name.c_str(), &selected);

							if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = i;

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
				
				if (ImGui::Button("Add"))
				{
					if (this->m_tae.AddTimeAct(this->m_timeActFlags.m_addTimeActId) == false)
						Debug::Alert(Debug::LVL_INFO, "TimeActReader.cpp", "Failed to create TimeAct %d\n", this->m_timeActFlags.m_addTimeActId);

					this->m_timeActFlags.m_addTimeAct = false;
					ImGui::CloseCurrentPopup();
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
						Debug::Alert(Debug::LVL_INFO, "TimeActReader.cpp", "Failed to delete TimeAct %d\n", this->m_timeActFlags.m_deleteTimeActId);

					this->m_timeActFlags.m_deleteTimeAct = false;

					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
			else
				this->m_timeActFlags.m_deleteTimeAct = false;

			if (this->m_tae.m_init)
			{
				ImGui::Text(StringHelper::ToNarrow(this->m_tae.m_fileName.c_str()).c_str());

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

			if (this->m_tae.m_init)
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

	static int selectedTrack = -1;
	static int selectedEvent = -1;
	static int firstFrame = 0;
	static bool expanded = true;
	static int currentFrame = 0;
	static float zoomLevel = 5.f;

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("EventTrack");
	{
		bool focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

		if (this->m_nmb.m_init)
		{
			if (ImGui::Button("Load"))
			{
				if (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1)
				{
					this->m_eventTrackEditorFlags.m_load = true;
					selectedTrack = -1;
					selectedEvent = -1;
				}
				else
					Debug::Alert(Debug::LVL_INFO, "Application.cpp", "No animation is selected\n");
			}

			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				if (this->m_eventTrackEditor.GetTrackCount() > 0)
					this->m_eventTrackEditorFlags.m_save = true;
				else
					Debug::Alert(Debug::LVL_INFO, "Application.cpp", "No Event Tracks are loaded\n");
			}

			if (this->m_eventTrackEditor.m_animIdx > -1)
				ImGui::Text(m_nmb.GetAnimFileName(this->m_eventTrackEditor.m_animIdx).c_str());
			else
				ImGui::Text("");

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_eventTrackEditor, &currentFrame, &selectedTrack, &selectedEvent, &expanded, focused, &firstFrame, &zoomLevel, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_TRACK_RENAME | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
			ImGui::EndChild();
		}
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("Event Data");
	{
		if ((this->m_eventTrackEditor.m_eventTracks.size() > 0) && (selectedTrack != -1 && selectedTrack < this->m_eventTrackEditor.m_eventTracks.size()) && (selectedEvent != -1 && this->m_eventTrackEditor.m_eventTracks[selectedTrack].m_numEvents))
		{
			EventTrackEditor::EventTrack* track = &this->m_eventTrackEditor.m_eventTracks[selectedTrack];
			float startTime = MathHelper::FrameToTime(track->m_event[selectedEvent].m_frameStart);
			float endTime = MathHelper::FrameToTime(track->m_event[selectedEvent].m_duration + track->m_event[selectedEvent].m_frameStart);

			ImGui::Text(track->m_name);
			ImGui::PushItemWidth(100);
			ImGui::InputInt("Event ID", &track->m_eventId, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Info");
				ImGui::Separator();

				ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionWidth());
				ImGui::Text(getEventTrackCategoryTooltip(track->m_eventId).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputInt("Event Value", &track->m_event[selectedEvent].m_value, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Info");
				ImGui::Separator();

				ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionWidth());
				ImGui::Text(getEventTrackEventTooltip(track->m_event[selectedEvent].m_value).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputFloat("Start Time", &startTime, ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat("End Time", &endTime, ImGuiInputTextFlags_ReadOnly);
			ImGui::PopItemWidth();

			if (this->m_eventTrackEditorFlags.m_save)
			{
				this->m_eventTrackEditorFlags.m_save = false;
				this->m_eventTrackEditor.SetEditedState(false);

				track->SaveEventTrackData(this->m_eventTrackEditorFlags.m_lenMult);
			}
		}
	}
	ImGui::End();

	static int selectedTrackTae = -1;
	static int selectedEventTae = -1;
	static int firstFrameTae = 0;
	static bool expandedTae = true;
	static int currentFrameTae = 0;
	static float zoomLevelTae = 10.f;

	zoomLevelTae = 2 * zoomLevel;

	if (this->m_eventTrackEditor.GetTrackCount() > 0)
	{
		for (int i = 0; i < this->m_eventTrackEditor.GetTrackCount(); i++)
		{
			if (this->m_eventTrackEditor.m_eventTracks[i].m_eventId == 1000)
			{
				this->m_timeActEditorFlags.m_eventTrackActionTimeActStart = MathHelper::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_frameStart);
				this->m_timeActEditorFlags.m_eventTrackActionTimeActDuration = MathHelper::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_duration);
				this->m_timeActEditorFlags.m_eventTrackActionTimeActValue = this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_value;
			}
		}

		if (this->m_timeActEditorFlags.m_eventTrackActionTimeActValue == this->m_timeActEditorFlags.m_taeId)
			currentFrameTae = MathHelper::TimeToFrame(m_timeActEditor.m_source->CalculatePlaybackPosFromMorphemeEventTrack(this->m_timeActEditorFlags.m_eventTrackActionTimeActStart, this->m_timeActEditorFlags.m_eventTrackActionTimeActDuration, MathHelper::FrameToTime(currentFrame)), 30);
	}

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
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
					selectedTrackTae = -1;
				}
				else
					Debug::Alert(Debug::LVL_INFO, "Application.cpp", "No TimeAct file is currently loaded\n");
			}

			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				if (this->m_tae.m_init)
					this->m_timeActEditorFlags.m_save = true;
				else
					Debug::Alert(Debug::LVL_INFO, "Application.cpp", "No TimeAct track is currently loaded\n");
			}

			if (this->m_timeActEditorFlags.m_taeId > -1)
				ImGui::Text(std::to_string(this->m_timeActEditorFlags.m_taeId).c_str());
			else
				ImGui::Text("");

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_timeActEditor, &currentFrameTae, &selectedTrackTae, &selectedEventTae, &expandedTae, focused, &firstFrameTae, &zoomLevelTae, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_TRACK_ADD | ImSequencer::EDITOR_TRACK_RENAME | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
			ImGui::EndChild();
		}
	}
	ImGui::End();

	zoomLevel = zoomLevelTae * 0.5f;

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("TimeAct Data");
	{
		if ((this->m_timeActEditor.m_tracks.size() > 0) && (selectedTrackTae != -1 && selectedTrackTae < this->m_timeActEditor.m_tracks.size()) && (selectedEventTae != -1 && this->m_timeActEditor.m_tracks[selectedTrackTae].m_count))
		{
			TimeActEditor::TimeActTrack* track = &this->m_timeActEditor.m_tracks[selectedTrackTae];
			float startTime = MathHelper::FrameToTime(track->m_event[selectedEventTae].m_frameStart, 30);
			float endTime = MathHelper::FrameToTime(track->m_event[selectedEventTae].m_duration + track->m_event[selectedEventTae].m_frameStart, 30);

			ImGui::Text(m_timeActEditor.GetEventLabel(selectedTrackTae, selectedEventTae, false).c_str());
			ImGui::PushItemWidth(100);
			ImGui::InputInt("Event Group", &track->m_eventGroup, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Info");
				ImGui::Separator();

				ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionWidth());
				ImGui::Text(getTaeCategoryTooltip(track->m_eventGroup).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputInt("Event ID", &track->m_event[selectedEventTae].m_value, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Info");
				ImGui::Separator();

				ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionWidth());
				ImGui::Text(getTaeEventTooltip(track->m_event[selectedEventTae].m_value).c_str());
				ImGui::PopTextWrapPos();
			}

			ImGui::InputFloat("Start Time", &startTime, ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat("End Time", &endTime, ImGuiInputTextFlags_ReadOnly);

			track->m_event[selectedEventTae].m_args->ImGuiEdit();

			if (this->m_timeActEditorFlags.m_save)
			{
				this->m_timeActEditorFlags.m_save = false;
				this->m_timeActEditor.SetEditedState(false);

				track->SaveTimeActTrack();
			}

			ImGui::PopItemWidth();
		}
	}
	ImGui::End();
}

void Application::RenderPopups()
{

}

void Application::SettingsWindow()
{
	ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Appearing);
	ImGui::Begin("Settings##gui", &this->m_windowStates.m_settingWindow);

	ImGui::BeginTabBar("settings");

	/*
	if (ImGui::BeginTabItem("GUI"))
	{
		ImGui::ShowStyleEditor();

		ImGui::EndTabItem();
	}
	*/

	if (ImGui::BeginTabItem("EventTrack Editor"))
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

	if (ImGui::BeginTabItem("TimeAct Editor"))
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
		ImGui::Text("Parameters");
		ImGui::Separator();

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

		ImGui::Text("Input");
		ImGui::Separator();

		ImGui::Checkbox("Invert X Drag", &g_preview.m_camera.m_settings.m_dragInvertX);
		ImGui::Checkbox("Invert Y Drag", &g_preview.m_camera.m_settings.m_dragInvertY);

		ImGui::Checkbox("Invert X Rotation", &g_preview.m_camera.m_settings.m_rotInvertX);
		ImGui::Checkbox("Invert Y Rotation", &g_preview.m_camera.m_settings.m_rotInvertY);

		ImGui::Text("Speed Settings");
		ImGui::Separator();

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

void Application::ProcessVariables()
{
	if (this->m_windowStates.m_settingWindow)
	{
		this->SettingsWindow();
	}

	if (this->m_windowStates.m_previewSettings)
	{
		this->PreviewDebugManagerWindow();
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

	if (this->m_flags.m_saveFile)
	{
		this->m_flags.m_saveFile = false;

		if (this->m_nmb.m_init || this->m_tae.m_init)
			this->SaveFile();
		else
			Debug::Alert(Debug::LVL_ERROR, "Application.cpp", "No file is loaded\n");
	}

	if (this->m_flags.m_saveAll)
	{
		this->m_flags.m_saveAll = false;

		if (this->m_nmb.m_init)
		{
			bool status = m_nmb.SaveToFile(this->m_nmb.m_filePath);

			if (status)
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.m_outFilePath, m_nmb.m_bundles.size(), m_nmb.m_outFileSize);
			else
				Debug::Alert(Debug::LVL_ERROR, "Failed to generate file\n", "NMBReader.cpp");
		}

		if (this->m_tae.m_init)
		{
			bool status = m_tae.SaveFile(this->m_tae.m_filePath);

			if (status)
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
			else
				Debug::Alert(Debug::LVL_ERROR, "Failed to generate file\n", "TimeActReader.cpp");
		}
	}

	if (this->m_nmb.m_init == false)
	{
		this->m_eventTrackEditor.Clear();

		m_eventTrackEditorFlags.m_load = false;
		m_eventTrackEditorFlags.m_selectedAnimIdx = -1;
	}

	if (this->m_eventTrackEditorFlags.m_load)
	{
		this->m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();

		this->m_timeActEditor.Clear();

		if ((this->m_nmb.m_init == true) && (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1))
		{
			bool found = false;

			for (int idx = 0; idx < this->m_nmb.m_network.m_data->m_numNodes; idx++)
			{
				NodeDef* node = this->m_nmb.m_network.m_data->m_nodes[idx];

				if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
				{
					if (this->m_nmb.m_network.m_data->m_nodes[idx]->m_nodeData[1].m_attrib != NULL)
					{
						NodeDataAttrib_SourceAnim* source_anim = (NodeDataAttrib_SourceAnim*)this->m_nmb.m_network.m_data->m_nodes[idx]->m_nodeData[1].m_attrib->m_content;
						NodeDataAttrib_EventTrack* event_track = (NodeDataAttrib_EventTrack*)this->m_nmb.m_network.m_data->m_nodes[idx]->m_nodeData[2].m_attrib->m_content;

						if (source_anim->m_animIdx == this->m_eventTrackEditorFlags.m_targetAnimIdx)
						{
							this->m_eventTrackEditor.m_nodeSource = node;
							this->m_eventTrackEditor.m_frameMin = 0;
							this->m_eventTrackEditor.m_frameMax = MathHelper::TimeToFrame(source_anim->m_animLen);
							this->m_eventTrackEditor.m_animIdx = source_anim->m_animIdx;

							this->m_eventTrackEditorFlags.m_lenMult = source_anim->m_animLen / source_anim->m_trackLen;

							int track_count = 0;
							for (size_t i = 0; i < 3; i++)
								track_count += event_track->m_eventTracks[i].m_trackCount;

							this->m_eventTrackEditor.m_eventTracks.reserve(track_count);

							if (track_count > 0)
							{
								found = true;

								for (int i = 0; i < event_track->m_eventTracks[0].m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->m_eventTracks[0].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, true));
								}

								for (int i = 0; i < event_track->m_eventTracks[1].m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->m_eventTracks[1].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								for (int i = 0; i < event_track->m_eventTracks[2].m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = m_nmb.GetEventTrackBundle(event_track->m_eventTracks[2].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								if (this->m_tae.m_init)
								{
									for (size_t i = 0; i < this->m_eventTrackEditor.m_eventTracks.size(); i++)
									{
										if (this->m_eventTrackEditor.m_eventTracks[i].m_eventId == 1000)
										{
											this->m_timeActEditorFlags.m_eventTrackActionTimeActStart = MathHelper::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_frameStart);
											this->m_timeActEditorFlags.m_eventTrackActionTimeActDuration = MathHelper::FrameToTime(this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_duration);

											this->m_timeActEditorFlags.m_taeId = this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_value;

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
						}
					}
				}
			}
		}
	}

	if (this->m_tae.m_init == false)
	{
		this->m_timeActEditor.Clear();

		m_timeActEditorFlags.m_load = false;
		m_timeActEditorFlags.m_selectedTimeActIdx = -1;
	}

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
					if (timeact->m_taeData->m_eventGroupCount > 0)
					{
						for (int j = 0; j < timeact->m_taeData->m_eventGroupCount; j++)
							this->m_timeActEditor.m_tracks.push_back(&timeact->m_taeData->m_groups[j]);

						float trackLen = (float)timeact->m_taeData->m_animData->m_lenght / (float)timeact->m_taeData->m_animData->m_fps;

						this->m_timeActEditor.m_frameMax = MathHelper::TimeToFrame(trackLen, 30);
						this->m_timeActEditor.m_frameMin = 0;
					}
				}
				else
					Debug::Alert(Debug::LVL_INFO, "Application.cpp", "TimeAct %d not found\n", this->m_timeActEditorFlags.m_taeId);
			}
			else
				Debug::Alert(Debug::LVL_INFO, "Application.cpp", "No TimeAct is loaded\n");			
		}
	}
}

void Application::NetworkCleanup()
{
}

int Application::GetChrIdFromNmbFileName(std::wstring name)
{
	std::wstring chr_id_str;
	int chr_id = -1;

	int lastCPos = name.find_last_of(L"\\");

	if (name.substr(lastCPos + 1, 1).compare(L"c") != 0)
		return -1;

	chr_id_str = name.substr(lastCPos + 2, 4);

	chr_id = stoi(chr_id_str);

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Chr ID: %d\n", chr_id);

	return chr_id;
}

std::wstring Application::GetObjIdFromTaeFileName(std::wstring name)
{
	std::wstring obj_id;

	int lastCPos = name.find_last_of(L"\\");

	obj_id = name.substr(lastCPos + 1, 8);

	if (obj_id.substr(0, 1).compare(L"o") != 0)
		return L"";

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Obj ID: %s\n", obj_id);

	return obj_id;
}

std::vector<std::wstring> getTaeFileListFromChrId(std::wstring tae_path, std::wstring chr_id)
{
	std::vector<std::wstring> files;
	
	for (const auto& entry : std::filesystem::directory_iterator(tae_path))
	{
		if (entry.path().extension().compare(".tae") == 0)
		{
			std::wstring filename = entry.path().filename();
			std::wstring file_chr_id_str = filename.substr(1, 4);

			if (file_chr_id_str.compare(chr_id) == 0)
			{
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "\t%ws\n", filename.c_str());
				files.push_back(entry.path());
			}
		}	
	}

	if (files.size() == 0)
		Debug::Alert(Debug::LVL_DEBUG, "Application.cpp", "Found 0 TimeAct files that belong to c%d in %ws\n", chr_id, tae_path);

	return files;
}

std::wstring getModelNameFromChrId(std::wstring model_path, std::wstring chr_id)
{
	for (const auto& entry : std::filesystem::directory_iterator(model_path))
	{
		if (entry.path().extension().compare(".bnd") == 0)
		{
			std::wstring filename = entry.path().filename();
			std::wstring file_chr_id_str = filename.substr(1, 4);

			if (file_chr_id_str.compare(chr_id) == 0)
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
						std::filesystem::path filepath_tae = std::wstring(pszFilePath);

						if (filepath_tae.extension() == ".nmb")
						{
							m_nmb.m_init = false;
							m_nmb = NMBReader(pszFilePath);
							
							if (m_nmb.m_init)
							{
								Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (bundles=%d, len=%d)\n", m_nmb.m_filePath, m_nmb.m_bundles.size(), m_nmb.m_fileSize);

								this->m_eventTrackEditorFlags.m_targetAnimIdx = -1;
								this->m_eventTrackEditorFlags.m_selectedAnimIdx = -1;

								this->m_eventTrackEditorFlags.m_edited.clear();
								this->m_eventTrackEditorFlags.m_edited.reserve(m_nmb.m_fileNameLookupTable.m_data->m_animList.m_elemCount);

								for (int i = 0; i < m_nmb.m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
									this->m_eventTrackEditorFlags.m_edited.push_back(false);

								this->m_eventTrackEditorFlags.chr_id = GetChrIdFromNmbFileName(m_nmb.m_filePath);

								if (this->m_eventTrackEditorFlags.chr_id != -1)
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
										swprintf_s(chr_id_str, L"%04d", this->m_eventTrackEditorFlags.chr_id);

										std::wstring string = std::wstring(chr_id_str);

										this->m_eventTrackEditorFlags.m_taeList = getTaeFileListFromChrId(filepath_tae, chr_id_str);
										this->m_eventTrackEditorFlags.m_loadTae = true;

										m_bnd.m_init = false;
										std::wstring path_tmp = getModelNameFromChrId(filepath_dcx, chr_id_str);

										if (path_tmp.compare(L"") != 0)
										{
											PWSTR dcx_path = (wchar_t*)path_tmp.c_str();

											m_bnd = BNDReader(dcx_path);

											std::string filename = "c" + StringHelper::ToNarrow(string.c_str()) + ".flv";

											for (size_t i = 0; i < m_bnd.m_fileCount; i++)
											{
												if (m_bnd.m_files[i].m_name == filename)
												{
													UMEM* umem = uopenMem(m_bnd.m_files[i].m_data, m_bnd.m_files[i].m_uncompressedSize);
													FLVER2 flver_model = FLVER2(umem);

													this->m_model = FlverModel(umem);

													Debug::DebuggerMessage(Debug::LVL_DEBUG, "Loaded model %s\n", filename.c_str());
													break;
												}
											}
										}
									}
								}
							}
						}
						else if (filepath_tae.extension() == ".tae")
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

								Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

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

											std::string filename = StringHelper::ToNarrow(obj_id.c_str()) + ".flv";

											for (size_t i = 0; i < m_bnd.m_fileCount; i++)
											{
												if (m_bnd.m_files[i].m_name == filename)
												{
													UMEM* umem = uopenMem(m_bnd.m_files[i].m_data, m_bnd.m_files[i].m_uncompressedSize);
													FLVER2 flver_model = FLVER2(umem);

													this->m_model = FlverModel(umem);

													Debug::DebuggerMessage(Debug::LVL_DEBUG, "Loaded model %s\n", filename.c_str());
													break;
												}
											}
										}
									}
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
								Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.m_outFilePath, m_nmb.m_bundles.size(), m_nmb.m_outFileSize);
							else
								Debug::Alert(Debug::LVL_ERROR, "NMBReader.cpp", "Failed to generate NMB file\n");
						}
						else if (filepath.extension() == ".tae")
						{
							bool status = m_tae.SaveFile(pszOutFilePath);

							if (status)
								Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
							else
								Debug::Alert(Debug::LVL_ERROR, "TimeActReader.cpp", "Failed to generate TAE file\n");
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