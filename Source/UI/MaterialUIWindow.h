#pragma once
#include "UIWindow.h"
#include "../Engine/Material.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class MaterialUIWindow : public UIWindow
{
public:
    MaterialUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void RenderWindow() override;
};
