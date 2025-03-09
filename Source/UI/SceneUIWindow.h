#pragma once

#include "../Engine/RenderTexture.h"

class SceneUIWindow
{
public:
    SceneUIWindow(const std::shared_ptr<Camera>& camera, int width, int height);
    void NewFrame();
    void Render();
    int width, height;
    RenderTexture renderTexture;
};
