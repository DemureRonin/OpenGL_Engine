#pragma once
#include <map>

#include "Texture.h"
#include <glm/glm.hpp>
struct ShaderParams
{
    std::string shaderIDString;
    std::map<std::string, int> intParameters;
    std::map<std::string, float> floatParameters;
    std::map<std::string, glm::vec2> vec2Parameters;
    std::map<std::string, glm::vec3> vec3Parameters;
    std::map<std::string, glm::vec4> vec4Parameters;
    std::map<std::string, std::shared_ptr<Texture>> textureParameters;
};
