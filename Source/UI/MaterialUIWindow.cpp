#include "MaterialUIWindow.h"

#include "InspectorUIWindow.h"
#include "../Engine/Object.h"

void MaterialUIWindow::Render()
{
    if (ImGui::Begin("Material Parameters", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        if (InspectorUIWindow::activeUIObject == nullptr || InspectorUIWindow::activeUIObject->material == nullptr)
        {
            ImGui::End();
            return;
        }


        std::string name;
        if (InspectorUIWindow::activeUIObject->material->shader != nullptr)
        {
            name = InspectorUIWindow::activeUIObject->material->shader->assetPath;
        }
        ImGui::Text("Shader: %s", name.c_str());

        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->textureParameters)
        {
            ImGui::Text(name.c_str());
            ImGui::SameLine();
            ImGui::Text(value->assetPath.c_str());
        }

        // Int Parameters (Clamp between 0 and 1, though int might not be ideal for this)
        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->intParameters)
        {
            value = glm::clamp(value, 0, 1); // Ensure value stays in range
            ImGui::DragInt(name.c_str(), &value, 1, 0, 1); // Step = 1, range [0, 1]
        }

        // Float Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->floatParameters)
        {
            ImGui::DragFloat(name.c_str(), &value, 0.001f, 0.0f, 1.0f, "%.4f"); // Step 0.001, more precise
        }

        // Vec2 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->vec2Parameters)
        {
            ImGui::DragFloat2(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }

        // Vec3 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->vec3Parameters)
        {
            ImGui::DragFloat3(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }

        // Vec4 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : InspectorUIWindow::activeUIObject->material->shaderParams->vec4Parameters)
        {
            ImGui::DragFloat4(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }
        ImGui::End();
    }
}
