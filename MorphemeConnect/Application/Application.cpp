#include "Application.h"
#include "../extern.h"

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
			if (ImGui::MenuItem("Save", NULL)) {}

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

		ImGui::EndTabItem();
	}
	ImGui::End();

	{
		static char categoryInfo[100], valueInfo[255];
		static int selectedEntry = -1;
		static int firstFrame = 0;
		static bool expanded = true;
		static int currentFrame = -1;

		ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Appearing);
		ImGui::Begin("EventTrack");
		{
			if (ImGui::Button("Load")) 
			{ 
				this->m_eventTrackEditorFlags.m_load = true;
				selectedEntry = -1;
			}
			ImGui::SameLine();
			if (ImGui::Button("Save")) { this->m_eventTrackEditorFlags.m_save = true; }

			ImGui::BeginChild("sequencer");
			ImSequencer::Sequencer(&m_eventTrackEditor, &currentFrame, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_STARTEND /*| ImSequencer::SEQUENCER_LOOP_EVENTS*/); //Morpheme supports looped events, DS2 does not use it
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::Begin("Event Data");
		{
			if (selectedEntry != -1)
			{
				EventTrackEditor::EventTrack& item = m_eventTrackEditor.myItems[selectedEntry];
				float startTime = MathHelper::FrameToTime(item.mFrameStart);
				float duration = MathHelper::FrameToTime(item.mFrameEnd);

				ImGui::Text("%s", item.trackName);
				ImGui::PushItemWidth(100);
				ImGui::InputInt("Event ID", &item.eventId, 1, 0);
				if (ImGui::IsItemHovered())
				{
					ImGui::Text(categoryInfo);
				}

				ImGui::InputInt("Event Value", &item.value, 1, 0);
				if (ImGui::IsItemHovered())
				{
					ImGui::Text("Info");
					ImGui::Separator();

					ImGui::Text(valueInfo);
				}

				ImGui::DragFloat("Start Time", &startTime, 1 / 60, 0, MathHelper::FrameToTime(m_eventTrackEditor.mFrameMax, 60), "%.3f", ImGuiSliderFlags_ReadOnly);
				ImGui::DragFloat("End Time", &duration, 1 / 60, 0, MathHelper::FrameToTime(m_eventTrackEditor.mFrameMax, 60), "%.3f", ImGuiSliderFlags_ReadOnly);
				ImGui::PopItemWidth();

				item.SaveEventTrackData(item.morpheme_track, this->m_eventTrackEditorFlags.m_lenMult);
			}
		}
		ImGui::End();
	}

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

		this->LoadFile();
	}

	if (this->m_eventTrackEditorFlags.m_load)
	{
		this->m_eventTrackEditorFlags.m_load = false;
		this->m_eventTrackEditor.Clear();
		this->m_eventTrackList.ClearTrackList();

		if ((this->nmb.m_init == true) && (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1))
		{
			bool found = false;

			for (int idx = 0; idx < this->nmb.m_network.m_data->m_numNodes; idx++)
			{
				NodeDef* node = this->nmb.m_network.m_data->m_nodes[idx];

				if (node->m_nodeTypeID == NodeType_NodeAnimSyncEvents)
				{
					NodeData104* node_data = (NodeData104*)this->nmb.m_network.m_data->m_nodes[idx]->node_data;

					if (node_data != NULL)
					{
						if (node_data->m_attribSourceAnim->m_animIdx == this->m_eventTrackEditorFlags.m_targetAnimIdx)
						{
							this->m_eventTrackEditor.mFrameMin = 0;
							this->m_eventTrackEditor.mFrameMax = MathHelper::TimeToFrame(node_data->m_attribSourceAnim->m_animLen);

							this->m_eventTrackList = MorphemeEventTrackList(node_data->m_attribEventTrack);
							this->m_eventTrackEditorFlags.m_lenMult = node_data->m_attribSourceAnim->m_animLen / node_data->m_attribSourceAnim->m_trackLen;

							int id = 0;

							for (size_t i = 0; i < m_eventTrackList.count_discrete; i++)
							{
								m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_discrete[i]);
								m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_discrete[i], this->m_eventTrackEditorFlags.m_lenMult);

								if (m_eventTrackList.tracks_discrete[i].eventCount > 1)
								{
									for (size_t j = 0; j < m_eventTrackList.count_discreteSub; j++)
									{
										if (m_eventTrackList.tracks_discreteSub[j].parentId == i)
										{
											m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_discreteSub[j]);
											m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_discreteSub[j], this->m_eventTrackEditorFlags.m_lenMult);

											id++;
										}
									}
								}
								else
									id++;
							}

							for (size_t i = 0; i < m_eventTrackList.count_unk; i++)
							{
								m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_unk[i]);
								m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_unk[i], this->m_eventTrackEditorFlags.m_lenMult);

								if (m_eventTrackList.tracks_unk[i].eventCount > 1)
								{
									for (size_t j = 0; j < m_eventTrackList.count_unkSub; j++)
									{
										if (m_eventTrackList.tracks_unkSub[j].parentId == i)
										{
											m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_unkSub[j]);
											m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_unkSub[j], this->m_eventTrackEditorFlags.m_lenMult);

											id++;
										}
									}
								}
								else
									id++;
							}

							for (size_t i = 0; i < m_eventTrackList.count_timed; i++)
							{
								m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_timed[i]);
								m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_timed[i], this->m_eventTrackEditorFlags.m_lenMult);

								if (m_eventTrackList.tracks_timed[i].eventCount > 1)
								{
									for (size_t j = 0; j < m_eventTrackList.count_timedSub; j++)
									{
										if (m_eventTrackList.tracks_timedSub[j].parentId == i)
										{
											m_eventTrackEditor.LoadTrackName(id, m_eventTrackList.tracks_timedSub[j]);
											m_eventTrackEditor.AddMorphemeEventTrack(id, &m_eventTrackList.tracks_timedSub[j], this->m_eventTrackEditorFlags.m_lenMult);

											id++;
										}
									}
								}
								else
									id++;
							}

							if ((m_eventTrackList.count_discrete > 0) || (m_eventTrackList.count_unk > 0) || (m_eventTrackList.count_timed > 0))
							{	
								found = true;
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

	if (this->m_eventTrackEditorFlags.m_save)
	{
		this->m_eventTrackEditorFlags.m_save = false;

		if ((this->nmb.m_init == true) && (this->m_eventTrackEditorFlags.m_targetAnimIdx != -1))
		{
			this->m_eventTrackList.SaveEventTracks();
		}
	}
}

void Application::Dockspace(ImGuiID dockSpace)
{
}

void Application::NetworkCleanup()
{
}

void Application::LoadFile()
{
	COMDLG_FILTERSPEC ComDlgFS[3] = { {L"Morpheme Network Binary", L"*.nmb"},{L"Text", L"*.txt;*.xml;*.json;*.ini"}, {L"All Files",L"*.*"} };

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
						nmb = NMBReader(pszFilePath);
						Debug::DebuggerMessage(Debug::LVL_DEBUG, "Open file %ls (bundles=%d, len=%d)\n", nmb.m_filePath, nmb.m_bundles.size(), nmb.m_fileSize);
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