#include "UIWindow.h"

#include <memory>

#include "HierarchyUIWindow.h"
#include "InspectorUIWindow.h"


UIWindow::UIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager)
{
    this->name = inName;
    this->UIID = inUIID;
    this->uiManager = inUIManager;
    windowName = std::string(name) + "###" + std::to_string(UIID.id);
    windowHash = "###" + std::to_string(UIID.id);
}

void UIWindow::RenderPopUp()
{
    if (ImGui::IsItemHovered())
    {
        if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
        {
            ImGui::OpenPopup("RightClickMenu");
        }
    }

    if (ImGui::BeginPopup("RightClickMenu"))
    {
        if (ImGui::MenuItem("Close Tab"))
        {
            uiManager->CloseWindow(this->GetSharedPtr());
        }
        ImGui::EndPopup();
    }
}
