#pragma once
#include <string>
#include <vector>

#include "ObjectUIWindow.h"
#include "../Engine/Object.h"

#include "../imgui/imgui.h"
#include "../Engine/Transform.h"


class HierarchyUIWindow
{
public:
    static unsigned int hierarchyCounter;
    static void Render(const std::vector<std::shared_ptr<Object>>& objects);
    
};

