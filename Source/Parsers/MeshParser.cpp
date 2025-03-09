#include "MeshParser.h"

#include <fstream>

#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Utils/json.h"
const char* MeshParser::m_DebugName = "MESH_PARSER";

std::shared_ptr<Mesh> MeshParser::ParseMesh(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        ConsoleDebug::PrintFileError(m_DebugName, filePath, "");
        return nullptr;
    }
    nlohmann::json j;
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

    std::string fileName = j["model"].get<std::string>();
    Model model(fileName.c_str(),Engine::GUID::Generate() );

    std::shared_ptr<Mesh> mesh = model.meshes[0];
    std::string message = std::string(filePath) + " Loaded successfully";
    ConsoleDebug::PrintMessage(m_DebugName, message.c_str());
    return mesh;
}
