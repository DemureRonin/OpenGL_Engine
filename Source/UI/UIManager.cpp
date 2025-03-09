#include "UIManager.h"

#include "MaterialUIWindow.h"
#include "UIWindow.h"
#include "Toolbar.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
UIManager::UIManager()
= default;

void UIManager::CreateInspectorWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<InspectorUIWindow> inspector = std::make_shared<InspectorUIWindow>(
        "Inspector", UIID, GetSharedPtr());
    AddWindow(inspector);
}

void UIManager::CreateHierarchyWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<HierarchyUIWindow> hierarchy = std::make_shared<HierarchyUIWindow>(
        "Hierarchy", UIID, GetSharedPtr());
    AddWindow(hierarchy);
}

void UIManager::CreateMaterialWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<MaterialUIWindow> materialUIWindow = std::make_shared<MaterialUIWindow>(
        "Material", UIID, GetSharedPtr());
    AddWindow(materialUIWindow);
}

void UIManager::AddWindow(const std::shared_ptr<UIWindow>& window)
{
    windows.push_back(window);
}

void UIManager::CloseWindow(const std::shared_ptr<UIWindow>& window)
{
    std::erase(windows, window);
}

void UIManager::RenderUI() const
{
    for (size_t i = 0; i < windows.size(); ++i)
    {
        if (windows[i])
            windows[i]->Render();
        else std::cout << "NULL" << std::endl;
    }
}

void UIManager::CreateBasicLayout()
{
    auto UIID = Engine::UIID();
    std::shared_ptr<Toolbar> toolbar = std::make_shared<Toolbar>("Toolbar", UIID, GetSharedPtr());
    AddWindow(toolbar);

    UIID = Engine::UIID();
    std::shared_ptr<InspectorUIWindow> inspector = std::make_shared<InspectorUIWindow>(
        "Inspector", UIID, GetSharedPtr());
    AddWindow(inspector);

    UIID = Engine::UIID();
    std::shared_ptr<HierarchyUIWindow> hierarchy = std::make_shared<HierarchyUIWindow>(
        "Hierarchy", UIID, GetSharedPtr());
    AddWindow(hierarchy);
}
