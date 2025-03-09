#pragma once
#include <memory>
#include <vector>


class UIWindow;

class UIManager : public std::enable_shared_from_this<UIManager>
{
public:
     UIManager();
     std::shared_ptr<UIManager> GetSharedPtr()
     {
          return shared_from_this();
     }

     void CreateInspectorWindow();
     void CreateHierarchyWindow();
     void CreateMaterialWindow();
     std::vector<std::shared_ptr<UIWindow>> windows;
     void AddWindow(const std::shared_ptr<UIWindow>& window);
     void CloseWindow(const std::shared_ptr<UIWindow>& window);
     void RenderUI() const;
     void CreateBasicLayout();
};
