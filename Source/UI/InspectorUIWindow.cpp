#include "InspectorUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Renderer.h"
#include "../Engine/Managers/AssetLoader.h"
#include "../Engine/Managers/ObjectManager.h"

ImVec2 InspectorUIWindow::size = ImVec2(300, 0);
std::shared_ptr<Object> InspectorUIWindow::activeUIObject = nullptr;
bool InspectorUIWindow::showModelSelectionWindow = false;
bool InspectorUIWindow::showMaterialSelectionWindow = false;

void InspectorUIWindow::SetObject(const std::shared_ptr<Object>& obj)
{
    InspectorUIWindow::activeUIObject = obj;
}

std::shared_ptr<Object> InspectorUIWindow::GetObject()
{
    return InspectorUIWindow::activeUIObject;
}

void InspectorUIWindow::Render()
{
    ImGui::Begin("Inspector");
    ImGui::Text(activeUIObject != nullptr ? activeUIObject->name.c_str() : " ");

    ImGui::PushItemWidth(70);
    if (activeUIObject != nullptr)
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

        ImGui::Text("Model:");
        ImGui::SameLine();
        ImGui::Text(activeUIObject->model ? activeUIObject->model->assetPath.c_str() : "");
        if (ImGui::Button("Add Model"))
        {
            showModelSelectionWindow = true;
        }
        ImGui::Text("Material:");
        ImGui::SameLine();
        ImGui::Text(activeUIObject->material ? activeUIObject->material->assetPath.c_str() : "");
        if (ImGui::Button("Select Material"))
        {
            showMaterialSelectionWindow = true;
        }

        if (showModelSelectionWindow)
        {
            ImGui::Begin("Select Model", &showModelSelectionWindow, ImGuiWindowFlags_AlwaysAutoResize);

            for (const auto& [guid, model] : AssetLoader::models)
            {
                if (ImGui::Button(model->assetPath.c_str()))
                {
                    activeUIObject->model = model;
                    showModelSelectionWindow = false; // Close the window after selecting
                }
            }

            ImGui::End();
        }
        
        if (showMaterialSelectionWindow)
        {
            ImGui::Begin("Select Material", &showMaterialSelectionWindow, ImGuiWindowFlags_AlwaysAutoResize);

            for (const auto& [guid, material] : AssetLoader::materials)
            {
                if (ImGui::Button(material->assetPath.c_str()))
                {
                    activeUIObject->SetMaterial(material);
                    material->shader = std::static_pointer_cast<Shader>(AssetLoader::GetAsset(material->shader->guid));
                    ObjectManager::InitMaterialMap();
                    showMaterialSelectionWindow = false;
                }
            }

            ImGui::End();
        }
    }
    ImGui::PopItemWidth();
    ImGui::End();
}
