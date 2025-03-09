#pragma once
#include <string>

#include "UIWindow.h"
#include "../imgui/imgui.h"
#include "../Engine/Transform.h"
#include "../Engine/Object.h"

class InspectorUIWindow : public UIWindow
{
public:
    InspectorUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    static std::shared_ptr<Object> activeUIObject;
    void Render() override;
    void RenderInspectorObjectInfo();
    void RenderModelInfo();
    static bool showModelSelectionWindow;
    static bool showMaterialSelectionWindow;

    static void SetObject(const std::shared_ptr<Object>& obj);
    static std::shared_ptr<Object> GetObject();
};
