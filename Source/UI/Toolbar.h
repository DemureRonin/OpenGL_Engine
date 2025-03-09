#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Toolbar
{
public:
    static const float toolBarHeight;

    static void Render()
    {
      
        if (ImGui::BeginMainMenuBar())  // Creates the top bar
        {
            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Inspector"))
                {
                    
                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
        
    }
};
