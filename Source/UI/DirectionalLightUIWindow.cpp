#include "DirectionalLightUIWindow.h"

#include "DirectionalLightUIWindow.h"

void DirectionalLightUIWindow::Render(DirectionalLight& directionalLight)
{
    int offset = 250;
    ImGui::SetNextWindowPos(ImVec2(10, 120), ImGuiCond_Always); 
    ImGui::SetNextWindowSize(ImVec2(offset, 160), ImGuiCond_Always);

    ImGui::Begin("Directional Light", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::PushItemWidth(50);

    ImGui::Text("Direction:");
    ImGui::Text("X"); ImGui::SameLine(); ImGui::DragFloat("##DirectionX", &directionalLight.direction.x, 0.1f); ImGui::SameLine();
    ImGui::Text("Y"); ImGui::SameLine(); ImGui::DragFloat("##DirectionY", &directionalLight.direction.y, 0.1f); ImGui::SameLine();
    ImGui::Text("Z"); ImGui::SameLine(); ImGui::DragFloat("##DirectionZ", &directionalLight.direction.z, 0.1f);

    
   
    ImGui::PopItemWidth();
    ImGui::End();
}
