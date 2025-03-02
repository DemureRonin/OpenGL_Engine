#include "ObjectParser.h"

#include "MaterialParser.h"
#include "MeshParser.h"

std::shared_ptr<Object> ObjectParser::ParseObject(const char* filePath, LitShader& shader)
{
    std::ifstream file(filePath); // Open the file for reading
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open the file");
    }

    json j;
    file >> j; // Deserialize JSON into the `json` object
    file.close();

    // Extract the data
    std::string name = j["name"].get<std::string>(); // Name as std::string
    glm::vec3 position; // Transform structure
    glm::vec3 rotation; // Transform structure
    glm::vec3 scale; // Transform structure

    // Parsing position, rotation, and scale as glm::vec3
    position = glm::vec3(j["position"][0].get<float>(), j["position"][1].get<float>(), j["position"][2].get<float>());
    rotation = glm::vec3(j["rotation"][0].get<float>(), j["rotation"][1].get<float>(), j["rotation"][2].get<float>());
    scale = glm::vec3(j["scale"][0].get<float>(), j["scale"][1].get<float>(), j["scale"][2].get<float>());

    std::string mesh = j["mesh"].get<std::string>(); // Mesh path as std::string
    std::string material = j["material"].get<std::string>(); // Material path as std::string

    std::shared_ptr<Object> object = std::make_shared<Object>(name, position, rotation, scale);
    std::shared_ptr<Mesh> objectMesh = MeshParser::ParseMesh(mesh.c_str());
    std::shared_ptr<Material> objectMaterial = MaterialParser::ParseMaterial(material.c_str(), shader);
    object->SetMesh(objectMesh);
    object->SetMaterial(objectMaterial);
    return object;
}
