#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../Engine/Transform.h"
#include "../Engine/Object.h"

class InspectorUIWindow
{
public:
    static ImVec2 size;
    static std::shared_ptr<Object> activeUIObject;

    static bool showModelSelectionWindow;
    static bool showMaterialSelectionWindow;
    static void SetObject(const std::shared_ptr<Object>& obj);
    static std::shared_ptr<Object> GetObject();
    static void Render();
};
