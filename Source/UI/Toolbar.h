#pragma once
#include "HierarchyUIWindow.h"
#include "InspectorUIWindow.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Toolbar : public UIWindow
{
public:
    Toolbar(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void Render() override;
};
