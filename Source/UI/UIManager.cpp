#include "UIManager.h"

#include "AssetBrowserUIWindow.h"
#include "SceneUIWindow.h"
#include "MaterialUIWindow.h"
#include "UIWindow.h"
#include "Toolbar.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

UIManager::UIManager(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Camera>& inCamera, int inWidth,
                     int inHeight)
{
    camera = inCamera;
    height = inHeight;
    width = inWidth;
    this->scene = scene;
}

void UIManager::ResetHierarchyActiveObject() const
{
    for (const auto& hierarchy : hierarchies)
    {
        hierarchy->activeUIObject = nullptr;
    }
}

void UIManager::CreateAssetBrowserWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<AssetBrowserUIWindow> assetBrowser = std::make_shared<AssetBrowserUIWindow>(
        "Asset Browser", UIID, GetSharedPtr());
    AddWindow(assetBrowser);
}

void UIManager::CreateSceneWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<SceneUIWindow> sceneUIWindow = std::make_shared<SceneUIWindow>(
        "Scene", UIID, GetSharedPtr(), camera, width, height, scene);
    sceneUIWindows.push_back(sceneUIWindow);
}

void UIManager::SceneNewFrame() const
{
    for (const auto& sceneUIWIndow : sceneUIWindows)
    {
        sceneUIWIndow->NewFrame();
    }
}

void UIManager::RenderScene() const
{
    for (const auto& sceneUIWIndow : sceneUIWindows)
    {
        sceneUIWIndow->RenderWindow();
    }
}

void UIManager::CreateInspectorWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<InspectorUIWindow> inspector = std::make_shared<InspectorUIWindow>(
        "Inspector", UIID, GetSharedPtr());
    AddWindow(inspector);
    inspectors.push_back(inspector);
}

void UIManager::CreateHierarchyWindow()
{
    auto UIID = Engine::UIID();
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    std::shared_ptr<HierarchyUIWindow> hierarchy = std::make_shared<HierarchyUIWindow>(
        "Hierarchy", UIID, GetSharedPtr());
    AddWindow(hierarchy);
    hierarchies.push_back(hierarchy);
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

void UIManager::UpdateInspectorWindows(const std::function<void()>& inRenderFunction) const
{
    for (const auto& inspector : inspectors)
    {
        inspector->RenderInspectorContents(inRenderFunction);
    }
}

void UIManager::OnHierarchyObjectAdded(const std::shared_ptr<Prefab>& object) const
{
    for (const auto& hierarchy : hierarchies)
    {
        hierarchy->OnObjectAdded(object);
    }
}

void UIManager::RenderUI() const
{
    for (size_t i = 0; i < windows.size(); ++i)
    {
        if (windows[i])
            windows[i]->RenderWindow();
        else std::cout << "NULL" << std::endl;
    }
}

void UIManager::CreateToolbar()
{
    auto UIID = Engine::UIID();
    std::shared_ptr<Toolbar> toolbar = std::make_shared<Toolbar>("Toolbar", UIID, GetSharedPtr());
    AddWindow(toolbar);
}

void UIManager::CreateBasicLayout()
{
    CreateToolbar();
    CreateInspectorWindow();
    CreateHierarchyWindow();
    CreateSceneWindow();
    CreateAssetBrowserWindow();
}
