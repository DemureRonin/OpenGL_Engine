#include "SceneUIWindow.h"


#include "UIWindow.h"
#include "../Engine/Camera.h"
#include "../Engine/Scene.h"
#include "../Engine/Types.h"
#include "../Engine/Managers/AssetLoader.h"
#include "../imgui/imgui.h"


SceneUIWindow::SceneUIWindow(const char* inName, Engine::UIID inUIID,
                             const std::shared_ptr<UIManager>& inUIManager, const std::shared_ptr<Camera>& camera,
                             int width, int height,
                             const std::shared_ptr<Scene>& inScene): UIWindow(inName, inUIID, inUIManager),
                                                                     camera(camera),
                                                                     width(width),
                                                                     height(height), renderTexture(camera),
                                                                     scene(inScene)


{
} 


void SceneUIWindow::NewFrame()
{
    renderTexture.NewFrame(width, height);
}

void SceneUIWindow::RenderWindow()
{
    renderTexture.BindTexture();
    if (ImGui::Begin(windowName.c_str()))
    {
        ImGui::Image(renderTexture.FBO.GetColorBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MODEL_PATH"))
            {
                std::string modelGUID = static_cast<const char*>(payload->Data);
                auto model = TYPEOF(Model)(AssetLoader::GetAsset(Engine::GUID::FromString(modelGUID)));
                auto sceneObject = scene->AddModel(model);
                uiManager->OnHierarchyObjectAdded(sceneObject);
            }
            ImGui::EndDragDropTarget();
        }
        width = ImGui::GetWindowWidth();
        height = ImGui::GetWindowHeight();
        ImGui::End();
    }
}
