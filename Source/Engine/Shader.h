#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "Camera.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Object.h"
#include "ProgramObject.h"
#include "ShaderParams.h"
#include "glm/fwd.hpp"

#include <fstream>
#include <map>
#include <regex>

#include "glm/gtc/type_ptr.hpp"
#include "../Utils/json.h"
#include <sstream>


#define SHADER_LIT "Source/Shaders/Lit.glsl"
#define SHADER_UNLIT "Source/Shaders/Unlit.glsl"

class Shader : public ProgramObject
{
/*public:
    ShaderParams shaderParams;
    Shader(const char* filePath = SHADER_LIT);
    void Bind() const override;
    void Unbind() const override;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, glm::vec2 vec2) const;
    void SetVec3(const std::string& name, float v1, float v2, float v3) const;
    void SetVec3(const std::string& name, glm::vec3 vec3) const;
    void SetMat4(glm::mat4 mat4, std::string name) const;
    void SetVec4(const std::string& name, glm::vec4 vec4) const;
    void SetMaterialUniforms(const std::shared_ptr<Material>& material) const;
    void SetObjectUniforms(const Camera& camera, const Object& object) const;
    void SetDirectionalLightUniforms(const DirectionalLight& dirLight) const;
    static ShaderParams ParseShaderMaterialFloats(const std::string& filePath);
    static void SaveShaderParamsToJson(const ShaderParams& params, const std::string& filePath);

private:
    struct ShaderProgramSource
    {
        std::string vertex, fragment;
    };

    ShaderProgramSource ParseShader(const std::string& filePath);

    void CheckCompileErrors(unsigned int shader, std::string type);*/
};

#endif
