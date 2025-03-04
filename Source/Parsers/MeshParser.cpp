#include "MeshParser.h"
#include "../Utils/json.h"

std::shared_ptr<Mesh> MeshParser::ParseMesh(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "[MESH PARSER] Could not open the file" << filePath << '\n';
        return nullptr;
    }
    nlohmann::json j;
    file >> j; 
    file.close();

    std::string fileName = j["model"].get<std::string>();;
    Model model(fileName.c_str());
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(model.meshes[0]->vertices, model.meshes[0]->indices);
    mesh->m_FilePath = filePath;
    return mesh;
}
