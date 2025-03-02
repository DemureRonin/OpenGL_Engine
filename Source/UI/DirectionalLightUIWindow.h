#pragma once
#include "../Engine/DirectionalLight.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
class DirectionalLightUIWindow
{
public:
    static void Render(DirectionalLight& directionalLight);
};
