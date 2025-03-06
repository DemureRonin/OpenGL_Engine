#pragma once
#include <fstream>
#include <regex>

#include "ShaderParams.h"
#include "../Utils/json.h"

class ShaderParser
{
public:
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
            params.shaderFile = filePath;
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

    static void SaveShaderParamsToJson(const ShaderParams& params, const std::string& filePath)
    {
        nlohmann::json jsonData;
        jsonData["shaderFile"] = params.shaderFile;
        // Convert texture parameters
        jsonData["textureParams"] = nlohmann::json::array();
        for (std::map<std::string, std::shared_ptr<Texture>>::const_iterator it = params.textureParameters.begin(); it
             !=
             params.textureParameters.end(); ++it)
        {
            if (it->second)
            {
                // Check if texture exists
                jsonData["textureParams"].push_back({
                    {"name", it->first},
                    {"filePath", it->second->GetFilePath()} // Assuming Texture has GetFilePath() method
                });
            }
        }

        // Convert float parameters
        jsonData["floatParams"] = nlohmann::json::array();
        for (std::map<std::string, float>::const_iterator it = params.floatParameters.begin(); it != params.
             floatParameters.
             end(); ++it)
        {
            jsonData["floatParams"].push_back({
                {"name", it->first},
                {"value", it->second}
            });
        }

        // Convert int parameters
        jsonData["intParams"] = nlohmann::json::array();
        for (std::map<std::string, int>::const_iterator it = params.intParameters.begin(); it != params.intParameters.
             end();
             ++it)
        {
            jsonData["intParams"].push_back({
                {"name", it->first},
                {"value", it->second}
            });
        }

        // Convert vec2 parameters
        jsonData["vec2Params"] = nlohmann::json::array();
        for (std::map<std::string, glm::vec2>::const_iterator it = params.vec2Parameters.begin(); it != params.
             vec2Parameters.end(); ++it)
        {
            jsonData["vec2Params"].push_back({
                {"name", it->first},
                {"value", {it->second.x, it->second.y}}
            });
        }

        // Convert vec3 parameters
        jsonData["vec3Params"] = nlohmann::json::array();
        for (std::map<std::string, glm::vec3>::const_iterator it = params.vec3Parameters.begin(); it != params.
             vec3Parameters.end(); ++it)
        {
            jsonData["vec3Params"].push_back({
                {"name", it->first},
                {"value", {it->second.x, it->second.y, it->second.z}}
            });
        }

        // Convert vec4 parameters
        jsonData["vec4Params"] = nlohmann::json::array();
        for (std::map<std::string, glm::vec4>::const_iterator it = params.vec4Parameters.begin(); it != params.
             vec4Parameters.end(); ++it)
        {
            jsonData["vec4Params"].push_back({
                {"name", it->first},
                {"value", {it->second.x, it->second.y, it->second.z, it->second.w}}
            });
        }

        // Write to file
        std::ofstream file(filePath);
        if (file.is_open())
        {
            file << jsonData.dump(4); // Pretty print JSON with indentation
            file.close();
            std::cout << "Shader parameters saved to " << filePath << std::endl;
        }
        else
        {
            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        }
    }
};
