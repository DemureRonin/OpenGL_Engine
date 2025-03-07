#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../Engine/Transform.h"
#include "../Engine/Object.h"

class ObjectUIWindow
{
public:
    static ImVec2 size;
    static std::shared_ptr<Object> activeUIObject;
    
    static void SetObject(const std::shared_ptr<Object>& obj);
    static std::shared_ptr<Object> GetObject();
    static void Render();
};
