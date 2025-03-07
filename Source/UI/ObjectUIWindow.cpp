#include "ObjectUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Renderer.h"
ImVec2 ObjectUIWindow::size = ImVec2(300, 0);
std::shared_ptr<Object> ObjectUIWindow::activeUIObject = nullptr;

void ObjectUIWindow::SetObject(const std::shared_ptr<Object>& obj)
{
    ObjectUIWindow::activeUIObject = obj;
}

std::shared_ptr<Object> ObjectUIWindow::GetObject()
{
    return ObjectUIWindow::activeUIObject;
}

void ObjectUIWindow::Render()
{
    ImGui::Begin(activeUIObject != nullptr ? activeUIObject->name.c_str() : " ");

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
    }
    ImGui::PopItemWidth();
    ImGui::End();
}
