#pragma once
#include "../imgui/imgui.h"

#include <string>
#include "../Engine/FastDelegate.h"
#include "UIWindow.h"



namespace Engine
{
    struct UIID;
}


class UIManager;

class AssetBrowserUIWindow : public UIWindow
{
private:
    std::string currentPath;
    std::string assetsPath;
    std::string selectedAssetPath;

public:
    AssetBrowserUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void RenderWindow() override;
    void RenderInspectorMaterialInfo() const;
};
