#include "InspectorUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Renderer.h"
#include "../Engine/Initialization/ImGUIInitializer.h"
#include "../Engine/Managers/AssetLoader.h"
#include "../Engine/Managers/ObjectManager.h"
#include "../imgui/imgui_internal.h"

std::shared_ptr<Object> InspectorUIWindow::activeUIObject = nullptr;
bool InspectorUIWindow::showModelSelectionWindow = false;
bool InspectorUIWindow::showMaterialSelectionWindow = false;


InspectorUIWindow::InspectorUIWindow(const char* inName, Engine::UIID inUIID,
                                     const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
}

void InspectorUIWindow::Render()
{
    if (ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse))
    {
        RenderPopUp();
        auto objectName = activeUIObject != nullptr ? activeUIObject->name.c_str() : " ";
        ImGui::Text(objectName);

        ImGui::PushItemWidth(70);
        if (activeUIObject != nullptr)
        {
            RenderInspectorObjectInfo();
            RenderModelInfo();
        }
        ImGui::PopItemWidth();
    }

    ImGui::End();
}

void InspectorUIWindow::RenderInspectorObjectInfo()
{
    ImGui::Text("Position:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionX", &activeUIObject->transform.position.x, 0.1f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionY", &activeUIObject->transform.position.y, 0.1f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionZ", &activeUIObject->transform.position.z, 0.1f);

    ImGui::Text("Rotation:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationX", &activeUIObject->transform.rotation.x, 1.0f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationY", &activeUIObject->transform.rotation.y, 1.0f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationZ", &activeUIObject->transform.rotation.z, 1.0f);

    ImGui::Text("Scale:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleX", &activeUIObject->transform.scale.x, 0.1f, 0.01f, 10.0f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleY", &activeUIObject->transform.scale.y, 0.1f, 0.01f, 10.0f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleZ", &activeUIObject->transform.scale.z, 0.1f, 0.01f, 10.0f);
}

void InspectorUIWindow::RenderModelInfo()
{
    ImGui::Text(activeUIObject->model != nullptr ? activeUIObject->model->GetAssetPath().c_str() : " ");

    if (ImGui::Button("Set Model"))
    {
        ImGui::OpenPopup("Model Selection Popup");
    }


    if (ImGui::BeginPopup("Model Selection Popup"))
    {
        for (auto& it : AssetLoader::models)
        {
            std::string label = it.second->GetAssetPath() + "###" + it.first.ToString();
            if (ImGui::MenuItem(label.c_str()))
            {
                activeUIObject->SetModel(it.second);
              
            }
        }

        ImGui::EndPopup();
    }
    ImGui::Text(activeUIObject->material != nullptr ? activeUIObject->material->GetAssetPath().c_str() : " ");
    if (ImGui::Button("Set Material"))
    {
        ImGui::OpenPopup("Material Selection Popup");
    }
    if (ImGui::BeginPopup("Material Selection Popup"))
    {
        for (auto& it : AssetLoader::materials)
        {
            std::string label = it.second->GetAssetPath() + "###" + it.first.ToString();
            if (ImGui::MenuItem(label.c_str()))
            {
                activeUIObject->SetMaterial(it.second);
                
            }
        }

        ImGui::EndPopup();
    }
}

void InspectorUIWindow::SetObject(const std::shared_ptr<Object>& obj)
{
    InspectorUIWindow::activeUIObject = obj;
}

std::shared_ptr<Object> InspectorUIWindow::GetObject()
{
    return InspectorUIWindow::activeUIObject;
}
