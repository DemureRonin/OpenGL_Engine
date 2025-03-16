#pragma once
#include <functional>
#include <memory>
#include <vector>


class Camera;
class SceneUIWindow;
class Prefab;
class HierarchyUIWindow;
class InspectorUIWindow;
class Scene;
class UIWindow;

class UIManager : public std::enable_shared_from_this<UIManager>
{
private:
    void CreateToolbar();

public:
    UIManager(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Camera>& inCamera, int inWidth, int inHeight);

    std::shared_ptr<UIManager> GetSharedPtr()
    {
        return shared_from_this();
    }

    void ResetHierarchyActiveObject() const;

    std::shared_ptr<Camera> camera = nullptr;
    int width;
    int height;


    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<HierarchyUIWindow>> hierarchies;
    std::vector<std::shared_ptr<UIWindow>> windows;
    std::vector<std::shared_ptr<InspectorUIWindow>> inspectors;
    std::vector<std::shared_ptr<SceneUIWindow>> sceneUIWindows;

    void SceneNewFrame() const;
    void RenderScene() const;


    void CreateInspectorWindow();
    void CreateHierarchyWindow();
    void CreateMaterialWindow();
    void CreateAssetBrowserWindow();
    void CreateSceneWindow();

    void AddWindow(const std::shared_ptr<UIWindow>& window);
    void CloseWindow(const std::shared_ptr<UIWindow>& window);
    void OnHierarchyObjectAdded(const std::shared_ptr<Prefab>& object) const;
    void UpdateInspectorWindows(const std::function<void()>& inRenderFunction) const;
    void RenderUI() const;

    void CreateBasicLayout();
};
