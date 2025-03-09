#include "Toolbar.h"


Toolbar::Toolbar(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
}

void Toolbar::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Inspector"))
            {
                uiManager->CreateInspectorWindow();
            }

            if (ImGui::MenuItem("Hierarchy"))
            {
                uiManager->CreateHierarchyWindow();
            }

            if (ImGui::MenuItem("Material"))
            {
                uiManager->CreateMaterialWindow();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
