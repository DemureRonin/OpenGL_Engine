#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../Engine/Transform.h"
#include "../Engine/Object.h"

class ObjectUIWindow
{
public:
    static std::shared_ptr<Object> object;
    static void SetObject(const std::shared_ptr<Object>& obj);
    static std::shared_ptr<Object> GetObject();
    static void Render();
};
