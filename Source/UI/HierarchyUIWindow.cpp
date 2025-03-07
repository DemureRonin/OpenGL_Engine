#include "HierarchyUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Managers/ObjectManager.h"

unsigned int HierarchyUIWindow::hierarchyCounter = 0;
static bool showAddObjectWindow = false;

void HierarchyUIWindow::Render(const std::vector<std::shared_ptr<Object>>& objects)
{
    ImGui::Begin("Hierarchy");

    // ImGui::SameLine();
    if (ImGui::Button("+"))
    {
        showAddObjectWindow = !showAddObjectWindow; // Toggle the new window visibility
    }

    // ImGui::Separator();
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
