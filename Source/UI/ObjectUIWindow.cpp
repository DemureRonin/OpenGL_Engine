#include "ObjectUIWindow.h"

std::shared_ptr<Object> ObjectUIWindow::object = nullptr;

void ObjectUIWindow::SetObject(const std::shared_ptr<Object>& obj)
{
    ObjectUIWindow::object = obj;
}

std::shared_ptr<Object> ObjectUIWindow::GetObject()
{
    return ObjectUIWindow::object;
}


void ObjectUIWindow::Render()
{
    int offset = 300;
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - offset, 10), ImGuiCond_Always); // Top-right corner
    ImGui::SetNextWindowSize(ImVec2(offset, 160), ImGuiCond_Always); // Fixed width
    ImGui::Begin(object != nullptr ? object->name.c_str() : " ", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::PushItemWidth(70);
    if (object != nullptr)
    {
        ImGui::Text("Position:");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("##PositionX", &object->transform.position.x, 0.1f);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("##PositionY", &object->transform.position.y, 0.1f);
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("##PositionZ", &object->transform.position.z, 0.1f);

        ImGui::Text("Rotation:");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("##RotationX", &object->transform.rotation.x, 1.0f);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("##RotationY", &object->transform.rotation.y, 1.0f);
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("##RotationZ", &object->transform.rotation.z, 1.0f);

        ImGui::Text("Scale:");
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::DragFloat("##ScaleX", &object->transform.scale.x, 0.1f, 0.01f, 10.0f);
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::DragFloat("##ScaleY", &object->transform.scale.y, 0.1f, 0.01f, 10.0f);
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::DragFloat("##ScaleZ", &object->transform.scale.z, 0.1f, 0.01f, 10.0f);
    }
    ImGui::PopItemWidth();
    ImGui::End();
}
