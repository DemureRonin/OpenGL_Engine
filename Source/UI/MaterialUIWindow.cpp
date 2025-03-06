#include "MaterialUIWindow.h"

void MaterialUIWindow::Render(const Material& material)
{
    // Set position to bottom-right corner
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 windowSize(300, 400);  // Adjust size as needed
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - windowSize.x - 10, io.DisplaySize.y - windowSize.y - 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(windowSize);

    if (ImGui::Begin("Material Parameters", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        
        // Shader File
        ImGui::Text("Shader: %s", material.shaderParams->shaderFile.c_str());

        // Int Parameters (Clamp between 0 and 1, though int might not be ideal for this)
        for (auto& [name, value] : material.shaderParams->intParameters) {
            value = glm::clamp(value, 0, 1); // Ensure value stays in range
            ImGui::DragInt(name.c_str(), &value, 1, 0, 1); // Step = 1, range [0, 1]
        }

        // Float Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : material.shaderParams->floatParameters) {
            ImGui::DragFloat(name.c_str(), &value, 0.001f, 0.0f, 1.0f, "%.4f"); // Step 0.001, more precise
        }

        // Vec2 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : material.shaderParams->vec2Parameters) {
            ImGui::DragFloat2(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }

        // Vec3 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : material.shaderParams->vec3Parameters) {
            ImGui::DragFloat3(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }

        // Vec4 Parameters (Slow drag, range 0 - 1)
        for (auto& [name, value] : material.shaderParams->vec4Parameters) {
            ImGui::DragFloat4(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
        }
        ImGui::End();
    }

}
