#pragma once
#include <string>
#include <vector>

#include "InspectorUIWindow.h"
#include "../Engine/Prefab.h"

#include "../imgui/imgui.h"
#include "../Engine/Transform.h"


class HierarchyUIWindow : public UIWindow
{
public:
    HierarchyUIWindow(const char* inName, Engine::UIID inUIID, const std::shared_ptr<UIManager>& inUIManager);
    void RenderInspectorObjectInfo() const;
    void RenderModelInfo();
    unsigned int AssignObjectID(const std::shared_ptr<Prefab>& obj);
    void RenderWindow() override;
    void OnObjectAdded(const std::shared_ptr<Prefab>& obj);
    void RenderAddObjectButton(const std::shared_ptr<Scene>& scene);
    void RenderObjectHierarchy(const std::vector<std::shared_ptr<Prefab>>& objects);
    void RenderObjectHierarchyRecursive(const std::shared_ptr<Prefab>& obj, int counter, unsigned int objID);
    void SetActiveUIObject(const std::shared_ptr<Prefab>& obj);
    void RenderObjectContextMenu(const std::shared_ptr<Prefab>& obj, unsigned int objID);
    void RenderObjectRenameInput(const std::shared_ptr<Prefab>& obj);
    void HandleObjectSelection(const std::shared_ptr<Prefab>& obj);
    void HandleObjectRenaming(const std::shared_ptr<Prefab>& obj);

    std::shared_ptr<Prefab> activeUIObject = nullptr;
    bool showAddObjectWindow = false;

    static std::shared_ptr<Prefab> renamingObject;
    static char nameBuffer[256];
    static unsigned int hierarchyCounter;

private:
    static std::unordered_map<std::shared_ptr<Prefab>, unsigned int> objectIDs;
    void RenderInspector();
};
