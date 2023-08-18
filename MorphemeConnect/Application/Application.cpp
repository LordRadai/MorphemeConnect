#include "Application.h"
#include "../extern.h"
#include "../MathHelper/MathHelper.h"
#include <Shlwapi.h>

Application::Application()
{
	this->m_flags.style_editor = false;
}

Application::~Application()
{
	this->m_flags.style_editor = false;
}

void Application::GUIStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowBorderSize = 1;
	style->FrameBorderSize = 0;
	style->PopupBorderSize = 1;
	style->TabBorderSize = 0;

	style->WindowRounding = 0;
	style->ChildRounding = 0;
	style->FrameRounding = 0;
	style->PopupRounding = 0;
	style->ScrollbarRounding = 9;
	style->GrabRounding = 0;
	style->TabRounding = 0;
	style->WindowMenuButtonPosition = ImGuiDir_Left;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
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
	ProcessVariables();
	RenderGUI(APPNAME_A);
}

void Application::RenderGUI(const char* title)
{
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	ImGui::Begin(title, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImGuiID dockSpace = ImGui::GetID("MainWindowDockspace");
	ImGui::DockSpace(dockSpace, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", NULL, &this->m_flags.load_file)) { this->m_flags.load_file = true; }
			if (ImGui::MenuItem("Save", NULL, &this->m_flags.save_file)) { this->m_flags.save_file = true; }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Style Editor", NULL, &this->m_flags.style_editor)) { this->m_flags.style_editor != this->m_flags.style_editor; }

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
	ImGui::Begin("Assets");
	{
		ImGui::BeginTabBar("assets tab bar");
		if (ImGui::BeginTabItem("NSA"))
		{
			static ImGuiTextFilter filter;
			ImGui::Text("Filter:");
			filter.Draw("##asset searchbar", 340.f);

			if (nmb.m_init)
			{
				ImGui::BeginChild("NSA");
				{
					for (int i = 0; i < nmb.m_fileNameLookupTable.m_data->m_animList.m_elemCount; i++)
					{
						std::string anim_name = nmb.GetAnimFileName(i);

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

			if (nmb.m_init)
			{
				ImGui::BeginChild("XMD");
				{
					for (int i = 0; i < nmb.m_fileNameLookupTable.m_data->m_sourceXmdList.m_elemCount; i++)
					{
						std::string anim_name = nmb.GetXmdSourceAnimFileName(i);

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

			if (tae.m_init)
			{
				ImGui::BeginChild("TAE");
				{
					for (int i = 0; i < tae.m_header.m_taeCount; i++)
					{
						std::string anim_name = std::to_string(tae.m_tae[i].m_id);

						if (filter.PassFilter(anim_name.c_str()))
						{
							ImGui::PushID(i);

							if (ImGui::Selectable(anim_name.c_str()))
								this->m_timeActEditorFlags.m_taeId = tae.m_tae[i].m_id;

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
		if (ImGui::Button("Load")) 
		{ 
			if (this->nmb.m_init)
			{
				this->m_eventTrackEditorFlags.m_load = true;
				selectedTrack = -1;
				selectedEvent = -1;
			}
			else
				Debug::Alert(MB_ICONERROR, "Application.cpp", "No NMB file is currently loaded");
		}

		if (this->m_eventTrackEditor.m_animIdx > -1)
			ImGui::Text(nmb.GetAnimFileName(this->m_eventTrackEditor.m_animIdx).c_str());
		else
			ImGui::Text("");

		ImGui::BeginChild("sequencer");
		ImSequencer::Sequencer(&m_eventTrackEditor, &currentFrame, &selectedTrack, &selectedEvent, &expanded, &firstFrame, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_EVENT_ADD | ImSequencer::EDITOR_TRACK_RENAME);
		ImGui::EndChild();
	}
	ImGui::End();

	ImGui::Begin("Event Data");
	{
		if ((this->m_eventTrackEditor.m_eventTracks.size() > 0) && (selectedTrack != -1) && (selectedEvent != -1))
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

			track->SaveEventTrackData(this->m_eventTrackEditorFlags.m_lenMult);
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
		if (ImGui::Button("Load"))
		{
			if (this->tae.m_init)
			{
				this->m_timeActEditorFlags.m_load = true;
				selectedTrackTae = -1;
			}
			else
				Debug::Alert(MB_ICONERROR, "Application.cpp", "No TimeAct file is currently loaded");
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
		ImSequencer::Sequencer(&m_timeActEditor, &currentFrame, &selectedTrackTae, &selectedEventTae, &expandedTae, &firstFrameTae, ImSequencer::EDITOR_EDIT_ALL | ImSequencer::EDITOR_TRACK_ADD | ImSequencer::EDITOR_EVENT_ADD);
		ImGui::EndChild();
	}
	ImGui::End();

	ImGui::Begin("TimeAct Data");
	{
		if ((this->m_timeActEditor.m_tracks.size() > 0) && (selectedTrackTae != -1) && (selectedEventTae != -1))
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
			ImGui::PopItemWidth();

			track->SaveTimeActTrack();
		}
	}
	ImGui::End();

	ImGui::End();
}

void Application::ProcessVariables()
{
	if (this->m_flags.style_editor)
	{
		ImGui::Begin("Style Editor", &this->m_flags.style_editor);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}

	if (this->m_flags.load_file)
	{
		this->m_flags.load_file = false;

		m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();
		this->LoadFile();
	}

	if (this->m_flags.save_file)
	{
		this->m_flags.save_file = false;

		if (this->nmb.m_init)
			this->SaveFile();
		else
		{
			Debug::DebuggerMessage(Debug::LVL_ERROR, "No file is loaded\n");
			Debug::Alert(MB_ICONERROR, "Application.cpp", "No file is loaded\n");
		}
	}

	if (this->nmb.m_init == false)
	{
		this->m_eventTrackEditor.Clear();

		m_eventTrackEditorFlags.m_load = false;
	}

	if (this->m_eventTrackEditorFlags.m_load)
	{
		this->m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();

		if ((this->nmb.m_init == true) && (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1))
		{
			bool found = false;

			for (int idx = 0; idx < this->nmb.m_network.m_data->m_numNodes; idx++)
			{
				NodeDef* node = this->nmb.m_network.m_data->m_nodes[idx];

				if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
				{
					if (this->nmb.m_network.m_data->m_nodes[idx]->m_nodeData[1].m_attrib != NULL)
					{
						NodeDataAttrib_SourceAnim* source_anim = (NodeDataAttrib_SourceAnim*)this->nmb.m_network.m_data->m_nodes[idx]->m_nodeData[1].m_attrib->m_content;
						NodeDataAttrib_EventTrack* event_track = (NodeDataAttrib_EventTrack*)this->nmb.m_network.m_data->m_nodes[idx]->m_nodeData[2].m_attrib->m_content;

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
									MorphemeBundle_EventTrack* event_tracks = nmb.GetEventTrackBundle(event_track->m_eventTracks[0].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, true));
								}

								for (int i = 0; i < event_track->m_eventTracks[1].m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = nmb.GetEventTrackBundle(event_track->m_eventTracks[1].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								for (int i = 0; i < event_track->m_eventTracks[2].m_trackCount; i++)
								{
									MorphemeBundle_EventTrack* event_tracks = nmb.GetEventTrackBundle(event_track->m_eventTracks[2].m_trackSignatures[i]);

									if (event_tracks)
										this->m_eventTrackEditor.m_eventTracks.push_back(EventTrackEditor::EventTrack(event_tracks, this->m_eventTrackEditorFlags.m_lenMult, false));
								}

								if (this->tae.m_init)
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
			{
				Debug::DebuggerMessage(Debug::LVL_INFO, "This animation does not have any event tracks associated to it\n");
				Debug::Alert(MB_ICONINFORMATION, "Application.cpp", "This animation does not have any event tracks associated to it\n");
			}
		}
	}

	if (this->tae.m_init == false)
	{
		this->m_timeActEditor.Clear();

		m_timeActEditorFlags.m_load = false;
	}

	if (this->m_timeActEditorFlags.m_load)
	{
		this->m_timeActEditorFlags.m_load = false;
		this->m_timeActEditor.Clear();

		if (this->tae.m_init && this->m_timeActEditorFlags.m_taeId > -1)
		{
			if (tae.m_tae.size() > 0)
			{
				for (int i = 0; i < tae.m_tae.size(); i++)
				{
					TimeAct* event = &tae.m_tae[i];
					if (event->m_id == this->m_timeActEditorFlags.m_taeId)
					{
						if (tae.m_tae[i].m_taeData->m_eventGroupCount > 0)
						{
							float max = 0;

							for (int j = 0; j < tae.m_tae[i].m_taeData->m_eventGroupCount; j++)
							{
								for (int k = 0; k < tae.m_tae[i].m_taeData->m_groups[j].m_count; k++)
								{
									if (tae.m_tae[i].m_taeData->m_groups[j].m_event[k].m_end > max)
										max = tae.m_tae[i].m_taeData->m_groups[j].m_event[k].m_end;
								}

								this->m_timeActEditor.m_tracks.push_back(&tae.m_tae[i].m_taeData->m_groups[j]);
							}


							this->m_timeActEditor.m_frameMax = MathHelper::TimeToFrame(max);

							if (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1)
								this->m_timeActEditor.m_frameMax = MathHelper::TimeToFrame(this->m_timeActEditorFlags.m_lenght);

							this->m_timeActEditor.m_frameMin = 0;
						}
						else
						{
							Debug::DebuggerMessage(Debug::LVL_INFO, "This TimeAct track has no events associated to it\n");
							Debug::Alert(MB_ICONINFORMATION, "Application.cpp", "This TimeAct track has no events associated to it\n");
						}

						break;
					}
				}
			}
			else
			{
				Debug::DebuggerMessage(Debug::LVL_INFO, "No TimeAct is loaded\n");
				Debug::Alert(MB_ICONINFORMATION, "Application.cpp", "No TimeAct is loaded\n");
			}
			
		}
	}
}

void Application::NetworkCleanup()
{
}

int Application::GetChrIdFromNmbFileName(std::string name)
{
	std::string chr_id;

	int lastCPos = name.find_last_of("\\c");

	chr_id = name.substr(lastCPos + 1, 4);

	Debug::DebuggerMessage(Debug::LVL_DEBUG, "Chr ID: %s\n", chr_id);

	return stoi(chr_id);
}

std::string getTaeFileListFromChrId(std::string tae_path, int chr_id)
{
	std::string chr_id_str = std::to_string(chr_id);

	return "";
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
						PWSTR format = PathFindExtensionW(pszFilePath);
						std::wstring extension = std::wstring(format);

						if (extension.compare(L".nmb") == 0)
						{
							nmb.m_init = false;
							nmb = NMBReader(pszFilePath);
							Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (bundles=%d, len=%d)\n", nmb.m_filePath, nmb.m_bundles.size(), nmb.m_fileSize);							
						}

						if (extension.compare(L".tae") == 0)
						{
							tae.m_init = false;
							tae = TimeActReader(pszFilePath);
							Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (len=%d)\n", tae.m_filePath, tae.m_fileSize);
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
						if (nmb.m_init)
						{
							PWSTR format = PathFindExtensionW(pszOutFilePath);
							std::wstring extension = std::wstring(format);

							if (extension.compare(L".nmb") == 0)
							{
								bool status = nmb.SaveToFile(pszOutFilePath);

								if (status)
									Debug::DebuggerMessage(Debug::LVL_DEBUG, "Save file %ls (bundles=%d, len=%d)\n", nmb.m_outFilePath, nmb.m_bundles.size(), nmb.m_outFileSize);
								else
								{
									Debug::DebuggerMessage(Debug::LVL_ERROR, "Failed to generate NMB file\n");
									Debug::Alert(MB_ICONERROR, "Failed to generate file\n", "NMBReader.cpp");
								}
							}
							else
							{
								Debug::Alert(MB_ICONERROR, "Application.cpp", "Saving TimeAct files is not supported yet\n");
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