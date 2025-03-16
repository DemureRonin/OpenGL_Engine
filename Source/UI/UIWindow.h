#pragma once
#include <memory>
#include <string>
#include <vector>


#include "UIManager.h"
#include "../Engine/EngineID/GUID.h"
#include "../Engine/EngineID/UIID.h"

class UIWindow : public std::enable_shared_from_this<UIWindow>
{
public:
    UIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    virtual ~UIWindow() = default;

    std::shared_ptr<UIWindow> GetSharedPtr()
    {
        return shared_from_this();
    }

    std::shared_ptr<UIManager> uiManager;
    std::string name;
    Engine::UIID UIID;
    std::string windowName;
    std::string windowHash;
    void RenderPopUp();
    virtual void RenderWindow() = 0;
};
