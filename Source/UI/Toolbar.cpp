#include "Toolbar.h"


Toolbar::Toolbar(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
}

void Toolbar::RenderWindow()
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
            
            if (ImGui::MenuItem("Asset Browser"))
            {
                uiManager->CreateAssetBrowserWindow();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
