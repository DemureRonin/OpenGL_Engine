#include "InspectorUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Renderer.h"
#include "../Engine/Scene.h"
#include "../Engine/Initialization/ImGUIInitializer.h"
#include "../Engine/Managers/AssetLoader.h"

#include "../imgui/imgui_internal.h"


InspectorUIWindow::InspectorUIWindow(const char* inName, Engine::UIID inUIID,
                                     const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
}

void InspectorUIWindow::RenderInspectorContents(const std::function<void()>& inRenderFunction)
{
   renderFunction = inRenderFunction;
}

void InspectorUIWindow::RenderWindow()
{
   
    if (ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse))
    {
        RenderPopUp();
        if (renderFunction)
        {
            renderFunction();
        }
       
        ImGui::End();
    }
}
