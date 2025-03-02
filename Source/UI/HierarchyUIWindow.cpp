#include "HierarchyUIWindow.h"
unsigned int HierarchyUIWindow::hierarchyCounter = 0;
void HierarchyUIWindow::Render(const std::vector<std::shared_ptr<Object>>& objects)
{
    int offset = 300;
    int height_offset = 170;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - offset, 10 + height_offset), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(offset, 400), ImGuiCond_Always);

    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    int counter = 0;
    for (const auto& obj : objects)
    {
        std::string buttonLabel = obj->name + "##" + std::to_string(counter);
        if (ImGui::Button(buttonLabel.c_str(), ImVec2(-1, 0)))
        {
            ObjectUIWindow::SetObject(obj);
        }
        counter++;
    }

    ImGui::End();
}


