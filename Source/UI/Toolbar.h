#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Toolbar
{
public:
    static float toolBarHeight;

    static void Render()
    {
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.0f; // Fully transparent windows
        ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg].w = 0.0f; // Transparent menu bar

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // Fully transparent
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);  
        if (ImGui::BeginMainMenuBar())  // Creates the top bar
        {
            toolBarHeight = ImGui::GetWindowSize().y;

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Inspector"))
                {
                    
                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
};
