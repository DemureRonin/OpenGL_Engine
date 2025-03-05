#include "HierarchyUIWindow.h"

#include "../Engine/Managers/ObjectManager.h"

unsigned int HierarchyUIWindow::hierarchyCounter = 0;
static bool showAddObjectWindow = false;

void HierarchyUIWindow::Render(const std::vector<std::shared_ptr<Object>>& objects)
{
    int offset = 300;
    int height_offset = 170;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - offset, 10 + height_offset), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(offset, 400), ImGuiCond_Always);

    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::SameLine();
    if (ImGui::Button("+"))
    {
        showAddObjectWindow = !showAddObjectWindow; // Toggle the new window visibility
    }

    ImGui::Separator();
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

    // Render the additional window to the right of "Scene"
    if (showAddObjectWindow)
    {
        ImVec2 sceneWindowPos = ImVec2(ImGui::GetIO().DisplaySize.x - offset, 10 + height_offset);
        ImVec2 addObjectWindowPos = ImVec2(sceneWindowPos.x + offset - 500, sceneWindowPos.y); // Position to the right

        ImGui::SetNextWindowPos(addObjectWindowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Always);

        ImGui::Begin("Add Object", &showAddObjectWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        if (ImGui::Button("Create Empty"))
        {
            std::string name = "Empty Object";
            ObjectManager::AddEmpty(name);
        }
        if (ImGui::Button("Load From File"))
        {
            ObjectManager::LoadObjectFromFile();
        }


        ImGui::End();
    }
}
