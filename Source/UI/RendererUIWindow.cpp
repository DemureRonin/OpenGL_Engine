#include "RendererUIWindow.h"

void RendererUIWindow::Render()
{
    int offset = 10;
    ImGui::SetNextWindowPos(ImVec2( offset, 10), ImGuiCond_Always); // Top-right corner
    ImGui::SetNextWindowSize(ImVec2(250, 100), ImGuiCond_Always);

    ImGui::Begin("Renderer Settings", nullptr, ImGuiWindowFlags_NoResize);

    if (ImGui::Checkbox("Wireframe Mode", &Renderer::polygonMode))
    {
        Renderer::SetPolygonMode();
    }

   
    ImGui::Text("Clear Color:");
    ImGui::ColorEdit4("##color", &Renderer::color[0]);

    ImGui::End();
}