// https://github.com/CedricGuillemet/ImGuizmo
// v 1.83
//
// The MIT License(MIT)
//
// Copyright(c) 2021 Cedric Guillemet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "ImSequencer.h"
#include "../imgui/imgui.h"
#include "../MathHelper/MathHelper.h"
#include <cstdlib>
#include "../Application/Application.h"

#define TRACK_COLOR 0xFFEB5050
#define TRACK_COLOR_INACTIVE 0xFF464646
#define TRACK_COLOR_INVERT 0xFF633132
#define TRACK_COLOR_ACTIVE 0xFF633132
#define TRACK_BOUND 0xFF1D0D0E
#define TRACK_BOUND_ACTIVE 0xFF0000FF
#define TRACK_TEXT_COLOR 0xFFFFFFFF

namespace ImSequencer
{
#ifndef IMGUI_DEFINE_MATH_OPERATORS
    static ImVec2 operator+(const ImVec2& a, const ImVec2& b) {
        return ImVec2(a.x + b.x, a.y + b.y);
    }
#endif

    static bool SequencerAddDelButton(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, bool add = true)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImRect delRect(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        bool overDel = delRect.Contains(io.MousePos);

        int delColor = 0xFFFF9E61;

        if (overDel && io.MouseDown[0])
            delColor = 0xFFFFC099;

        float midy = pos.y + size.x / 2 - 0.5f;
        float midx = pos.x + size.y / 2 - 0.5f;

        //draw_list->AddRectFilled(delRect.Min, delRect.Max, buttonCol, 0);
        //draw_list->AddRect(delRect.Min, delRect.Max, delColor, 0);
        if (add)
        {
            draw_list->AddLine(ImVec2(delRect.Min.x + 5, midy), ImVec2(delRect.Max.x - 5, midy), 0xFF000000, 5);
            draw_list->AddLine(ImVec2(midx, delRect.Min.y + 5), ImVec2(midx, delRect.Max.y - 5), 0xFF000000, 5);

            draw_list->AddLine(ImVec2(delRect.Min.x + 3, midy), ImVec2(delRect.Max.x - 3, midy), delColor, 2);
            draw_list->AddLine(ImVec2(midx, delRect.Min.y + 3), ImVec2(midx, delRect.Max.y - 3), delColor, 2);
        }
        else
        {
            draw_list->AddLine(ImVec2(delRect.Min.x + 5, midy), ImVec2(delRect.Max.x - 5, midy), 0xFF000000, 5);

            draw_list->AddLine(ImVec2(delRect.Min.x + 3, midy), ImVec2(delRect.Max.x - 3, midy), delColor, 2);
        }

        return overDel;
    }

    static bool SequencerAddRemoveButton(ImDrawList* draw_list, ImVec2 pos, ImVec2 size)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImRect delRect(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        bool overDel = delRect.Contains(io.MousePos);

        int delColor = 0xFFFF9E61;

        if (overDel && io.MouseDown[0])
            delColor = 0xFFFFC099;

        //draw_list->AddRectFilled(delRect.Min, delRect.Max, buttonCol, 0);
        //draw_list->AddRect(delRect.Min, delRect.Max, delColor, 0);

        draw_list->AddLine(ImVec2(delRect.Min.x + 5, delRect.Min.y + 5), ImVec2(delRect.Max.x - 5, delRect.Max.y - 5), 0xFF000000, 5);
        draw_list->AddLine(ImVec2(delRect.Min.x + 5, delRect.Max.y - 5), ImVec2(delRect.Max.x - 5, delRect.Min.y + 5), 0xFF000000, 5);

        draw_list->AddLine(ImVec2(delRect.Min.x + 3, delRect.Min.y + 3), ImVec2(delRect.Max.x - 3, delRect.Max.y - 3), delColor, 2);
        draw_list->AddLine(ImVec2(delRect.Min.x + 3, delRect.Max.y - 3), ImVec2(delRect.Max.x - 3, delRect.Min.y + 3), delColor, 2);

        return overDel;
    }

    static bool SequencerAddTrackButton(ImDrawList* draw_list, ImVec2 pos, ImVec2 size)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImVec2 textSize = ImGui::CalcTextSize("Add Track");
        pos.x -= textSize.x;

        ImRect delRect(ImVec2(pos.x - size.x, pos.y), ImVec2(pos.x + textSize.x + size.x, pos.y + size.y));
        ImVec2 textP(delRect.Min.x + (delRect.Max.x - delRect.Min.x - textSize.x) / 2, delRect.Max.y + (delRect.Min.y - delRect.Max.y - textSize.y) / 2);

        bool overDel = delRect.Contains(io.MousePos);

        int buttonCol = 0xFF303030;

        if (overDel && io.MouseDown[0])
            buttonCol = 0xFF606060;

        draw_list->AddRectFilled(delRect.Min, delRect.Max, buttonCol, 0);
        draw_list->AddRect(delRect.Min, delRect.Max, 0xFF000000, 0);
        draw_list->AddText(textP, 0xFFFFFFFF, "Add Track");

        return overDel;
    }

    static bool SequencerAddTrackLabel(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, char* label)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImVec2 textSize = ImGui::CalcTextSize(label);

        ImRect delRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y));

        bool overDel = delRect.Contains(io.MousePos);

        int buttonCol = 0xFF303030;

        draw_list->AddRectFilled(delRect.Min, delRect.Max, buttonCol, 0);
        draw_list->AddRect(delRect.Min, delRect.Max, 0xFF000000, 0);

        ImGui::RenderTextClipped(delRect.Min + ImVec2(5, 0), delRect.Max - ImVec2(5, 0), label, NULL, &textSize, ImVec2(0.f, 0.5f), &delRect);

        return overDel;
    }

    bool Sequencer(EventTrackEditor* eventTrackEditor, int* currentFrame, int* selectedTrack, int* selectedEvent, bool* expanded, int* firstFrame, int sequenceOptions)
    {
        bool ret = false;
        ImGuiIO& io = ImGui::GetIO();
        int cx = (int)(io.MousePos.x);
        int cy = (int)(io.MousePos.y);
        static float framePixelWidth = 11.f;
        static float framePixelWidthTarget = 11.f;

        static bool resizeLegend = false;
        static int legendWidth = 210;

        static int movingTrack = -1;
        static int movingEvent = -1;
        static int movingPos = -1;

        enum MovingPart
        {
            MovingPart_None,
            MovingPart_Start,
            MovingPart_End,
            MovingPart_All
        };

        static int movingPart;

        bool reload = false;
        bool removeTrack = false;
        bool renameTrack = false;
        static char trackRename[50] = "";

        bool addTrack = false;
        static int addTrackEventId = 0;
        static char addTrackName[50] = "MyTrack";
        static bool addTrackType = true;

        static MorphemeBundle_EventTrack::BundleData_EventTrack::Event addEvent;

        bool delEvent = false;

        int ItemHeight = 22;

        static bool popupOpened = false;

        if (!eventTrackEditor->GetTrackCount())
            return false;

        ImGui::BeginGroup();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
         
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();        // Resize canvas to what's available

        int firstFrameUsed = firstFrame ? *firstFrame : 0;

        int controlHeight = eventTrackEditor->GetTrackCount() * ItemHeight;

        int frameCount = ImMax(eventTrackEditor->GetFrameMax() - eventTrackEditor->GetFrameMin(), 1);

        canvas_size.y = controlHeight + 2.5 * ItemHeight;

        static bool MovingScrollBar = false;
        static bool MovingCurrentFrame = false;
        struct CustomDraw
        {
            int index;
            ImRect customRect;
            ImRect legendRect;
            ImRect clippingRect;
            ImRect legendClippingRect;
        };
        ImVector<CustomDraw> customDraws;
        ImVector<CustomDraw> compactCustomDraws;

        // zoom in/out
        const int visibleFrameCount = (int)floorf((canvas_size.x - legendWidth) / framePixelWidth);
        const float barWidthRatio = ImMin(visibleFrameCount / (float)frameCount, 1.f);
        const float barWidthInPixels = barWidthRatio * (canvas_size.x - legendWidth);

        ImRect regionRect(canvas_pos, canvas_pos + canvas_size);

        static bool panningView = false;
        static ImVec2 panningViewSource;
        static int panningViewFrame;
        if (ImGui::IsWindowFocused() && io.KeyAlt && io.MouseDown[2])
        {
            if (!panningView)
            {
                panningViewSource = io.MousePos;
                panningView = true;
                panningViewFrame = *firstFrame;
            }
            *firstFrame = panningViewFrame - int((io.MousePos.x - panningViewSource.x) / framePixelWidth);
            *firstFrame = ImClamp(*firstFrame, eventTrackEditor->GetFrameMin(), eventTrackEditor->GetFrameMax() - visibleFrameCount);
        }
        if (panningView && !io.MouseDown[2])
        {
            panningView = false;
        }
        framePixelWidthTarget = ImClamp(framePixelWidthTarget, 0.1f, 50.f);

        framePixelWidth = ImLerp(framePixelWidth, framePixelWidthTarget, 0.33f);

        frameCount = eventTrackEditor->GetFrameMax() - eventTrackEditor->GetFrameMin();
        if (visibleFrameCount >= frameCount && firstFrame)
            *firstFrame = eventTrackEditor->GetFrameMin();

        // --
        if (expanded && !*expanded)
        {
            ImGui::InvisibleButton("canvas", ImVec2(canvas_size.x - canvas_pos.x, (float)ItemHeight));
            draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_size.x + canvas_pos.x, canvas_pos.y + ItemHeight), 0xFF3D3837, 0);
            char tmps[512];
            ImFormatString(tmps, IM_ARRAYSIZE(tmps), "%d Frames / %d tracks", frameCount, eventTrackEditor->GetTrackCount());
            draw_list->AddText(ImVec2(canvas_pos.x + 26, canvas_pos.y + 2), 0xFFFFFFFF, tmps);
        }
        else
        {
            bool hasScrollBar(true);

            // test scroll area
            ImVec2 headerSize(canvas_size.x, (float)ItemHeight);
            ImVec2 scrollBarSize(canvas_size.x, 14.f);
            ImGui::InvisibleButton("topBar", headerSize);
            draw_list->AddRectFilled(canvas_pos, canvas_pos + headerSize, 0xFFFF0000, 0);
            ImVec2 childFramePos = ImGui::GetCursorScreenPos();
            ImVec2 childFrameSize(canvas_size.x, canvas_size.y - 8.f - headerSize.y - (hasScrollBar ? scrollBarSize.y : 0));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);

            ImGui::BeginChildFrame(889, childFrameSize);
            eventTrackEditor->focused = ImGui::IsWindowFocused();
            ImGui::InvisibleButton("contentBar", ImVec2(canvas_size.x, float(controlHeight)));
            const ImVec2 contentMin = ImGui::GetItemRectMin();
            const ImVec2 contentMax = ImGui::GetItemRectMax();
            const ImRect contentRect(contentMin, contentMax);
            const float contentHeight = contentMax.y - contentMin.y;

            // full background
            draw_list->AddRectFilled(canvas_pos, canvas_pos + canvas_size, 0xFF242424, 0);

            // current frame top
            ImRect topRect(ImVec2(canvas_pos.x + legendWidth, canvas_pos.y), ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + ItemHeight));
            ImRect legendRect(ImVec2(canvas_pos.x + legendWidth, canvas_pos.y), ImVec2(canvas_pos.x + legendWidth + 10, canvas_pos.y + ItemHeight));

            if (!popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1 && legendRect.Contains(io.MousePos))
            {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));

                if (io.MouseDown[0])
                    resizeLegend = true;
            }

            if (resizeLegend)
            {
                legendWidth = (int)((io.MousePos.x - contentMin.x));
            }

            if (resizeLegend && io.MouseReleased[0])
                resizeLegend = false;

            //header
            draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_size.x + canvas_pos.x, canvas_pos.y + ItemHeight), 0xFF404040, 0);
            if (sequenceOptions & EDITOR_TRACK_ADD)
            {
                if (SequencerAddTrackButton(draw_list, ImVec2(canvas_pos.x + legendWidth - 8, canvas_pos.y + 2), ImVec2(4, ItemHeight * 0.8f)) && !popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1)
                {
                    SetCursor(LoadCursor(NULL, IDC_HAND));

                    if (io.MouseReleased[0])
                    {
                        popupOpened = true;
                        ImGui::OpenPopup("addTrack");
                    }
                }

                ImGui::PopStyleColor();
                if (ImGui::BeginPopup("addTrack"))
                {
                    ImGui::Text("Add Track");
                    ImGui::Separator();

                    ImGui::InputText("Name", addTrackName, 50);
                    ImGui::InputInt("Event ID", &addTrackEventId);

                    const char* types[2] = {"Discrete", "Duration"};

                    if (ImGui::BeginCombo("Type", types[addTrackType]))
                    {
                        for (size_t i = 0; i < 2; i++)
                        {
                            const bool selected = (addTrackType == i);
                            if (ImGui::Selectable(types[i], addTrackType))
                                addTrackType = i;
                        }

                        ImGui::EndCombo();
                    }

                    if (ImGui::Button("Add Track") || GetAsyncKeyState(VK_RETURN) & 1)
                    {
                        eventTrackEditor->AddTrack(addTrackEventId, addTrackName, addTrackType);
                        ImGui::CloseCurrentPopup();

                        *selectedTrack = -1;
                        *selectedEvent = -1;

                        reload = true;
                    }

                    ImGui::EndPopup();
                }

                ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);
            }

            if (sequenceOptions & EDITOR_CHANGE_FRAME && currentFrame && topRect.Contains(io.MousePos))
            {
                SetCursor(LoadCursor(NULL, IDC_HAND));

                if (!resizeLegend && !popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1 && io.MouseDown[0])
                    MovingCurrentFrame = true;
            }

            if (MovingCurrentFrame)
            {
                if (frameCount)
                {
                    *currentFrame = (int)((io.MousePos.x - topRect.Min.x) / framePixelWidth) + firstFrameUsed;
                    if (*currentFrame < eventTrackEditor->GetFrameMin())
                        *currentFrame = eventTrackEditor->GetFrameMin();
                    if (*currentFrame >= eventTrackEditor->GetFrameMax())
                        *currentFrame = eventTrackEditor->GetFrameMax();
                }
                if (!io.MouseDown[0])
                    MovingCurrentFrame = false;
            }

            //header frame number and lines
            int modFrameCount = frameCount * 4;
            int frameStep = 1;
            while ((modFrameCount * framePixelWidth) < 150)
            {
                modFrameCount *= 2;
                frameStep *= 2;
            };
            int halfModFrameCount = modFrameCount / 2;

            auto drawLine = [&](int i, int regionHeight) {
                bool baseIndex = ((i % modFrameCount) == 0) || (i == eventTrackEditor->GetFrameMax() || i == eventTrackEditor->GetFrameMin());
                bool halfIndex = (i % halfModFrameCount) == 0;
                ImVec2 pos = ImVec2(contentMin.x + legendWidth - firstFrameUsed * framePixelWidth, contentMin.y + ItemHeight * i + 1);
                float px = pos.x + i * framePixelWidth - 1;
                //int px = (int)canvas_pos.x + int(i * framePixelWidth) + legendWidth + int(firstFrameUsed * framePixelWidth) + 3;
                int tiretStart = baseIndex ? 4 : (halfIndex ? 10 : 14);
                int tiretEnd = baseIndex ? regionHeight : ItemHeight;              

                if (px <= (canvas_size.x + canvas_pos.x) && px >= (canvas_pos.x + legendWidth))
                {
                    draw_list->AddLine(ImVec2((float)px, canvas_pos.y + (float)tiretStart), ImVec2((float)px, canvas_pos.y + (float)tiretEnd - 1), 0xFF606060, 1);

                    draw_list->AddLine(ImVec2((float)px, canvas_pos.y + (float)ItemHeight), ImVec2((float)px, canvas_pos.y + (float)regionHeight - 1), 0x30606060, 1);
                }

                if (baseIndex && px > (canvas_pos.x + legendWidth))
                {
                    char tmps[512];
                    ImFormatString(tmps, IM_ARRAYSIZE(tmps), "%.3f", MathHelper::FrameToTime(i));
                    draw_list->AddText(ImVec2((float)(px + 6), canvas_pos.y), 0xFFBBBBBB, tmps);
                }
            };

            auto drawLineContent = [&](int i, int /*regionHeight*/) {
                //int px = (int)canvas_pos.x + int(i * framePixelWidth) + legendWidth + int(firstFrameUsed * framePixelWidth) + 3;
                ImVec2 pos = ImVec2(contentMin.x + legendWidth - firstFrameUsed * framePixelWidth, contentMin.y + ItemHeight * i + 1);
                float px = pos.x + i * framePixelWidth - 1;
                int tiretStart = int(contentMin.y);
                int tiretEnd = int(contentMax.y);

                if (px <= (canvas_size.x + canvas_pos.x) && px >= (canvas_pos.x + legendWidth))
                {
                    //draw_list->AddLine(ImVec2((float)px, canvas_pos.y + (float)tiretStart), ImVec2((float)px, canvas_pos.y + (float)tiretEnd - 1), 0xFF606060, 1);

                    draw_list->AddLine(ImVec2(float(px), float(tiretStart)), ImVec2(float(px), float(tiretEnd)), 0x30606060, 1);
                }
            };
            for (int i = eventTrackEditor->GetFrameMin() + 1; i <= eventTrackEditor->GetFrameMax(); i += frameStep)
            {
                drawLine(i, ItemHeight);
            }
            drawLine(eventTrackEditor->GetFrameMin(), ItemHeight);
            drawLine(eventTrackEditor->GetFrameMax(), ItemHeight);

            for (int i = eventTrackEditor->GetFrameMax() + 1; i <= 500; i += frameStep)
            {
                drawLine(i, ItemHeight);
            }

            // clip content
            draw_list->PushClipRect(childFramePos, childFramePos + childFrameSize, true);

            // draw item names in the legend rect on the left
            size_t customHeight = 0;
            for (int i = 0; i < eventTrackEditor->GetTrackCount(); i++)
            {
                ImVec2 tpos(contentMin.x + 3, contentMin.y + i * ItemHeight + 2 + customHeight);
                bool overLabel = SequencerAddTrackLabel(draw_list, ImVec2(tpos.x, tpos.y), ImVec2(legendWidth - ItemHeight - ItemHeight - 15, ItemHeight * 0.9f), eventTrackEditor->GetTrackName(i));

                if (sequenceOptions & EDITOR_TRACK_ADD)
                {                    
                    if (SequencerAddRemoveButton(draw_list, ImVec2(contentMin.x + legendWidth - ItemHeight - ItemHeight + 2 - 10, tpos.y + 2), ImVec2(ItemHeight * 0.8f, ItemHeight * 0.8f)) && !popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1)
                    {
                        SetCursor(LoadCursor(NULL, IDC_HAND));

                        if (io.MouseReleased[0])
                        {
                            *selectedTrack = i;
                            *selectedEvent = -1;
                            removeTrack = true;
                        }
                    }

                    ImVec2 pos = ImVec2(contentMin.x + legendWidth, contentMin.y + ItemHeight * i + 1 + customHeight);
                    ImVec2 sz = ImVec2(canvas_size.x + canvas_pos.x, pos.y + ItemHeight - 1);
                    if (overLabel && !popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1)
                    {
                        SetCursor(LoadCursor(NULL, IDC_HAND));

                        if (io.MouseReleased[0])
                        {
                            *selectedTrack = i;
                            *selectedEvent = -1;
                            renameTrack = true;
                        }
                    }
                }

                if (sequenceOptions & EDITOR_EVENT_ADD)
                {
                    if (SequencerAddDelButton(draw_list, ImVec2(contentMin.x + legendWidth - ItemHeight + 2 - 10, tpos.y + 2), ImVec2(ItemHeight * 0.8f, ItemHeight * 0.8f), true) && !popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1)
                    {
                        SetCursor(LoadCursor(NULL, IDC_HAND));

                        if (io.MouseReleased[0])
                        {
                            addTrack = true;
                            *selectedTrack = i;
                        }
                    }

                    if (!popupOpened && !MovingCurrentFrame && !MovingScrollBar && movingTrack == -1)
                    {
                        for (size_t j = 0; j < eventTrackEditor->m_eventTracks[i].m_numEvents; j++)
                        {
                            if (GetAsyncKeyState(VK_DELETE) & 1)
                                delEvent = true;
                        }
                    }
                }
            }

            ImGui::PopStyleColor();
            if (removeTrack && !reload)
            {
                popupOpened = true;
                ImGui::OpenPopup("deleteTrack");
            }

            if (ImGui::BeginPopup("deleteTrack"))
            {
                std::string header = std::string(eventTrackEditor->m_eventTracks[*selectedTrack].m_name);

                ImGui::Text(header.c_str());
                ImGui::Separator();

                if (ImGui::Button("Delete Track") || GetAsyncKeyState(VK_RETURN) & 1)
                {
                    reload = true;

                    eventTrackEditor->DeleteTrack(*selectedTrack);
                    *selectedTrack = -1;
                    *selectedEvent = -1;

                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (renameTrack && !reload)
            {
                popupOpened = true;
                ImGui::OpenPopup("renameTrack");
            }

            if (ImGui::BeginPopup("renameTrack"))
            {
                std::string header = std::string(eventTrackEditor->m_eventTracks[*selectedTrack].m_name);

                ImGui::Text(header.c_str());
                ImGui::Separator();

                ImGui::InputText("Name", eventTrackEditor->m_eventTracks[*selectedTrack].m_name, 50);

                if (GetAsyncKeyState(VK_RETURN))
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }

            if (delEvent && !reload)
            {
                popupOpened = true;
                ImGui::OpenPopup("deleteEvent");
            }

            if (ImGui::BeginPopup("deleteEvent"))
            {
                std::string header = std::string(eventTrackEditor->m_eventTracks[*selectedTrack].m_name) + " [" + std::to_string(*selectedEvent) + "]";

                ImGui::Text(header.c_str());
                ImGui::Separator();

                if (ImGui::Button("Delete Event") || GetAsyncKeyState(VK_RETURN) & 1)
                {
                    eventTrackEditor->DeleteEvent(*selectedTrack, *selectedEvent);

                    *selectedTrack = -1;
                    *selectedEvent = -1;

                    ImGui::CloseCurrentPopup();

                    reload = true;
                }

                ImGui::EndPopup();
            }

            if (addTrack && !reload)
            {
                popupOpened = true;
                ImGui::OpenPopup("addEvent");
            }

            if (ImGui::BeginPopup("addEvent"))
            {
                ImGui::Text(eventTrackEditor->m_eventTracks[*selectedTrack].m_name);
                ImGui::Separator();

                ImGui::InputFloat("Start", &addEvent.m_start, 1.f / 60.f);

                if (eventTrackEditor->m_eventTracks[*selectedTrack].m_discrete == false)
                    ImGui::InputFloat("Duration", &addEvent.m_duration, 1.f / 60.f);
                else
                    addEvent.m_duration = 0.f;

                *currentFrame = MathHelper::TimeToFrame(addEvent.m_start);

                ImGui::InputInt("Value", &addEvent.m_value);

                if (ImGui::Button("Add Event") || GetAsyncKeyState(VK_RETURN) & 1)
                {
                    eventTrackEditor->AddEvent(*selectedTrack, EventTrackEditor::EventTrack::Event{ MathHelper::TimeToFrame(addEvent.m_start), MathHelper::TimeToFrame(addEvent.m_duration), addEvent.m_value});
                    ImGui::CloseCurrentPopup();

                    reload = true;
                }

                ImGui::EndPopup();
            }
            ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);

            if (!reload)
            {
                if (*currentFrame > 0 && !popupOpened)
                    addEvent.m_start = MathHelper::FrameToTime(*currentFrame);

                // clipping rect so items bars are not visible in the legend on the left when scrolled

                // slots background
                for (int i = 0; i < eventTrackEditor->GetTrackCount(); i++)
                {
                    unsigned int col = 0xFF313131;

                    ImVec2 pos = ImVec2(contentMin.x + legendWidth, contentMin.y + ItemHeight * i + 1 + customHeight);
                    ImVec2 sz = ImVec2(canvas_size.x + canvas_pos.x, pos.y + ItemHeight - 1);

                    draw_list->AddRectFilled(pos, sz, col, 0);

                    if (!popupOpened && cy >= pos.y && cy < pos.y + ItemHeight && movingTrack == -1 && cx>contentMin.x && cx < contentMin.x + canvas_size.x)
                    {
                        draw_list->AddRectFilled(pos, sz, 0x10FFFFFF, 0);
                    }
                }

                draw_list->PushClipRect(childFramePos + ImVec2(float(legendWidth), 0.f), childFramePos + childFrameSize, true);

                // vertical frame lines in content area
                for (int i = eventTrackEditor->GetFrameMin() + 1; i <= eventTrackEditor->GetFrameMax(); i += frameStep)
                {
                    drawLineContent(i, int(contentHeight));
                }
                drawLineContent(eventTrackEditor->GetFrameMin(), int(contentHeight));
                drawLineContent(eventTrackEditor->GetFrameMax(), int(contentHeight));

                for (int i = eventTrackEditor->GetFrameMax() + 1; i <= 500; i += frameStep)
                {
                    drawLineContent(i, ItemHeight);
                }

                draw_list->AddRectFilled(ImVec2(contentMin.x + legendWidth - firstFrameUsed * framePixelWidth + eventTrackEditor->GetFrameMax() * framePixelWidth, canvas_pos.y), canvas_pos + canvas_size, 0x40000000, 0);

                // tracks
                customHeight = 0;
                for (int trackIndex = 0; trackIndex < eventTrackEditor->GetTrackCount(); trackIndex++)
                {
                    unsigned int color;
                    unsigned int slotColor = TRACK_COLOR;
                    unsigned int slotColorHalf = slotColor | 0x40000000;
                    unsigned int boundColor = TRACK_BOUND;

                    EventTrackEditor::EventTrack* track = &eventTrackEditor->m_eventTracks[trackIndex];

                    bool isDiscrete = track->m_discrete;

                    for (int eventIdx = 0; eventIdx < track->m_numEvents; eventIdx++)
                    {
                        std::string event_value = eventTrackEditor->GetEventLabel(trackIndex, eventIdx);

                        if ((sequenceOptions & EDITOR_MARK_ACTIVE_EVENTS) && *currentFrame > -1)
                        {
                            if (!track->m_discrete)
                            {
                                if ((*currentFrame >= track->m_event[eventIdx].m_frameStart) && *currentFrame <= (track->m_event[eventIdx].m_duration + track->m_event[eventIdx].m_frameStart))
                                    slotColor = TRACK_COLOR_ACTIVE;
                            }
                            else
                            {
                                if (*currentFrame == track->m_event[eventIdx].m_frameStart)
                                    slotColor = TRACK_COLOR_ACTIVE;
                            }
                        }

                        ImVec2 pos = ImVec2(contentMin.x + legendWidth - firstFrameUsed * framePixelWidth, contentMin.y + ItemHeight * trackIndex + 1 + customHeight);
                        ImVec2 slotP1(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + 2);
                        ImVec2 slotP2(pos.x + (track->m_event[eventIdx].m_duration + track->m_event[eventIdx].m_frameStart) * framePixelWidth - 1, pos.y + ItemHeight - 2);
                        ImVec2 slotP3(pos.x + (track->m_event[eventIdx].m_duration + track->m_event[eventIdx].m_frameStart) * framePixelWidth - 1, pos.y + ItemHeight - 2);
                        ImVec2 slotP1Loop;
                        ImVec2 slotP2Loop;
                        ImVec2 slotP3Loop;
                        ImVec2 slotD1Loop;
                        ImVec2 slotD2Loop;
                        ImVec2 slotD3Loop;
                        ImVec2 slotT1Loop;
                        ImVec2 slotT2Loop;
                        ImVec2 slotT3Loop;

                        ImVec2 slotD1(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + 2);
                        ImVec2 slotD2(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + ItemHeight - 7);
                        ImVec2 slotD3(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + ItemHeight - 7);
                        ImVec2 slotT1 = ImVec2(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + ItemHeight - 7);
                        ImVec2 slotT2 = ImVec2(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + ItemHeight - 7);
                        ImVec2 slotT3 = ImVec2((slotT2.x + slotT1.x) / 2, (slotT2.y + slotT1.y) / 2 + 5);

                        ImVec2 frameMin = ImVec2(pos.x - 1, 0);
                        ImVec2 frameMax = ImVec2(frameMin.x + eventTrackEditor->GetFrameMax() * framePixelWidth, 0);

                        ImVec2 textSize = ImGui::CalcTextSize(event_value.c_str());
                        ImVec2 textSizeIdx = ImGui::CalcTextSize(std::to_string(eventIdx).c_str());
                        ImVec2 textP(slotP1.x + (slotP2.x - slotP1.x - textSize.x) / 2, slotP2.y + (slotP1.y - slotP2.y - textSize.y) / 2);
                        ImVec2 textD(slotD1.x + (slotD2.x - slotD1.x - textSize.x) / 2, slotD2.y + (slotD1.y - slotD2.y - textSize.y) / 2);
                        ImVec2 textDIdx(slotD1.x + framePixelWidth / 2 + textSize.x / 3, slotT3.y - textSizeIdx.y);
                        ImVec2 textPLoop;

                        if ((slotP1.x <= (canvas_size.x + contentMin.x) || slotP1.x >= (contentMin.x + legendWidth)) && (slotP2.x >= (contentMin.x + legendWidth) || slotP2.x <= (canvas_size.x + contentMin.x)))
                        {
                            if (isDiscrete)
                            {
                                slotD1.x -= framePixelWidth / 2;
                                slotD2.x += framePixelWidth / 2;

                                slotT1.x -= framePixelWidth / 2;
                                slotT2.x += framePixelWidth / 2;

                                draw_list->AddRectFilled(slotD1, slotD3, slotColorHalf, 0);
                                draw_list->AddRectFilled(slotD1, slotD2, slotColor, 0); //Track Box
                                draw_list->AddLine(slotD1, ImVec2(slotD2.x, slotD1.y), boundColor);
                                draw_list->AddLine(slotD2, ImVec2(slotD2.x, slotD1.y), boundColor);
                                draw_list->AddLine(slotD1, ImVec2(slotD1.x, slotD2.y), boundColor);

                                //draw_list->AddRect(slotD1, slotD2, boundColor, 0); //Track Bounding Box

                                draw_list->AddTriangleFilled(slotT1, slotT2, slotT3, slotColorHalf);
                                draw_list->AddTriangleFilled(slotT1, slotT2, slotT3, slotColor);
                                draw_list->AddLine(slotT1, slotT3, boundColor);
                                draw_list->AddLine(slotT2, slotT3, boundColor);

                                ImRect track_box(slotD1, slotD2);

                                draw_list->AddText(textD, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                                //draw_list->AddText(textDIdx, TRACK_TEXT_COLOR, std::to_string(eventIdx).c_str()); //Event Idx
                            }
                            else
                            {
                                draw_list->AddRectFilled(slotP1, slotP3, slotColorHalf, 0);
                                draw_list->AddRectFilled(slotP1, slotP2, slotColor, 0); //Track Box
                                draw_list->AddRect(slotP1, slotP2, boundColor, 0); //Track Bounding Box
                                draw_list->AddText(textP, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                            }

                            if (sequenceOptions & EDITOR_EVENT_LOOP)
                            {
                                if (slotP2.x > frameMax.x)
                                {
                                    if (slotP1.x < frameMax.x)
                                    {
                                        slotP1Loop = ImVec2(frameMin.x, slotP1.y);
                                        slotP2Loop = ImVec2(slotP1Loop.x + fmin(abs(slotP2.x - slotP1.x), abs(slotP2.x - frameMax.x)), slotP2.y);
                                        textPLoop = ImVec2(slotP1Loop.x + (slotP2Loop.x - slotP1Loop.x - textSize.x) / 2, slotP2Loop.y + (slotP1Loop.y - slotP2Loop.y - textSize.y) / 2);
                                    }
                                    else
                                    {
                                        slotP1Loop = ImVec2(frameMin.x + abs(slotP1.x - frameMax.x), slotP1.y);
                                        slotP2Loop = ImVec2(slotP1Loop.x + fmin(abs(slotP2.x - slotP1.x), abs(slotP2.x - frameMax.x)), slotP2.y);
                                        textPLoop = ImVec2(slotP1Loop.x + (slotP2Loop.x - slotP1Loop.x - textSize.x) / 2, slotP2Loop.y + (slotP1Loop.y - slotP2Loop.y - textSize.y) / 2);
                                    }

                                    draw_list->AddRectFilled(slotP1Loop, slotP2Loop, slotColor, 0); //Track Box
                                    draw_list->AddRect(slotP1Loop, slotP2Loop, TRACK_BOUND, 0); //Track Bounding Box
                                    draw_list->AddText(textPLoop, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                                }
                                else if (slotP1.x < frameMin.x)
                                {
                                    if (slotP2.x > frameMin.x)
                                    {
                                        slotP2Loop = ImVec2(frameMax.x, slotP2.y);
                                        slotP1Loop = ImVec2(slotP2Loop.x - fmin(abs(slotP2.x - slotP1.x), abs(slotP1.x - frameMin.x)), slotP1.y);
                                        textPLoop = ImVec2(slotP1Loop.x + (slotP2Loop.x - slotP1Loop.x - textSize.x) / 2, slotP2Loop.y + (slotP1Loop.y - slotP2Loop.y - textSize.y) / 2);
                                    }
                                    else
                                    {
                                        slotP2Loop = ImVec2(frameMax.x - abs(slotP2.x - frameMin.x), slotP2.y);
                                        slotP1Loop = ImVec2(slotP2Loop.x - fmin(abs(slotP2.x - slotP1.x), abs(slotP1.x - frameMin.x)), slotP1.y);
                                        textPLoop = ImVec2(slotP1Loop.x + (slotP2Loop.x - slotP1Loop.x - textSize.x) / 2, slotP2Loop.y + (slotP1Loop.y - slotP2Loop.y - textSize.y) / 2);
                                    }

                                    draw_list->AddRectFilled(slotP1Loop, slotP2Loop, slotColor, 0); //Track Box
                                    draw_list->AddRect(slotP1Loop, slotP2Loop, TRACK_BOUND, 0); //Track Bounding Box
                                    draw_list->AddText(textPLoop, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                                }
                                else
                                {
                                    slotP1Loop = ImVec2(0, 0);
                                    slotP2Loop = ImVec2(0, 0);
                                    textPLoop = ImVec2(0, 0);
                                }
                            }
                        }

                        //Drag
                        {
                            ImRect rects[3] = { ImRect(ImVec2(slotP1.x - framePixelWidth / 3, slotP1.y), ImVec2(slotP1.x, slotP2.y))
                                , ImRect(ImVec2(slotP2.x, slotP1.y), ImVec2(slotP2.x + framePixelWidth / 3, slotP2.y))
                                , ImRect(slotP1, slotP2) };

                            ImRect rect_discrete = ImRect(slotD1, slotD2);

                            ImRect rects_loop[3] = { ImRect(ImVec2(slotP1Loop.x - framePixelWidth / 3, slotP1Loop.y), ImVec2(slotP1Loop.x, slotP2Loop.y))
                                , ImRect(ImVec2(slotP2Loop.x, slotP1Loop.y), ImVec2(slotP2Loop.x + framePixelWidth / 3, slotP2Loop.y))
                                , ImRect(slotP1Loop, slotP2Loop) };

                            //rect[1] = start drag
                            //rect[2] = end drag
                            //rect[3] = event drag

                            if (slotP1.x > slotP2.x)
                                rects[2] = ImRect(ImVec2(slotP2.x, slotP1.y), ImVec2(slotP1.x, slotP2.y));

                            const unsigned int quadColor[] = { 0x20FFFFFF, 0x20FFFFFF, 0x20FFFFFF };

                            //Tracks
                            if (movingTrack == -1 && (sequenceOptions & EDITOR_EVENT_EDIT_STARTEND))// TODOFOCUS && backgroundRect.Contains(io.MousePos))
                            {
                                if (!isDiscrete)
                                {
                                    for (int j = 0; j < 3; j++)
                                    {
                                        ImRect& rc = rects[j];
                                        if (!rc.Contains(io.MousePos) && !popupOpened)
                                            continue;
                                        if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos))
                                            continue;

                                        if (j == 2)
                                            SetCursor(LoadCursor(NULL, IDC_HAND));
                                        else
                                            SetCursor(LoadCursor(NULL, IDC_SIZEWE));

                                        if (ImGui::IsMouseClicked(0) && !popupOpened && !MovingScrollBar && !MovingCurrentFrame)
                                        {
                                            movingTrack = trackIndex;
                                            movingEvent = eventIdx;
                                            movingPos = cx;
                                            movingPart = j + 1;

                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    ImRect& rc = rect_discrete;
                                    if (!rc.Contains(io.MousePos) && !popupOpened)
                                        continue;

                                    SetCursor(LoadCursor(NULL, IDC_HAND));                                

                                    if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos))
                                        continue;

                                    if (ImGui::IsMouseClicked(0) && !popupOpened && !MovingScrollBar && !MovingCurrentFrame)
                                    {
                                        movingTrack = trackIndex;
                                        movingEvent = eventIdx;
                                        movingPos = cx;
                                        movingPart = 3;

                                        break;
                                    }
                                }
                            }

                            //Looped entries
                            if (sequenceOptions & EDITOR_EVENT_LOOP)
                            {
                                if (movingTrack == -1 && (sequenceOptions & EDITOR_EVENT_EDIT_STARTEND))// TODOFOCUS && backgroundRect.Contains(io.MousePos))
                                {
                                    for (int j = 2; j >= 0; j--)
                                    {
                                        if (j == 2)
                                        {
                                            ImRect& rc = rects_loop[j];
                                            if (!rc.Contains(io.MousePos) && !popupOpened)
                                                continue;
                                            draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[j], 0);
                                        }
                                        else if (!isDiscrete)
                                        {
                                            ImRect& rc = rects_loop[j];
                                            if (!rc.Contains(io.MousePos) && !popupOpened)
                                                continue;
                                            draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[j], 0);
                                        }
                                    }

                                    for (int j = 0; j < 3; j++)
                                    {
                                        ImRect& rc = rects_loop[j];
                                        if (!rc.Contains(io.MousePos) && !popupOpened)
                                            continue;
                                        if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos) && !popupOpened)
                                            continue;

                                        if (j == 2)
                                        {
                                            if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                            {
                                                movingTrack = trackIndex;
                                                movingEvent = eventIdx;
                                                movingPos = cx;
                                                movingPart = j + 1;

                                                break;
                                            }
                                        }
                                        else if (!isDiscrete)
                                        {
                                            if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                            {
                                                movingTrack = trackIndex;
                                                movingEvent = eventIdx;
                                                movingPos = cx;
                                                movingPart = j + 1;

                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // moving
                if (!popupOpened)
                {
                    if (movingTrack >= 0 && movingEvent >= 0)
                    {
                        ImGui::CaptureMouseFromApp();
                        int diffFrame = int((cx - movingPos) / framePixelWidth);

                        if (std::abs(diffFrame) > 0)
                        {
                            if (selectedTrack)
                                *selectedTrack = movingTrack;

                            if (selectedEvent)
                                *selectedEvent = movingEvent;

                            EventTrackEditor::EventTrack* track = &eventTrackEditor->m_eventTracks[movingTrack];

                            if (movingPart == MovingPart_End)
                            {
                                track->m_event[movingEvent].m_duration += diffFrame;

                                movingPos += int(diffFrame * framePixelWidth);
                            }
                            else if (track->m_event[movingEvent].m_frameStart + diffFrame >= 0 && (track->m_event[movingEvent].m_frameStart + track->m_event[movingEvent].m_duration) + diffFrame <= 2 * eventTrackEditor->GetFrameMax())
                            {
                                if (movingPart == MovingPart_Start)
                                {
                                    track->m_event[movingEvent].m_frameStart += diffFrame;
                                    track->m_event[movingEvent].m_duration -= diffFrame;
                                }
                                else if (movingPart == MovingPart_All)
                                    track->m_event[movingEvent].m_frameStart += diffFrame;

                                movingPos += int(diffFrame * framePixelWidth);
                            }
                            else
                            {
                                if (track->m_event[movingEvent].m_frameStart < 0)
                                    track->m_event[movingEvent].m_frameStart = 0;

                                if ((track->m_event[movingEvent].m_frameStart + track->m_event[movingEvent].m_duration) > 2 * eventTrackEditor->GetFrameMax())
                                    track->m_event[movingEvent].m_frameStart = (2 * eventTrackEditor->GetFrameMax() - track->m_event[movingEvent].m_duration);
                            }

                        }
                        if (!io.MouseDown[0] && !popupOpened)
                        {
                            // single select
                            if (!diffFrame && movingPart && selectedTrack && selectedEvent)
                            {
                                *selectedTrack = movingTrack;
                                *selectedEvent = movingEvent;
                                ret = true;
                            }

                            movingTrack = -1;
                            movingEvent = -1;
                        }
                    }
                }

                // cursor
                if (currentFrame && firstFrame && *currentFrame >= *firstFrame && *currentFrame <= eventTrackEditor->GetFrameMax())
                {
                    static const float cursorWidth = 1.f;

                    float cursorOffset = contentMin.x + legendWidth + (*currentFrame - firstFrameUsed) * framePixelWidth - cursorWidth * 0.5f;
                    draw_list->AddLine(ImVec2(cursorOffset, canvas_pos.y), ImVec2(cursorOffset, contentMax.y), 0xFF0000FF, cursorWidth);

                    char tmps[512];
                    ImFormatString(tmps, IM_ARRAYSIZE(tmps), "%d", *currentFrame);
                    draw_list->AddText(ImVec2(cursorOffset + 10, canvas_pos.y + 2), 0xFF2A2AFF, tmps);
                }

                draw_list->PopClipRect();
                draw_list->PopClipRect();

                // copy paste
                if (sequenceOptions & EDITOR_COPYPASTE)
                {
                    ImRect rectCopy(ImVec2(contentMin.x + 100, canvas_pos.y + 2)
                        , ImVec2(contentMin.x + 100 + 30, canvas_pos.y + ItemHeight - 2));
                    bool inRectCopy = rectCopy.Contains(io.MousePos);
                    unsigned int copyColor = inRectCopy ? 0xFF1080FF : 0xFF000000;
                    draw_list->AddText(rectCopy.Min, copyColor, "Copy");

                    ImRect rectPaste(ImVec2(contentMin.x + 140, canvas_pos.y + 2)
                        , ImVec2(contentMin.x + 140 + 30, canvas_pos.y + ItemHeight - 2));
                    bool inRectPaste = rectPaste.Contains(io.MousePos);
                    unsigned int pasteColor = inRectPaste ? 0xFF1080FF : 0xFF000000;
                    draw_list->AddText(rectPaste.Min, pasteColor, "Paste");

                    if (inRectCopy && io.MouseReleased[0] && !popupOpened)
                    {
                        //eventTrackEditor->Copy();
                    }
                    if (inRectPaste && io.MouseReleased[0] && !popupOpened)
                    {
                        //eventTrackEditor->Paste();
                    }
                }
                //
            }

            ImGui::EndChildFrame();
            ImGui::PopStyleColor();
            if (hasScrollBar)
            {
                ImGui::InvisibleButton("scrollBar", scrollBarSize);
                ImVec2 scrollBarMin = ImGui::GetItemRectMin();
                ImVec2 scrollBarMax = ImGui::GetItemRectMax();

                // ratio = number of frames visible in control / number to total frames

                float startFrameOffset = ((float)(firstFrameUsed - eventTrackEditor->GetFrameMin()) / (float)frameCount) * (canvas_size.x - legendWidth);
                ImVec2 scrollBarA(scrollBarMin.x + legendWidth, scrollBarMin.y - 2);
                ImVec2 scrollBarB(scrollBarMin.x + canvas_size.x, scrollBarMax.y - 1);
                draw_list->AddRectFilled(scrollBarA, scrollBarB, 0xFF222222, 0);

                ImRect scrollBarRect(scrollBarA, scrollBarB);
                bool inScrollBar = scrollBarRect.Contains(io.MousePos);

                draw_list->AddRectFilled(scrollBarA, scrollBarB, 0xFF101010, 8);


                ImVec2 scrollBarC(scrollBarMin.x + legendWidth + startFrameOffset, scrollBarMin.y);
                ImVec2 scrollBarD(scrollBarMin.x + legendWidth + barWidthInPixels + startFrameOffset, scrollBarMax.y - 2);
                draw_list->AddRectFilled(scrollBarC, scrollBarD, (inScrollBar || MovingScrollBar) ? 0xFF606060 : 0xFF505050, 6);

                ImRect barHandleLeft(scrollBarC, ImVec2(scrollBarC.x + 14, scrollBarD.y));
                ImRect barHandleRight(ImVec2(scrollBarD.x - 14, scrollBarC.y), scrollBarD);

                bool onLeft = barHandleLeft.Contains(io.MousePos);
                bool onRight = barHandleRight.Contains(io.MousePos);

                static bool sizingRBar = false;
                static bool sizingLBar = false;

                draw_list->AddRectFilled(barHandleLeft.Min, barHandleLeft.Max, (onLeft || sizingLBar) ? 0xFFAAAAAA : 0xFF666666, 6);
                draw_list->AddRectFilled(barHandleRight.Min, barHandleRight.Max, (onRight || sizingRBar) ? 0xFFAAAAAA : 0xFF666666, 6);

                ImRect scrollBarThumb(scrollBarC, scrollBarD);
                static const float MinBarWidth = 44.f;
                if (sizingRBar)
                {
                    if (!io.MouseDown[0] && !popupOpened)
                    {
                        sizingRBar = false;
                    }
                    else
                    {
                        float barNewWidth = ImMax(barWidthInPixels + io.MouseDelta.x, MinBarWidth);
                        float barRatio = barNewWidth / barWidthInPixels;
                        framePixelWidthTarget = framePixelWidth = framePixelWidth / barRatio;
                        int newVisibleFrameCount = int((canvas_size.x - legendWidth) / framePixelWidthTarget);
                        int lastFrame = *firstFrame + newVisibleFrameCount;
                        if (lastFrame > eventTrackEditor->GetFrameMax())
                        {
                            framePixelWidthTarget = framePixelWidth = (canvas_size.x - legendWidth) / float(eventTrackEditor->GetFrameMax() - *firstFrame);
                        }
                    }
                }
                else if (sizingLBar)
                {
                    if (!io.MouseDown[0] && !popupOpened)
                    {
                        sizingLBar = false;
                    }
                    else
                    {
                        if (fabsf(io.MouseDelta.x) > FLT_EPSILON)
                        {
                            float barNewWidth = ImMax(barWidthInPixels - io.MouseDelta.x, MinBarWidth);
                            float barRatio = barNewWidth / barWidthInPixels;
                            float previousFramePixelWidthTarget = framePixelWidthTarget;
                            framePixelWidthTarget = framePixelWidth = framePixelWidth / barRatio;
                            int newVisibleFrameCount = int(visibleFrameCount / barRatio);
                            int newFirstFrame = *firstFrame + newVisibleFrameCount - visibleFrameCount;
                            newFirstFrame = ImClamp(newFirstFrame, eventTrackEditor->GetFrameMin(), ImMax(eventTrackEditor->GetFrameMax() - visibleFrameCount, eventTrackEditor->GetFrameMin()));
                            if (newFirstFrame == *firstFrame)
                            {
                                framePixelWidth = framePixelWidthTarget = previousFramePixelWidthTarget;
                            }
                            else
                            {
                                *firstFrame = newFirstFrame;
                            }
                        }
                    }
                }
                else
                {
                    if (MovingScrollBar)
                    {
                        if (!io.MouseDown[0] && !popupOpened)
                        {
                            MovingScrollBar = false;
                        }
                        else
                        {
                            float framesPerPixelInBar = barWidthInPixels / (float)visibleFrameCount;
                            *firstFrame = int((io.MousePos.x - panningViewSource.x) / framesPerPixelInBar) - panningViewFrame;
                            *firstFrame = ImClamp(*firstFrame, eventTrackEditor->GetFrameMin(), ImMax(eventTrackEditor->GetFrameMax() - visibleFrameCount, eventTrackEditor->GetFrameMin()));
                        }
                    }
                    else
                    {
                        if (scrollBarThumb.Contains(io.MousePos) && ImGui::IsMouseClicked(0) && firstFrame && !MovingCurrentFrame && movingTrack == -1)
                        {
                            MovingScrollBar = true;
                            panningViewSource = io.MousePos;
                            panningViewFrame = -*firstFrame;
                        }
                        if (!sizingRBar && onRight && ImGui::IsMouseClicked(0))
                            sizingRBar = true;
                        if (!sizingLBar && onLeft && ImGui::IsMouseClicked(0))
                            sizingLBar = true;

                    }
                }
            }

            if (!popupOpened)
            {
                if (regionRect.Contains(io.MousePos))
                {
                    bool overCustomDraw = false;
                    for (auto& custom : customDraws)
                    {
                        overCustomDraw = true;
                        if (custom.customRect.Contains(io.MousePos))
                        {
                            overCustomDraw = true;
                        }
                    }


                    if (overCustomDraw)
                    {
                    }
                    else
                    {
                        int frameOverCursor = (int)((io.MousePos.x - topRect.Min.x) / framePixelWidth) + firstFrameUsed;

                        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
                        {
                            if (io.MouseWheel < -FLT_EPSILON)
                            {
                                framePixelWidthTarget *= 0.9f;
                                framePixelWidth *= 0.9f;
                                int newFrameOverCursor = (int)((io.MousePos.x - topRect.Min.x) / framePixelWidth) + firstFrameUsed;
                                *firstFrame += frameOverCursor - newFrameOverCursor;
                            }

                            if (io.MouseWheel > FLT_EPSILON)
                            {
                                framePixelWidthTarget *= 1.1f;
                                framePixelWidth *= 1.1f;
                                int newFrameOverCursor = (int)((io.MousePos.x - topRect.Min.x) / framePixelWidth) + firstFrameUsed;
                                *firstFrame += frameOverCursor - newFrameOverCursor;
                            }
                        }
                    }
                }
            }
        }

        ImGui::EndGroup();

        if (expanded)
        {
            if (sequenceOptions & EDITOR_COLLAPSE)
            {
                bool overExpanded = SequencerAddDelButton(draw_list, ImVec2(canvas_pos.x + 2, canvas_pos.y + 2), ImVec2(4, ItemHeight), !*expanded);
                if (overExpanded && io.MouseReleased[0] && !popupOpened)
                    *expanded = !*expanded;
            }
        }

        if (!ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel))
            popupOpened = false;

        return ret;
    }
}
