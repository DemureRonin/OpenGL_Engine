#include "SceneUIWindow.h"
#include "../imgui/imgui.h"

SceneUIWindow::SceneUIWindow(const std::shared_ptr<Camera>& camera, int width, int height): width(width),
    height(height), renderTexture(camera)
{
}

void SceneUIWindow::NewFrame()
{
    renderTexture.NewFrame(width, height);
}

void SceneUIWindow::Render()
{
    renderTexture.BindTexture();
    ImGui::Begin("Scene");

    ImGui::Image(renderTexture.FBO.GetColorBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
    width = ImGui::GetWindowWidth();
    height = ImGui::GetWindowHeight();
    ImGui::End();
}
