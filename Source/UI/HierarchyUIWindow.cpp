#include "HierarchyUIWindow.h"

#include "Toolbar.h"
#include "../Engine/Managers/ObjectManager.h"
#include "../../Source/Engine/Managers/AssetLoader.h"

unsigned int HierarchyUIWindow::hierarchyCounter = 0;


HierarchyUIWindow::HierarchyUIWindow(const char* inName, Engine::UIID inUIID,
                                     const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
}

void HierarchyUIWindow::Render()
{
    const std::vector<std::shared_ptr<Object>>& objects = ObjectManager::objectHierarchy;
    std::string windowName = std::string(name) + "###" + std::to_string(UIID.id);

    if (ImGui::Begin(windowName.c_str()))
    {
        RenderPopUp();

        if (ImGui::Button("+"))
        {
            ImGui::OpenPopup("AddObjectPopup");
        }

        // Popup for adding objects
        if (ImGui::BeginPopup("AddObjectPopup"))
        {
            if (ImGui::MenuItem("Create Empty"))
            {
                std::string name = ("Empty");
                ObjectManager::AddEmpty(name);
            }

            if (ImGui::BeginMenu("Create 3D Object"))
            {
                if (ImGui::MenuItem("Sphere"))
                {
                    ObjectManager::CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_SPHERE));
                }
                if (ImGui::MenuItem("Cube"))
                {
                    ObjectManager::CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_CUBE));
                }
                if (ImGui::MenuItem("Plane"))
                {
                    ObjectManager::CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_PLANE));
                }
                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }

        ImGui::Separator();
        int counter = 0;
        for (const auto& obj : objects)
        {
            std::string buttonLabel = obj->name + "##" + std::to_string(counter);
            if (ImGui::Button(buttonLabel.c_str(), ImVec2(-1, 0)))
            {
                InspectorUIWindow::SetObject(obj);
            }
            counter++;
        }
    }
    ImGui::End();
}
