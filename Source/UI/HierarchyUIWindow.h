#pragma once
#include <string>
#include <vector>

#include "InspectorUIWindow.h"
#include "../Engine/Object.h"

#include "../imgui/imgui.h"
#include "../Engine/Transform.h"


class HierarchyUIWindow : public UIWindow
{
public:
    HierarchyUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void Render() override;
    bool showAddObjectWindow = false;
    static unsigned int hierarchyCounter;
};
