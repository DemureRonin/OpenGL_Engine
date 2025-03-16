#include "ObjectParser.h"
#include "MaterialParser.h"
#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Engine/ConsoleDebug/DebugUtils.h"
#include "../Engine/Managers/AssetLoader.h"

const char* ObjectParser::m_DebugName = "OBJECT_PARSER";


glm::vec3 ObjectParser::ParseVec3(const json& j, const std::string& key)
{
    if (j.contains(key) && j[key].is_array() && j[key].size() == 3)
    {
        return {
            j[key][0].get<float>(),
            j[key][1].get<float>(),
            j[key][2].get<float>()
        };
    }
    return glm::vec3(0.0f);
}

std::shared_ptr<Prefab> ObjectParser::ParseObject(const char* filePath, Engine::GUID inGUID)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        ConsoleDebug::PrintFileError(m_DebugName, filePath, "Falling back to default object");
        return nullptr;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        ConsoleDebug::PrintFileError(m_DebugName, filePath, e.what());
        file.close();
        return nullptr;
    }
    file.close();

   
    std::string name = j.value("name", "Unnamed Object");
    glm::vec3 position = ParseVec3(j, "position");
    glm::vec3 rotation = ParseVec3(j, "rotation");
    glm::vec3 scale = ParseVec3(j, "scale");

 
    Engine::GUID modelID = Engine::GUID::FromString(j.value("modelGUID", ""));
    Engine::GUID materialID = Engine::GUID::FromString(j.value("materialGUID", ""));

    auto createdObject = std::make_shared<Prefab>(inGUID, name, position, rotation, scale, filePath);

  
    auto objectModel = std::static_pointer_cast<Model>(AssetLoader::GetAsset(modelID));
    auto objectMat = std::static_pointer_cast<Material>(AssetLoader::GetAsset(materialID));

    //if (objectModel)
      //  createdObject->SetMesh(objectModel);
    if (objectMat)
        createdObject->SetMaterial(objectMat);

    std::string message = std::string(filePath) + " Loaded Successfully";
    ConsoleDebug::PrintMessage(m_DebugName, message.c_str());

    return createdObject;
}

int ObjectParser::SaveObject(const char* filePath, const std::shared_ptr<Prefab>& object)
{
    if (!object->loadedSuccessfully)
    {
        ConsoleDebug::PrintError(m_DebugName, "Could not save object");
        return 1;
    }

   
    json jsonObject = {
        /*{"GUID", object->GetGUID().ToString()},
        {"modelGUID", object->mesh ? object->mesh->GetGUID().ToString() : ""},
        {"materialGUID", object->material ? object->material->GetGUID().ToString() : ""},
        {"name", object->name},
        {"position", {object->transform.position.x, object->transform.position.y, object->transform.position.z}},
        {"rotation", {object->transform.rotation.x, object->transform.rotation.y, object->transform.rotation.z}},
        {"scale", {object->transform.scale.x, object->transform.scale.y, object->transform.scale.z}}*/
    };

    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << jsonObject.dump(2);
        std::string message = std::string(filePath) + " Saved successfully";
        ConsoleDebug::PrintMessage(m_DebugName, message.c_str());
        file.close();
    }
    else
    {
        ConsoleDebug::PrintFileError(m_DebugName, filePath, "Could not save object");
        return 1;
    }

    return 0;
}
