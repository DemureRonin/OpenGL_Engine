#pragma once
#include <string>

#include "UIWindow.h"
#include "../imgui/imgui.h"
#include "../Engine/Transform.h"
#include "../Engine/Prefab.h"

class InspectorUIWindow : public UIWindow
{
public:
    InspectorUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void RenderInspectorContents(const std::function<void()>& inRenderFunction);

    void RenderWindow() override;
    std::function<void()> renderFunction;
};
