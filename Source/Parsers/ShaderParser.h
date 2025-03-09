#pragma once
#include <fstream>
#include <regex>

#include "../Engine/ShaderParams.h"
#include "../Utils/json.h"

class ShaderParser
{
public:
    struct ShaderProgramSource
    {
        std::string vertex, fragment;
    };

    static bool CheckCompileErrors(unsigned int shader, const std::string& type)
    {
        int success;
        char infoLog[1024];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- "
                          << std::endl;
                return false;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- "
                          << std::endl;
                return false;
            }
        }
        return true;
    }


    static ShaderProgramSource ParseShaderFile(const char* filePath)
    {
        enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 };
        ShaderType type = ShaderType::NONE;
        std::ifstream stream(filePath);
        std::string line;
        std::stringstream stringStream[2];
        while (std::getline(stream, line))
        {
            if (line.find("#pragma") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                stringStream[(int)type] << line << '\n';
            }
        }
        return {stringStream[0].str(), stringStream[1].str()};
    }

    static ShaderParams ParseShaderMaterialFloats(const std::string& filePath)
    {
        std::ifstream stream(filePath);
        std::string line;

        std::regex floatRegex(R"(\s*(float)\s+(\w+);)");
        std::regex vec2Regex(R"(\s*(vec2)\s+(\w+);)");
        std::regex vec3Regex(R"(\s*(vec3)\s+(\w+);)");
        std::regex vec4Regex(R"(\s*(vec4)\s+(\w+);)");
        std::regex intRegex(R"(\s*(int)\s+(\w+);)");
        std::regex sampler2DRegex(R"(\s*(sampler2D)\s+(\w+);)");

        ShaderParams params;
        if (stream.is_open())
        {
            bool insideMaterial = false;
            params.shaderIDString = filePath;
            while (std::getline(stream, line))
            {
                // Check if we entered the Material struct
                if (line.find("struct Material {") != std::string::npos)
                {
                    insideMaterial = true;
                    continue;
                }
                // Check if we exited the Material struct
                if (insideMaterial && line.find("};") != std::string::npos)
                {
                    insideMaterial = false;
                    break; // No need to parse further
                }
                // If inside Material, search for float parameters
                if (insideMaterial)
                {
                    std::smatch match;
                    if (std::regex_search(line, match, floatRegex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.floatParameters[name] = 0.0f;
                        std::cout << name << '\n';
                        continue; // Default value (can be updated later)
                    }
                    if (std::regex_search(line, match, sampler2DRegex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.textureParameters[name] = nullptr;
                        std::cout << name << '\n'; // Default value (can be updated later)
                        continue;
                    }
                    if (std::regex_search(line, match, intRegex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.intParameters[name] = 0;
                        std::cout << name << '\n';
                        continue; // Default value (can be updated later)
                    }
                    if (std::regex_search(line, match, vec2Regex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.vec2Parameters[name] = glm::vec2(0);
                        std::cout << name << '\n';
                        continue; // Default value (can be updated later)
                    }
                    if (std::regex_search(line, match, vec3Regex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.vec3Parameters[name] = glm::vec3(0);
                        std::cout << name << '\n';
                        continue; // Default value (can be updated later)
                    }
                    if (std::regex_search(line, match, vec4Regex))
                    {
                        std::string name = match[2]; // Capture float variable name
                        params.vec4Parameters[name] = glm::vec4(0);
                        std::cout << name << '\n';
                        continue; // Default value (can be updated later)
                    }
                }
            }
        }

        return params;
    }
};
