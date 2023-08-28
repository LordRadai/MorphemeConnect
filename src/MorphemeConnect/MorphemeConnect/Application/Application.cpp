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
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
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
	RenderGUI(APPNAME_A);
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

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Settings", NULL, &this->m_windowStates.m_settingWindow)) { this->m_windowStates.m_settingWindow != this->m_windowStates.m_settingWindow; }

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

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

		if (ImGui::IsItemHovered())
			g_preview.m_camera.m_registerInput = true;

		g_preview.SetViewportSize(width, height);

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

		if (this->m_eventTrackEditorFlags.load_tae && this->m_eventTrackEditorFlags.tae_list.size() > 0)
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
				Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);

				this->m_eventTrackEditorFlags.load_tae = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				this->m_eventTrackEditorFlags.load_tae = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::BeginChild("file_list");
			for (int i = 0; i < this->m_eventTrackEditorFlags.tae_list.size(); i++)
			{
				std::filesystem::path path = this->m_eventTrackEditorFlags.tae_list[i];
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
			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (m_nmb.m_init)
			{
				ImGui::BeginChild("NSA");
				{
					for (int i = 0; i < m_nmb.m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
					{
						std::string anim_name = m_nmb.GetAnimFileName(i);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							if (ImGui::Selectable(anim_name.c_str()))
							{
								this->m_eventTrackEditorFlags.m_targetAnimIdx = i;
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
			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (m_nmb.m_init)
			{
				ImGui::BeginChild("XMD");
				{
					for (int i = 0; i < m_nmb.m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount; i++)
					{
						std::string anim_name = m_nmb.GetXmdSourceAnimFileName(i);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);
							ImGui::Selectable(anim_name.c_str());
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
			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (m_tae.m_init)
			{
				ImGui::BeginChild("TAE");
				{
					for (int i = 0; i < m_tae.m_header.m_taeCount; i++)
					{
						std::string anim_name = std::to_string(m_tae.m_tae[i].m_id);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);

							if (ImGui::Selectable(anim_name.c_str()))
								this->m_timeActEditorFlags.m_taeId = m_tae.m_tae[i].m_id;

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

	static char categoryInfo[100], valueInfo[255];
	static int selectedTrack = -1;
	static int selectedEvent = -1;
	static int firstFrame = 0;
	static bool expanded = true;
	static int currentFrame = 0;

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
			ImSequencer::Sequencer(&m_eventTrackEditor, &currentFrame, &selectedTrack, &selectedEvent, &expanded, focused, & firstFrame, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_TRACK_RENAME | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
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
				ImGui::Text(categoryInfo);
			}

			ImGui::InputInt("Event Value", &track->m_event[selectedEvent].m_value, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Info");
				ImGui::Separator();

				ImGui::Text(valueInfo);
			}

			ImGui::InputFloat("Start Time", &startTime, 0, 0);
			ImGui::InputFloat("End Time", &endTime, 0, 0);
			ImGui::PopItemWidth();

			if (this->m_eventTrackEditorFlags.m_save)
			{
				this->m_eventTrackEditorFlags.m_save = false;
				track->SaveEventTrackData(this->m_eventTrackEditorFlags.m_lenMult);
			}
		}
	}
	ImGui::End();

	static char valueInfoTae[255], eventInfoTae[255];
	static int selectedTrackTae = -1;
	static int selectedEventTae = -1;
	static int firstFrameTae = 0;
	static bool expandedTae = true;

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

			int max = 0;

			for (int i = 0; i < m_timeActEditor.m_tracks.size(); i++)
			{
				for (int j = 0; j < m_timeActEditor.m_tracks[i].m_count; j++)
				{
					if (m_timeActEditor.m_tracks[i].m_event[j].m_frameStart + m_timeActEditor.m_tracks[i].m_event[j].m_duration > max)
						max = m_timeActEditor.m_tracks[i].m_event[j].m_frameStart + m_timeActEditor.m_tracks[i].m_event[j].m_duration;
				}
			}

			if (this->m_eventTrackEditorFlags.m_targetAnimIdx == -1)
				this->m_timeActEditor.m_frameMax = max;

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_timeActEditor, &currentFrame, &selectedTrackTae, &selectedEventTae, &expandedTae, focused, &firstFrameTae, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_TRACK_ADD | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_MARK_ACTIVE_EVENTS);
			ImGui::EndChild();
		}
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("TimeAct Data");
	{
		if ((this->m_timeActEditor.m_tracks.size() > 0) && (selectedTrackTae != -1 && selectedTrackTae < this->m_timeActEditor.m_tracks.size()) && (selectedEventTae != -1 && this->m_timeActEditor.m_tracks[selectedTrackTae].m_count))
		{
			TimeActEditor::TimeActTrack* track = &this->m_timeActEditor.m_tracks[selectedTrackTae];
			float startTime = MathHelper::FrameToTime(track->m_event[selectedEventTae].m_frameStart);
			float endTime = MathHelper::FrameToTime(track->m_event[selectedEventTae].m_duration + track->m_event[selectedEventTae].m_frameStart);

			ImGui::Text(m_timeActEditor.GetEventLabel(selectedTrackTae, selectedEventTae).c_str());
			ImGui::PushItemWidth(100);
			ImGui::InputInt("Event Group", &track->m_eventGroup, 1, 0);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text(valueInfoTae);
			}

			ImGui::InputInt("Event ID", &track->m_event[selectedEventTae].m_value, 1, 0);

			ImGui::InputFloat("Start Time", &startTime);
			ImGui::InputFloat("End Time", &endTime);

			track->m_event[selectedEventTae].m_args->ImGuiEditSection();

			if (this->m_timeActEditorFlags.m_save)
			{
				this->m_timeActEditorFlags.m_save = false;
				track->SaveTimeActTrack();
			}

			ImGui::PopItemWidth();
		}
	}
	ImGui::End();

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

	if (ImGui::BeginTabItem("GUI"))
	{
		ImGui::ShowStyleEditor();

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("EventTrack Editor"))
	{
		ImGui::ColorEdit4("Track", (float*)&this->m_eventTrackEditor.m_colors.m_trackColor);
		ImGui::ColorEdit4("Track Inactive", (float*)&this->m_eventTrackEditor.m_colors.m_trackColorInactive);
		ImGui::ColorEdit4("Track Active", (float*)&this->m_eventTrackEditor.m_colors.m_trackColorActive);
		ImGui::ColorEdit4("Track Inverted", (float*)&this->m_eventTrackEditor.m_colors.m_trackColorInvert);
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
		ImGui::ColorEdit4("Track Inverted", (float*)&this->m_timeActEditor.m_colors.m_trackColorInvert);
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

		ImGui::Text("Input");
		ImGui::Separator();

		ImGui::InputFloat("Width", &g_preview.m_camera.m_width, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Height", &g_preview.m_camera.m_height, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Aspect Ratio", &g_preview.m_camera.m_aspectRatio, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::Text("Speed Settings");
		ImGui::Separator();

		ImGui::DragFloat("Drag Speed", &g_preview.m_camera.m_speedParams.m_dragSpeed, 0.1f, 0.f, 10.f);
		ImGui::DragFloat("Zoom Speed", &g_preview.m_camera.m_speedParams.m_zoomSpeed, 0.1f, 0.f, 100.f);
	
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
		this->m_eventTrackEditor.Clear();
		this->LoadFile();
	}

	if (this->m_flags.m_saveFile)
	{
		this->m_flags.m_saveFile = false;

		if (this->m_nmb.m_init)
			this->SaveFile();
		else
			Debug::Alert(Debug::LVL_ERROR, "Application.cpp", "No file is loaded\n");
	}

	if (this->m_nmb.m_init == false)
	{
		this->m_eventTrackEditor.Clear();

		m_eventTrackEditorFlags.m_load = false;
	}

	if (this->m_eventTrackEditorFlags.m_load)
	{
		this->m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();

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
											this->m_timeActEditorFlags.m_taeId = this->m_eventTrackEditor.m_eventTracks[i].m_event[0].m_value;
											this->m_timeActEditorFlags.m_lenght = source_anim->m_animLen;
											this->m_timeActEditorFlags.m_load = true;
										}
									}
								}

								break;
							}
						}
					}
				}
			}

			if (found == false)
				Debug::Alert(Debug::LVL_INFO, "Application.cpp", "This animation does not have any event tracks associated to it\n");
		}
	}

	if (this->m_tae.m_init == false)
	{
		this->m_timeActEditor.Clear();

		m_timeActEditorFlags.m_load = false;
	}

	if (this->m_timeActEditorFlags.m_load)
	{
		this->m_timeActEditorFlags.m_load = false;
		this->m_timeActEditor.Clear();

		if (this->m_tae.m_init && this->m_timeActEditorFlags.m_taeId > -1)
		{
			if (m_tae.m_tae.size() > 0)
			{
				TimeAct* timeact = this->m_tae.TimeActLookup(this->m_timeActEditorFlags.m_taeId);

				if (timeact)
				{
					if (timeact->m_taeData->m_eventGroupCount > 0)
					{
						float max = 0;

						for (int j = 0; j < timeact->m_taeData->m_eventGroupCount; j++)
						{
							for (int k = 0; k < timeact->m_taeData->m_groups[j].m_count; k++)
							{
								if (timeact->m_taeData->m_groups[j].m_event[k].m_end > max)
									max = timeact->m_taeData->m_groups[j].m_event[k].m_end;
							}

							this->m_timeActEditor.m_tracks.push_back(&timeact->m_taeData->m_groups[j]);
						}

						this->m_timeActEditor.m_frameMax = MathHelper::TimeToFrame(max);

						if (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1)
							this->m_timeActEditor.m_frameMax = MathHelper::TimeToFrame(this->m_timeActEditorFlags.m_lenght);

						this->m_timeActEditor.m_frameMin = 0;
					}
					else
						Debug::Alert(Debug::LVL_INFO, "Application.cpp", "This TimeAct track has no events associated to it\n");
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
	int chr_id;

	int lastCPos = name.find_last_of(L"\\c");

	chr_id_str = name.substr(lastCPos + 1, 4);

	chr_id = stoi(chr_id_str);

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Chr ID: %d\n", chr_id);

	return chr_id;
}

std::vector<std::wstring> getTaeFileListFromChrId(std::wstring tae_path, int chr_id)
{
	std::vector<std::wstring> files;

	std::wstring chr_id_str = std::to_wstring(chr_id);
	
	Debug::DebuggerMessage(Debug::LVL_DEBUG, "TimeAct belonging to c%d:\n", chr_id);
	for (const auto& entry : std::filesystem::directory_iterator(tae_path))
	{
		std::wstring filename = entry.path().filename();
		std::wstring file_chr_id_str = filename.substr(1, 4);
		int file_chr_id = stoi(file_chr_id_str);

		if (file_chr_id == chr_id)
		{
			Debug::DebuggerMessage(Debug::LVL_DEBUG, "\t%ws\n", filename.c_str());
			files.push_back(entry.path());
		}
	}

	if (files.size() == 0)
		Debug::Alert(Debug::LVL_DEBUG, "Application.cpp", "Found 0 TimeAct files that belong to c%d in %ws\n", chr_id, tae_path);

	return files;
}

std::wstring getModelNameFromChrId(std::wstring model_path, int chr_id)
{
	std::wstring chr_id_str = std::to_wstring(chr_id);

	for (const auto& entry : std::filesystem::directory_iterator(model_path))
	{
		std::wstring filename = entry.path().filename();
		std::wstring file_chr_id_str = filename.substr(1, 4);

		int file_chr_id = stoi(file_chr_id_str);

		if (file_chr_id == chr_id && entry.path().extension() == ".bnd")
			return entry.path();
	}
}

void Application::LoadFile()
{
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"Morpheme Network Binary", L"*.nmb"}, {L"TimeAct", L"*.tae"}, {L"Text", L"*.txt;*.xml;*.json;*.ini"}, {L"All Files",L"*.*"} };

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
			pFileOpen->SetFileTypes(4, ComDlgFS);

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
							Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (bundles=%d, len=%d)\n", m_nmb.m_filePath, m_nmb.m_bundles.size(), m_nmb.m_fileSize);							
							
							this->m_eventTrackEditorFlags.chr_id = GetChrIdFromNmbFileName(m_nmb.m_filePath);

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

								this->m_eventTrackEditorFlags.tae_list = getTaeFileListFromChrId(filepath_tae, this->m_eventTrackEditorFlags.chr_id);
								this->m_eventTrackEditorFlags.load_tae = true;

								m_bnd.m_init = false;
								std::wstring path_tmp = getModelNameFromChrId(filepath_dcx, this->m_eventTrackEditorFlags.chr_id);
								PWSTR dcx_path = (wchar_t*)path_tmp.c_str();

								m_bnd = BNDReader(dcx_path);

								char chr_id_str[50];
								sprintf_s(chr_id_str, "%04d", this->m_eventTrackEditorFlags.chr_id);

								std::string filename = "c" + std::string(chr_id_str) + ".flv";

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
						else if (filepath_tae.extension() == ".tae")
						{
							m_tae.m_init = false;
							m_tae = TimeActReader(pszFilePath);
							Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (len=%d)\n", m_tae.m_filePath, m_tae.m_fileSize);
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
	COMDLG_FILTERSPEC ComDlgFS[] = { {L"Morpheme Network Binary", L"*.nmb"}, {L"TimeAct", L"*.tae"}, {L"Text", L"*.txt;*.xml;*.json;*.ini"}, {L"All Files",L"*.*"} };

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
			pFileSave->SetFileTypes(4, ComDlgFS);

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
						if (m_nmb.m_init)
						{
							std::filesystem::path filepath = std::wstring(pszOutFilePath);

							if (filepath.extension() == ".m_nmb")
							{
								bool status = m_nmb.SaveToFile(pszOutFilePath);

								if (status)
									Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (bundles=%d, len=%d)\n", m_nmb.m_outFilePath, m_nmb.m_bundles.size(), m_nmb.m_outFileSize);
								else
									Debug::Alert(Debug::LVL_ERROR, "Failed to generate file\n", "NMBReader.cpp");
							}
							else if (filepath.extension() == ".tae")
							{
								bool status = m_tae.SaveFile(pszOutFilePath);

								if (status)
									Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (taeCount=%d)\n", m_tae.m_outFilePath, m_tae.m_header.m_taeCount);
								else
									Debug::Alert(Debug::LVL_ERROR, "Failed to generate file\n", "TimeActReader.cpp");
							}
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