#pragma once

#include "UIWindow.h"
#include "../Engine/RenderTexture.h"


class Scene;

class SceneUIWindow : public UIWindow
{
public:
    SceneUIWindow(const char* inName, Engine::UIID inUIID,
                  const std::shared_ptr<UIManager>& inUIManager,
                  const std::shared_ptr<Camera>& camera, int width, int height, const std::shared_ptr<Scene>& inScene);
    std::shared_ptr<Camera> camera;
    void NewFrame();
    void RenderWindow() override;
    int width, height;
    std::shared_ptr<Material> gridMaterial;
    RenderTexture renderTexture;
    std::shared_ptr<Scene> scene;
};
