#include "ObjectParser.h"

#include "MaterialParser.h"
#include "MeshParser.h"
#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Engine/ConsoleDebug/DebugUtils.h"
#include "../Engine/Managers/AssetLoader.h"

const char* ObjectParser::m_DebugName = "OBJECT_PARSER";

std::shared_ptr<Object> ObjectParser::CreateErrorObject()
{
    /*std::string name = "ERROR";
    std::shared_ptr<Object> errorObject = std::make_shared<Object>(name, glm::vec3(0), glm::vec3(0), glm::vec3(1),
                                                                   false);
    return errorObject;*/
    return nullptr;
}


std::shared_ptr<Object> ObjectParser::ParseObject(const char* filePath, Engine::GUID inGUID)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        ConsoleDebug::PrintFileError(m_DebugName, filePath, "Falling back to default object");
        //  object = ObjectParser::CreateErrorObject();
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

    std::string name = j["name"].get<std::string>();

    glm::vec3 position = glm::vec3(j["position"][0].get<float>(), j["position"][1].get<float>(),
                                   j["position"][2].get<float>());
    glm::vec3 rotation = glm::vec3(j["rotation"][0].get<float>(), j["rotation"][1].get<float>(),
                                   j["rotation"][2].get<float>());
    glm::vec3 scale = glm::vec3(j["scale"][0].get<float>(), j["scale"][1].get<float>(), j["scale"][2].get<float>());

    auto modelID = Engine::GUID::FromString(j["modelGUID"].get<std::string>());
    auto materialID = Engine::GUID::FromString(j["materialGUID"].get<std::string>());

    std::shared_ptr<Object> createdObject = std::make_shared<Object>(inGUID, name, position, rotation, scale, true,
                                                                     filePath);
    auto objectModel = std::static_pointer_cast<Model>(AssetLoader::GetAsset(modelID));


    auto objectMat = std::static_pointer_cast<Material>(AssetLoader::GetAsset(materialID));

    if (objectModel != nullptr)
        createdObject->SetModel(objectModel);
    if (objectMat != nullptr)
        createdObject->SetMaterial(objectMat);

    std::string message = std::string(filePath) + " Loaded Successfully";
    ConsoleDebug::PrintMessage(m_DebugName, message.c_str());

    return createdObject;
}

int ObjectParser::SaveObject(const char* filePath, const std::shared_ptr<Object>& object)
{
    /*if (!object->loadedSuccessfully)
    {
        ConsoleDebug::PrintError(m_DebugName, "Could not save object");
        return 1;
    }
    nlohmann::json jsonObject = {
        {"name", object->name},
        {"position", {object->transform.position.x, object->transform.position.y, object->transform.position.z}},
        {"rotation", {object->transform.rotation.x, object->transform.rotation.y, object->transform.rotation.z}},
        {"scale", {object->transform.scale.x, object->transform.scale.y, object->transform.scale.z}},

    };
    if (object->mesh != nullptr)
        jsonObject.push_back({"mesh", " "});
    else jsonObject.push_back({"mesh", ""});
    
    if (object->material != nullptr)
        jsonObject.push_back({"material", object->material->GetFilePath()});
    else jsonObject.push_back({"material", ""});


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
    }*/

    return 0;
}
