#include "ObjectParser.h"

#include "MaterialParser.h"
#include "MeshParser.h"

std::shared_ptr<Object> ObjectParser::LoadObject(const char* filePath, LitShader& shader)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open the file");
    }

    json j;
    file >> j;
    file.close();


    std::string name = j["name"].get<std::string>();
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    position = glm::vec3(j["position"][0].get<float>(), j["position"][1].get<float>(), j["position"][2].get<float>());
    rotation = glm::vec3(j["rotation"][0].get<float>(), j["rotation"][1].get<float>(), j["rotation"][2].get<float>());
    scale = glm::vec3(j["scale"][0].get<float>(), j["scale"][1].get<float>(), j["scale"][2].get<float>());

    std::string mesh = j["mesh"].get<std::string>();
    std::string material = j["material"].get<std::string>();

    std::shared_ptr<Object> object = std::make_shared<Object>(name, position, rotation, scale);
    std::shared_ptr<Mesh> objectMesh = MeshParser::ParseMesh(mesh.c_str());
    std::shared_ptr<Material> objectMaterial = MaterialParser::ParseMaterial(material.c_str(), shader);
    if (objectMesh != nullptr)
        object->SetMesh(objectMesh);
    object->SetMaterial(objectMaterial);
    object->m_FilePath = filePath;
    return object;
}

int ObjectParser::SaveObject(const char* filePath, std::shared_ptr<Object> object)
{
    nlohmann::json jsonObject = {
        {"name", object->name},
        {"position", {object->transform.position.x, object->transform.position.y, object->transform.position.z}},
        {"rotation", {object->transform.rotation.x, object->transform.rotation.y, object->transform.rotation.z}},
        {"scale", {object->transform.scale.x, object->transform.scale.y, object->transform.scale.z}},
        {"mesh", object->mesh->m_FilePath},
        {"material", object->material->m_FilePath}
    };

    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << jsonObject.dump(2);
        std::cout << "LOAD";
        file.close();
    }

    return 0;
}
