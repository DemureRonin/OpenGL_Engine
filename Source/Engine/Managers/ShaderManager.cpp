#include "ShaderManager.h"
#include "../Shader.h"
#include <filesystem>
std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderManager::shaders{};

void ShaderManager::LoadShader(const std::string& filePath)
{
    if (shaders.find(filePath) != shaders.end())
    {
        std::cout << "Shader " << filePath << " already loaded, skipping.\n";
        return;
    }

    auto shader = std::make_shared<Shader>(filePath.c_str());
    shaders[filePath] = shader;
}

void ShaderManager::LoadShaders(const std::string& directory)
{
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
    {
        std::cerr << "Directory does not exist: " << directory << '\n';
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".glsl")
        {
            std::string filePath = entry.path().generic_string(); // Ensures forward slashes
            std::string relativePath = std::filesystem::relative(filePath, std::filesystem::current_path()).generic_string();

            LoadShader(relativePath);
        }
    }
}


std::shared_ptr<Shader> ShaderManager::GetShader(const std::string& filePath)
{
    auto it = shaders.find(filePath);
    if (it != shaders.end())
    {
        return it->second;
    }
    return nullptr;
}
