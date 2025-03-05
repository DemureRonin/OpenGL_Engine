#include "ObjectManager.h"
std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Object>>> ObjectManager::materialObjectMap{};

std::vector<std::shared_ptr<Object>> ObjectManager::object_hierarchy{};

void ObjectManager::AddObject(const std::shared_ptr<Object>& object)
{
    if (object != nullptr)
        object_hierarchy.push_back(object);
    if (object->material)
        ObjectManager::materialObjectMap[object->material].push_back(object);
}

void ObjectManager::LoadObject(const char* filename)
{
    std::shared_ptr<Object> object;
    ObjectParser::LoadObject(filename, object);
    AddObject(object);
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
        std::filesystem::path absolutePath = outPath; // Convert to filesystem path
        std::filesystem::path relativePath = std::filesystem::relative(absolutePath, projectRoot);

        std::cout << "User selected file: " << absolutePath << std::endl;
        std::cout << "Relative path: " << relativePath << std::endl;
        std::string relativePathStr = relativePath.string();
        LoadObject(relativePathStr.c_str());
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

void ObjectManager::AddEmpty(std::string& name)
{
    std::shared_ptr<Object> object = std::make_shared<Object>(name, glm::vec3(0), glm::vec3(0), glm::vec3(1),
                                                              true);
    object_hierarchy.push_back(object);
}

void ObjectManager::InitMaterialMap()
{
    for (const auto& obj : ObjectManager::object_hierarchy)
    {
        if (obj->material != nullptr)
            ObjectManager::materialObjectMap[obj->material].push_back(obj);
    }
}
