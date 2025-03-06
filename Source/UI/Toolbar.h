#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Toolbar
{
public:
    static void Render()
    {
        if (ImGui::BeginMainMenuBar())  // Creates the top bar
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New")) { /* Handle new file action */ }
                if (ImGui::MenuItem("Open")) { /* Handle open file action */ }
                if (ImGui::MenuItem("Save")) { /* Handle save action */ }
                if (ImGui::MenuItem("Exit")) { /* Handle exit action */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo")) { /* Handle undo */ }
                if (ImGui::MenuItem("Redo")) { /* Handle redo */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Cut")) { /* Handle cut */ }
                if (ImGui::MenuItem("Copy")) { /* Handle copy */ }
                if (ImGui::MenuItem("Paste")) { /* Handle paste */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Brush")) { /* Activate brush tool */ }
                if (ImGui::MenuItem("Eraser")) { /* Activate eraser tool */ }
                if (ImGui::MenuItem("Fill")) { /* Activate fill tool */ }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
};
