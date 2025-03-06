#pragma once
#include "../imgui/imgui.h"
class SceneWindow
{
public:
    static ImVec2 windowSize;
    static ImVec2 dddd;
    static void InitializeSceneWindow(int x, int y);
    static void RenderSceneWindow(int& width, int& height, int& posX, int& posY);
    
};
