#pragma once
#include "../Engine/Material.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class MaterialUIWindow
{
public:
    static void Render(Material& material);
};
