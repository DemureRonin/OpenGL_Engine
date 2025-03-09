#include "SceneUIWindow.h"


#include "UIWindow.h"
#include "../Engine/Camera.h"
#include "../Engine/Managers/AssetLoader.h"
#include "../imgui/imgui.h"


SceneUIWindow::SceneUIWindow(const std::shared_ptr<Camera>& camera, int width, int height): camera(camera),
    width(width),
    height(height), renderTexture(camera)
{
    gridVertices = GenerateGridVertices(100.0f, 2.0f);

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    gridMaterial = std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_UNLIT)));
}

std::vector<float> SceneUIWindow::GenerateGridVertices(float gridSize, float step)
{
    std::vector<float> vertices;

    // Lines along X-axis
    for (float z = -gridSize; z <= gridSize; z += step)
    {
        vertices.push_back(-gridSize); // X start
        vertices.push_back(0.0f); // Y
        vertices.push_back(z); // Z

        vertices.push_back(gridSize); // X end
        vertices.push_back(0.0f); // Y
        vertices.push_back(z); // Z
    }

    // Lines along Z-axis
    for (float x = -gridSize; x <= gridSize; x += step)
    {
        vertices.push_back(x); // X
        vertices.push_back(0.0f); // Y
        vertices.push_back(-gridSize); // Z start

        vertices.push_back(x); // X
        vertices.push_back(0.0f); // Y
        vertices.push_back(gridSize); // Z end
    }

    return vertices;
}


void SceneUIWindow::NewFrame()
{
    renderTexture.NewFrame(width, height);
}

void SceneUIWindow::Render()
{
    gridMaterial->shader->Bind();
    gridMaterial->shader->SetCameraUniforms(*camera);
    gridMaterial->shader->SetMaterialUniforms(gridMaterial);
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
    glBindVertexArray(0);
    renderTexture.BindTexture();
    ImGui::Begin("Scene");

    ImGui::Image(renderTexture.FBO.GetColorBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
    width = ImGui::GetWindowWidth();
    height = ImGui::GetWindowHeight();
    ImGui::End();
}
