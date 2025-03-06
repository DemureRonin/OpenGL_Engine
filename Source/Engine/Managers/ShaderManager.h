#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Shader;

class ShaderManager
{
private:
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
    static void LoadShaders(const std::string& directory);
    static void LoadShader(const std::string& filePath);
    static std::shared_ptr<Shader> GetShader(const std::string& filePath);
};
