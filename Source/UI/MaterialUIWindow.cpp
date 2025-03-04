#include "MaterialUIWindow.h"

void MaterialUIWindow::Render(Material& material)
{
    int offset = 300; 
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - offset, 600), ImGuiCond_Always); 
    ImGui::SetNextWindowSize(ImVec2(offset, 160), ImGuiCond_Always); 

    ImGui::Begin("Material", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Tint:");
    ImGui::ColorEdit4("##color", &material.tint.x);
    ImGui::Spacing();
    ImGui::Text("Shininess:");
    ImGui::DragFloat("##Shininess", &material.shininess, 0.01f, 0, 1); 

    ImGui::End();
}
