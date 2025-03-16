#include "SceneParser.h"

#include <fstream>
#include <iostream>

#include "../Utils/json.h"
#include "../Engine/EngineID/GUID.h"
#include "../Engine/Prefab.h"
#include "../Engine/Types.h"
#include "../Engine/Managers/AssetLoader.h"
#include "glm/vec3.hpp"

std::vector<std::shared_ptr<Prefab>> SceneParser::ParseScene(const char* assetPath)
{
    std::vector<std::shared_ptr<Prefab>> objects;
    std::ifstream file(assetPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open scene file: " << assetPath << std::endl;
        return objects;
    }

    nlohmann::json sceneJson;
    try
    {
        file >> sceneJson;
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing scene file: " << e.what() << std::endl;
        return objects;
    }

    int index = 1;
    
    for (const auto& obj : sceneJson["objects"])
    {
        Engine::GUID prefabGUID = Engine::GUID::Generate();
        Engine::GUID materialGUID = Engine::GUID::Generate();
        Engine::GUID modelGUID = Engine::GUID::Generate();
        std::string name = obj["name"];


        glm::vec3 position = {obj["position"][0], obj["position"][1], obj["position"][2]};
        glm::vec3 rotation = {obj["rotation"][0], obj["rotation"][1], obj["rotation"][2]};
        glm::vec3 scale = {obj["scale"][0], obj["scale"][1], obj["scale"][2]};

        auto prefab = std::make_shared<Prefab>(Engine::GUID::Generate(), name, position, rotation, scale);
        // prefab->SetModel(TYPEOF(Model)(AssetLoader::GetAsset(modelGUID)));
        //prefab->SetMaterial(TYPEOF(Material)(AssetLoader::GetAsset(materialGUID)));

        objects.push_back(prefab);
    }

    return objects;
}
