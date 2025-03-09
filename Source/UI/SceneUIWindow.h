#pragma once

#include "../Engine/RenderTexture.h"


class SceneUIWindow
{
public:
    SceneUIWindow(const std::shared_ptr<Camera>& camera, int width, int height);
    std::shared_ptr<Camera> camera;
    std::vector<float> GenerateGridVertices(float gridSize, float step);
    std::vector<float> gridVertices;
    GLuint gridVAO, gridVBO;
    void NewFrame();
    void Render();
    int width, height;
    std::shared_ptr<Material> gridMaterial;
    RenderTexture renderTexture;
};
