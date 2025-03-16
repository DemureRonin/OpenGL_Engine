#include "HierarchyUIWindow.h"
#include "Toolbar.h"

#include "../../Source/Engine/Managers/AssetLoader.h"
#include "IconsFontAwesome5.h"
#include "../Engine/Scene.h"

unsigned int HierarchyUIWindow::hierarchyCounter = 0;
std::shared_ptr<Prefab> HierarchyUIWindow::renamingObject = nullptr;
char HierarchyUIWindow::nameBuffer[256] = "";
std::unordered_map<std::shared_ptr<Prefab>, unsigned int> HierarchyUIWindow::objectIDs{};

HierarchyUIWindow::HierarchyUIWindow(const char* inName, Engine::UIID inUIID,
                                     const std::shared_ptr<UIManager>& inUIManager)
    : UIWindow(inName, inUIID, inUIManager)
{
    for (const auto& element : uiManager->scene->rootObjects)
    {
        AssignObjectID(element);
    }
}

void HierarchyUIWindow::RenderInspectorObjectInfo() const
{
    ImGui::Text("Position:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionX", &activeUIObject->transform.position.x, 0.1f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionY", &activeUIObject->transform.position.y, 0.1f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##PositionZ", &activeUIObject->transform.position.z, 0.1f);

    ImGui::Text("Rotation:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationX", &activeUIObject->transform.rotation.x, 1.0f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationY", &activeUIObject->transform.rotation.y, 1.0f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##RotationZ", &activeUIObject->transform.rotation.z, 1.0f);

    ImGui::Text("Scale:");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleX", &activeUIObject->transform.scale.x, 0.1f, 0.01f, 10.0f);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleY", &activeUIObject->transform.scale.y, 0.1f, 0.01f, 10.0f);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleZ", &activeUIObject->transform.scale.z, 0.1f, 0.01f, 10.0f);
}

void HierarchyUIWindow::RenderModelInfo()
{

    if (ImGui::Button("Set Model"))
    {
        ImGui::OpenPopup("Model Selection Popup");
    }


    if (ImGui::BeginPopup("Model Selection Popup"))
    {
        for (auto& it : AssetLoader::models)
        {
            std::string label = it.second->name + "###" + it.first.ToString();
            if (ImGui::MenuItem(label.c_str()))
            {
                activeUIObject->SetMesh(it.second->meshes[0]);
                uiManager->scene->AddObjectToRender(activeUIObject);
            }
        }

        ImGui::EndPopup();
    }
    ImGui::Text(activeUIObject->material != nullptr ? activeUIObject->material->name.c_str() : " ");
    if (ImGui::Button("Set Material"))
    {
        ImGui::OpenPopup("Material Selection Popup");
    }
    if (ImGui::BeginPopup("Material Selection Popup"))
    {
        for (auto& it : AssetLoader::materials)
        {
            std::string label = it.second->name + "###" + it.first.ToString();
            if (ImGui::MenuItem(label.c_str()))
            {
                auto old = activeUIObject->material;

                activeUIObject->SetMaterial(it.second);
                uiManager->scene->UpdateObjectMaterial(activeUIObject, old, it.second);
            }
        }

        ImGui::EndPopup();
    }
}

void HierarchyUIWindow::RenderInspector()
{
    auto objectName = activeUIObject != nullptr ? activeUIObject->name.c_str() : " ";
    ImGui::Text(objectName);

    ImGui::PushItemWidth(70);
    if (activeUIObject != nullptr)
    {
        RenderInspectorObjectInfo();
        RenderModelInfo();
    }
    ImGui::PopItemWidth();
}

unsigned int HierarchyUIWindow::AssignObjectID(const std::shared_ptr<Prefab>& obj)
{
    if (!obj)
        return {};

    auto it = objectIDs.find(obj);
    if (it != objectIDs.end())
    {
        return it->second;
    }
    Engine::UIID newID;
    objectIDs[obj] = newID.id;

    return newID.id;
}

void HierarchyUIWindow::RenderWindow()
{
    ImGui::ShowDemoWindow();
    auto scene = uiManager->scene;
    const auto& objects = scene->sceneObjects;

    for (auto it = objectIDs.begin(); it != objectIDs.end();)
    {
        if (std::ranges::find(objects, it->first) == objects.end())
            it = objectIDs.erase(it);
        else
            ++it;
    }

    std::string windowName = std::string(name) + "###" + std::to_string(UIID.id);
    if (ImGui::Begin(windowName.c_str()))
    {
        RenderPopUp();
        RenderAddObjectButton(scene);
        ImGui::Separator();

        if (ImGui::TreeNodeEx("Scene Objects", ImGuiTreeNodeFlags_DefaultOpen))
        {
            RenderObjectHierarchy(scene->rootObjects);
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

void HierarchyUIWindow::OnObjectAdded(const std::shared_ptr<Prefab>& obj)
{
    for (const auto& child : obj->children)
    {
        AssignObjectID(child);
    }
    AssignObjectID(obj);
    SetActiveUIObject(obj);
}

void HierarchyUIWindow::RenderAddObjectButton(const std::shared_ptr<Scene>& scene)
{
    if (ImGui::Button("+"))
    {
        ImGui::OpenPopup("AddObjectPopup");
    }

    if (ImGui::BeginPopup("AddObjectPopup"))
    {
        if (ImGui::MenuItem("Create Empty"))
        {
            auto obj = scene->AddEmpty("Empty");
            AssignObjectID(obj);
            SetActiveUIObject(obj);
        }


        if (ImGui::BeginMenu("Add Model"))
        {
            for (auto& it : AssetLoader::models)
            {
                std::string label = it.second->name + "###" + it.first.ToString() + "Model Add";
                if (ImGui::MenuItem(label.c_str()))
                {
                    auto obj = scene->AddModel(it.second);
                    OnObjectAdded(obj);
                   
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Create 3D Object"))
        {
            if (ImGui::MenuItem("Sphere"))
            {
                auto obj = scene->CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_SPHERE));
                AssignObjectID(obj);
                SetActiveUIObject(obj);
            }

            if (ImGui::MenuItem("Cube"))
            {
                auto obj = scene->CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_CUBE));
                AssignObjectID(obj);
                SetActiveUIObject(obj);
            }

            if (ImGui::MenuItem("Plane"))
            {
                auto obj = scene->CreatePrimitive(Engine::GUID::FromString(PRIMITIVE_PLANE));
                AssignObjectID(obj);
                SetActiveUIObject(obj);
            }

            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }
}

void HierarchyUIWindow::RenderObjectHierarchy(const std::vector<std::shared_ptr<Prefab>>& objects)
{
    int counter = 0;
    for (const auto& obj : objects)
    {
        if (obj && objectIDs.contains(obj))
        {
            RenderObjectHierarchyRecursive(obj, counter, objectIDs[obj]);
        }
    }
}

void HierarchyUIWindow::RenderObjectHierarchyRecursive(const std::shared_ptr<Prefab>& obj, int counter,
                                                       unsigned int objID)
{
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
    if (!obj->HasChildren())
        flag |= ImGuiTreeNodeFlags_Leaf;

    if (activeUIObject == obj)
        flag |= ImGuiTreeNodeFlags_Selected;
    // ICON_FA_CUBE
    //ICON_FA_DICE_D6
    std::string objectLabel = ICON_FA_CUBE + std::string(" ") + obj->name + "##" + std::to_string(objID);

    bool nodeOpen = ImGui::TreeNodeEx((renamingObject == obj) ? "##RenameNode" : objectLabel.c_str(), flag);


    if (renamingObject == obj)
    {
        ImGui::SameLine();
        RenderObjectRenameInput(obj);
    }

    HandleObjectSelection(obj);
    HandleObjectRenaming(obj);
    RenderObjectContextMenu(obj, objID);

    if (nodeOpen)
    {
        for (const auto& child : obj->children)
        {
            if (child)
            {
                auto childID = AssignObjectID(child);
                RenderObjectHierarchyRecursive(child, counter, childID);
            }
        }
        ImGui::TreePop();
    }
}

void HierarchyUIWindow::SetActiveUIObject(const std::shared_ptr<Prefab>& obj)
{
    activeUIObject = obj;
    uiManager->UpdateInspectorWindows([this]() { RenderInspector(); });
}

void HierarchyUIWindow::RenderObjectContextMenu(const std::shared_ptr<Prefab>& obj, unsigned int objID)
{
    std::string popupId = obj->name + "##ContextMenu" + std::to_string(objID);
    if (ImGui::BeginPopupContextItem(popupId.c_str()))
    {
        if (ImGui::MenuItem("Rename"))
        {
            renamingObject = obj;
            strncpy_s(nameBuffer, 256, obj->name.c_str(), _TRUNCATE);
        }

        if (ImGui::MenuItem("Delete"))
            uiManager->scene->RemoveObject(obj);

        if (ImGui::MenuItem("Create Child"))
        {
            auto child = uiManager->scene->AddChild(obj);
            SetActiveUIObject(child);
        }


        if (ImGui::MenuItem("Duplicate"))
        {
        }
        ImGui::EndPopup();
    }
}

void HierarchyUIWindow::RenderObjectRenameInput(const std::shared_ptr<Prefab>& obj)
{
    ImGui::SetNextItemWidth(ImGui::CalcTextSize(nameBuffer).x + 20);
    ImGui::SetKeyboardFocusHere();

    if (ImGui::InputText("##RenameObject", nameBuffer, sizeof(nameBuffer),
                         ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
    {
        obj->name = std::string(nameBuffer);
        renamingObject = nullptr;
    }

    if (!ImGui::IsItemActive() && ImGui::IsMouseClicked(0))
    {
        renamingObject = nullptr;
    }
}


void HierarchyUIWindow::HandleObjectSelection(const std::shared_ptr<Prefab>& obj)
{
    if (ImGui::IsItemClicked())
    {
        SetActiveUIObject(obj);
    }
}

void HierarchyUIWindow::HandleObjectRenaming(const std::shared_ptr<Prefab>& obj)
{
    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        renamingObject = obj;
        strncpy_s(nameBuffer, sizeof(nameBuffer), obj->name.c_str(), _TRUNCATE);
    }
}
