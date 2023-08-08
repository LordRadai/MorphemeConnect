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
#define TRACK_TEXT_COLOR 0xFFE3E3E1

namespace ImSequencer
{
#ifndef IMGUI_DEFINE_MATH_OPERATORS
    static ImVec2 operator+(const ImVec2& a, const ImVec2& b) {
        return ImVec2(a.x + b.x, a.y + b.y);
    }
#endif
    static bool SequencerAddDelButton(ImDrawList* draw_list, ImVec2 pos, bool add = true)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImRect delRect(pos, ImVec2(pos.x + 16, pos.y + 16));
        bool overDel = delRect.Contains(io.MousePos);
        int delColor = overDel ? 0xFFAAAAAA : 0x50000000;
        float midy = pos.y + 16 / 2 - 0.5f;
        float midx = pos.x + 16 / 2 - 0.5f;
        draw_list->AddRect(delRect.Min, delRect.Max, delColor, 4);
        draw_list->AddLine(ImVec2(delRect.Min.x + 3, midy), ImVec2(delRect.Max.x - 3, midy), delColor, 2);
        if (add)
            draw_list->AddLine(ImVec2(midx, delRect.Min.y + 3), ImVec2(midx, delRect.Max.y - 3), delColor, 2);
        return overDel;
    }

    bool Sequencer(EventTrackEditor* eventTrackEditor, int* currentFrame, int* selectedTrack, int* selectedEvent, bool* expanded, int* firstFrame, int sequenceOptions)
    {
        bool ret = false;
        ImGuiIO& io = ImGui::GetIO();
        int cx = (int)(io.MousePos.x);
        int cy = (int)(io.MousePos.y);
        static float framePixelWidth = 9.f;
        static float framePixelWidthTarget = 9.f;

        int legendWidth = 210;

        static int movingTrack = -1;
        static int movingEvent = -1;
        static int movingPos = -1;
        static int movingPart = -1;
        int delEntry = -1;
        int dupEntry = -1;
        int ItemHeight = 20;

        bool popupOpened = false;
        int sequenceCount = eventTrackEditor->GetTrackCount();
        if (!sequenceCount)
            return false;
        ImGui::BeginGroup();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
         
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
        ImVec2 canvas_size = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);        // Resize canvas to what's available

        int firstFrameUsed = firstFrame ? *firstFrame : 0;

        int controlHeight = sequenceCount * ItemHeight;

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
            ImFormatString(tmps, IM_ARRAYSIZE(tmps), "%d Frames / %d tracks", frameCount, sequenceCount);
            draw_list->AddText(ImVec2(canvas_pos.x + 26, canvas_pos.y + 2), 0xFFFFFFFF, tmps);
        }
        else
        {
            bool hasScrollBar(true);
            /*
            int framesPixelWidth = int(frameCount * framePixelWidth);
            if ((framesPixelWidth + legendWidth) >= canvas_size.x)
            {
                hasScrollBar = true;
            }
            */
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

            if (!MovingCurrentFrame && !MovingScrollBar && movingTrack == -1 && sequenceOptions & SEQUENCER_CHANGE_FRAME && currentFrame && *currentFrame >= 0 && topRect.Contains(io.MousePos) && io.MouseDown[0])
            {
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

            //header
            draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_size.x + canvas_pos.x, canvas_pos.y + ItemHeight), 0xFF383838, 0);
            if (sequenceOptions & SEQUENCER_ADD)
            {
                if (SequencerAddDelButton(draw_list, ImVec2(canvas_pos.x + legendWidth - ItemHeight, canvas_pos.y + 2), true) && io.MouseReleased[0])
                    ImGui::OpenPopup("addEntry");

                if (ImGui::BeginPopup("addEntry"))
                {
                    ImGui::EndPopup();
                    popupOpened = true;
                }
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
            /*
            draw_list->AddLine(canvas_pos, ImVec2(canvas_pos.x, canvas_pos.y + controlHeight), 0xFF000000, 1);
            draw_list->AddLine(ImVec2(canvas_pos.x, canvas_pos.y + ItemHeight), ImVec2(canvas_size.x, canvas_pos.y + ItemHeight), 0xFF000000, 1);
            */

            // clip content

            draw_list->PushClipRect(childFramePos, childFramePos + childFrameSize, true);

            // draw item names in the legend rect on the left
            size_t customHeight = 0;
            for (int i = 0; i < sequenceCount; i++)
            {
                ImVec2 tpos(contentMin.x + 3, contentMin.y + i * ItemHeight + 2 + customHeight);
                draw_list->AddText(tpos, 0xFFFFFFFF, eventTrackEditor->GetTrackName(i));

                if (sequenceOptions & SEQUENCER_DEL)
                {
                    bool overDel = SequencerAddDelButton(draw_list, ImVec2(contentMin.x + legendWidth - ItemHeight + 2 - 10, tpos.y + 2), false);
                    if (overDel && io.MouseReleased[0])
                        delEntry = i;

                    bool overDup = SequencerAddDelButton(draw_list, ImVec2(contentMin.x + legendWidth - ItemHeight - ItemHeight + 2 - 10, tpos.y + 2), true);
                    if (overDup && io.MouseReleased[0])
                        dupEntry = i;
                }
            }

            // clipping rect so items bars are not visible in the legend on the left when scrolled
            //

            // slots background
            for (int i = 0; i < sequenceCount; i++)
            {
                unsigned int col = (i & 1) ? 0xFF313131 : 0xFF282828;

                ImVec2 pos = ImVec2(contentMin.x + legendWidth, contentMin.y + ItemHeight * i + 1 + customHeight);
                ImVec2 sz = ImVec2(canvas_size.x + canvas_pos.x, pos.y + ItemHeight - 1);
                if (!popupOpened && cy >= pos.y && cy < pos.y + ItemHeight && movingTrack == -1 && cx>contentMin.x && cx < contentMin.x + canvas_size.x)
                {
                    col += 0x80201008;
                    pos.x -= legendWidth;
                }
                draw_list->AddRectFilled(pos, sz, col, 0);
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
            for (int i = 0; i < sequenceCount; i++)
            {
                unsigned int color;
                unsigned int slotColor = TRACK_COLOR;
                unsigned int slotColorHalf = slotColor | 0x40000000;
                unsigned int boundColor = TRACK_BOUND;

                EventTrackEditor::EventTrack* track = &eventTrackEditor->m_eventTracks[i];

                bool isDiscrete = track->m_discrete;

                for (int eventIdx = 0; eventIdx < track->m_numEvents; eventIdx++)
                {
                    std::string event_value = eventTrackEditor->GetEventLabel(i, eventIdx);

                    if (*currentFrame >= track->m_event[eventIdx].m_frameStart && *currentFrame <= track->m_event[eventIdx].m_frameEnd)
                        slotColor = TRACK_COLOR_ACTIVE;

                    ImVec2 pos = ImVec2(contentMin.x + legendWidth - firstFrameUsed * framePixelWidth, contentMin.y + ItemHeight * i + 1 + customHeight);
                    ImVec2 slotP1(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + 2);
                    ImVec2 slotP2(pos.x + track->m_event[eventIdx].m_frameEnd * framePixelWidth - 1, pos.y + ItemHeight - 2);
                    ImVec2 slotP3(pos.x + track->m_event[eventIdx].m_frameEnd * framePixelWidth - 1, pos.y + ItemHeight - 2);
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
                    ImVec2 slotD2(pos.x + track->m_event[eventIdx].m_frameEnd * framePixelWidth - 1, pos.y + ItemHeight - 7);
                    ImVec2 slotD3(pos.x + track->m_event[eventIdx].m_frameEnd * framePixelWidth - 1, pos.y + ItemHeight - 7);
                    ImVec2 slotT1 = ImVec2(pos.x + track->m_event[eventIdx].m_frameStart * framePixelWidth - 1, pos.y + ItemHeight - 7);
                    ImVec2 slotT2 = ImVec2(pos.x + track->m_event[eventIdx].m_frameEnd * framePixelWidth - 1, pos.y + ItemHeight - 7);
                    ImVec2 slotT3 = ImVec2((slotT2.x + slotT1.x) / 2, (slotT2.y + slotT1.y) / 2 + 5);

                    ImVec2 frameMin = ImVec2(pos.x - 1, 0);
                    ImVec2 frameMax = ImVec2(frameMin.x + eventTrackEditor->GetFrameMax() * framePixelWidth, 0);

                    ImVec2 textSize = ImGui::CalcTextSize(event_value.c_str());
                    ImVec2 textP(slotP1.x + (slotP2.x - slotP1.x - textSize.x) / 2, slotP2.y + (slotP1.y - slotP2.y - textSize.y) / 2);
                    ImVec2 textD(slotD1.x + (slotD2.x - slotD1.x - textSize.x) / 2, slotD2.y + (slotD1.y - slotD2.y - textSize.y) / 2);
                    ImVec2 textPLoop;

                    if (track->m_event[eventIdx].m_frameStart == track->m_event[eventIdx].m_frameEnd)
                    {
                        slotP1.x -= framePixelWidth / 2;
                        slotP2.x += framePixelWidth / 2;

                        slotD1.x -= framePixelWidth / 2;
                        slotD2.x += framePixelWidth / 2;

                        slotT1.x -= framePixelWidth / 2;
                        slotT2.x += framePixelWidth / 2;
                    }

                    if ((slotP1.x <= (canvas_size.x + contentMin.x) || slotP1.x >= (contentMin.x + legendWidth)) && (slotP2.x >= (contentMin.x + legendWidth) || slotP2.x <= (canvas_size.x + contentMin.x)))
                    {
                        if (isDiscrete)
                        {
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

                            draw_list->AddText(textD, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                        }
                        else
                        {
                            draw_list->AddRectFilled(slotP1, slotP3, slotColorHalf, 0);
                            draw_list->AddRectFilled(slotP1, slotP2, slotColor, 0); //Track Box
                            draw_list->AddRect(slotP1, slotP2, boundColor, 0); //Track Bounding Box
                            draw_list->AddText(textP, TRACK_TEXT_COLOR, event_value.c_str()); //Event Value
                        }

                        if (sequenceOptions & SEQUENCER_LOOP_EVENTS)
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
                        if (movingTrack == -1 && (sequenceOptions & SEQUENCER_EDIT_STARTEND))// TODOFOCUS && backgroundRect.Contains(io.MousePos))
                        {
                            if (!isDiscrete)
                            {
                                for (int j = 2; j >= 0; j--)
                                {
                                    ImRect& rc = rects[j];
                                    if (!rc.Contains(io.MousePos))
                                        continue;
                                    draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[j], 0);
                                }

                                for (int j = 0; j < 3; j++)
                                {
                                    ImRect& rc = rects[j];
                                    if (!rc.Contains(io.MousePos))
                                        continue;
                                    if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos))
                                        continue;

                                    if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                    {
                                        movingTrack = i;
                                        movingEvent = eventIdx;
                                        movingPos = cx;
                                        movingPart = j + 1;

                                        eventTrackEditor->BeginEdit(movingTrack);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                ImRect& rc = rect_discrete;
                                if (!rc.Contains(io.MousePos))
                                    continue;

                                draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[2], 0);
                                draw_list->AddTriangleFilled(slotT1, slotT2, slotT3, quadColor[2]);

                                if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos))
                                    continue;

                                if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                {
                                    movingTrack = i;
                                    movingEvent = eventIdx;
                                    movingPos = cx;
                                    movingPart = 3;

                                    eventTrackEditor->BeginEdit(movingTrack);
                                    break;
                                }
                            }
                        }

                        //Looped entries
                        if (sequenceOptions & SEQUENCER_LOOP_EVENTS)
                        {
                            if (movingTrack == -1 && (sequenceOptions & SEQUENCER_EDIT_STARTEND))// TODOFOCUS && backgroundRect.Contains(io.MousePos))
                            {
                                for (int j = 2; j >= 0; j--)
                                {
                                    if (j == 2)
                                    {
                                        ImRect& rc = rects_loop[j];
                                        if (!rc.Contains(io.MousePos))
                                            continue;
                                        draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[j], 0);
                                    }
                                    else if (!isDiscrete)
                                    {
                                        ImRect& rc = rects_loop[j];
                                        if (!rc.Contains(io.MousePos))
                                            continue;
                                        draw_list->AddRectFilled(rc.Min, rc.Max, quadColor[j], 0);
                                    }
                                }

                                for (int j = 0; j < 3; j++)
                                {
                                    ImRect& rc = rects_loop[j];
                                    if (!rc.Contains(io.MousePos))
                                        continue;
                                    if (!ImRect(childFramePos, childFramePos + childFrameSize).Contains(io.MousePos))
                                        continue;

                                    if (j == 2)
                                    {
                                        if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                        {
                                            movingTrack = i;
                                            movingEvent = eventIdx;
                                            movingPos = cx;
                                            movingPart = j + 1;

                                            eventTrackEditor->BeginEdit(movingTrack);
                                            break;
                                        }
                                    }
                                    else if (!isDiscrete)
                                    {
                                        if (ImGui::IsMouseClicked(0) && !MovingScrollBar && !MovingCurrentFrame)
                                        {
                                            movingTrack = i;
                                            movingEvent = eventIdx;
                                            movingPos = cx;
                                            movingPart = j + 1;

                                            eventTrackEditor->BeginEdit(movingTrack);
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

                    int& l = track->m_event[movingEvent].m_frameStart;
                    int& r = track->m_event[movingEvent].m_frameEnd;

                    if (l + diffFrame >= -eventTrackEditor->GetFrameMax() && r + diffFrame <= 2 * eventTrackEditor->GetFrameMax())
                    {
                        if (movingPart & 1)
                            l += diffFrame;

                        if (movingPart & 2)
                            r += diffFrame;

                        movingPos += int(diffFrame * framePixelWidth);
                    }
                    else
                    {
                        if (l < -eventTrackEditor->GetFrameMax())
                            l = -eventTrackEditor->GetFrameMax();

                        if (r > 2 * eventTrackEditor->GetFrameMax())
                            r = 2 * eventTrackEditor->GetFrameMax();
                    }
                    
                }
                if (!io.MouseDown[0])
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
                    eventTrackEditor->EndEdit();
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
            if (sequenceOptions & SEQUENCER_COPYPASTE)
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

                if (inRectCopy && io.MouseReleased[0])
                {
                    //eventTrackEditor->Copy();
                }
                if (inRectPaste && io.MouseReleased[0])
                {
                    //eventTrackEditor->Paste();
                }
            }
            //

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
                    if (!io.MouseDown[0])
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
                    if (!io.MouseDown[0])
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
                        if (!io.MouseDown[0])
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

        ImGui::EndGroup();

        if (expanded)
        {
            bool overExpanded = SequencerAddDelButton(draw_list, ImVec2(canvas_pos.x + 2, canvas_pos.y + 2), !*expanded);
            if (overExpanded && io.MouseReleased[0])
                *expanded = !*expanded;
        }

        if (delEntry != -1)
        {
            eventTrackEditor->DelTrack(delEntry);
            if (selectedTrack && (*selectedTrack == delEntry || *selectedTrack >= eventTrackEditor->GetTrackCount()))
                *selectedTrack = -1;
        }

        if (dupEntry != -1)
        {
            eventTrackEditor->DuplicateTrack(dupEntry);
        }
        return ret;
    }
}
