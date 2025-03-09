#include "ObjectManager.h"
#include "AssetLoader.h"

std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Object>>> ObjectManager::materialObjectMap{};
std::vector<std::shared_ptr<Object>> ObjectManager::objectHierarchy{};

void ObjectManager::AddObject(const std::shared_ptr<Object>& object)
{
    if (!object) return;

    objectHierarchy.push_back(object);
    AddObjectToRender(object);
}

void ObjectManager::RemoveObject(const std::shared_ptr<Object>& object)
{
    if (object)
        std::erase(objectHierarchy, object);
    if (object->material)
        RemoveObjectFromRender(object, object->material);
}

void ObjectManager::AddObjectToRender(const std::shared_ptr<Object>& object)
{
    if (!object || !object->material) return;
    materialObjectMap[object->material].push_back(object);
}

void ObjectManager::RemoveObjectFromRender(const std::shared_ptr<Object>& object,
                                           const std::shared_ptr<Material>& material)
{
    if (!object || !material) return;

    auto it = materialObjectMap.find(material);
    if (it != materialObjectMap.end())
    {
        auto& objects = it->second;
        std::erase(objects, object);

        if (objects.empty())
        {
            materialObjectMap.erase(it);
        }
    }
}

void ObjectManager::UpdateObjectMaterial(const std::shared_ptr<Object>& object,
                                         const std::shared_ptr<Material>& oldMaterial,
                                         const std::shared_ptr<Material>& newMaterial)
{
    if (!object) return;

    if (oldMaterial)
    {
        RemoveObjectFromRender(object, oldMaterial);
    }

    if (newMaterial)
    {
        AddObjectToRender(object);
    }
}

std::shared_ptr<Object> ObjectManager::AddEmpty(std::string& name)
{
    auto object = std::make_shared<Object>(Engine::GUID::Generate(), name, glm::vec3(0),
                                           glm::vec3(0), glm::vec3(1), true);
    AddObject(object);
    return object;
}

void ObjectManager::CreatePrimitive(Engine::GUID guid)
{
    std::string name = "Primitive";
    auto primitiveObject = AddEmpty(name);
    primitiveObject->SetModel(std::static_pointer_cast<Model>(AssetLoader::GetAsset(guid)));
}

void ObjectManager::LoadObjectFromFile()
{
    std::filesystem::path projectRoot = std::filesystem::current_path();
    std::filesystem::path defaultDir = projectRoot / "Assets" / "Objects";
    std::string defaultDirStr = defaultDir.string();

    nfdchar_t* outPath = nullptr;
    const nfdchar_t* defaultPath = defaultDirStr.c_str();

    nfdresult_t result = NFD_OpenDialog("object", defaultPath, &outPath);
    if (result == NFD_OKAY)
    {
        std::filesystem::path absolutePath = outPath;
        std::filesystem::path relativePath = std::filesystem::relative(absolutePath, projectRoot);

        std::cout << "User selected file: " << absolutePath << std::endl;
        std::cout << "Relative path: " << relativePath << std::endl;

        // LoadObject(relativePath.string().c_str());
        free(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        std::cout << "User canceled file selection." << std::endl;
    }
    else
    {
        std::cerr << "Error: " << NFD_GetError() << std::endl;
    }
}
