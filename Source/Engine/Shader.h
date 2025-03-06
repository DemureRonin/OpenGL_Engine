#pragma once
#include <string>
#include <ostream>


#include <fstream>
#include <iostream>

#include "glad/glad.h"
#include "glm/vec4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <sstream>

#include "DirectionalLight.h"

#include "ProgramObject.h"

#define SHADER_LIT "Source/Shaders/Lit.glsl"
#define SHADER_UNLIT "Source/Shaders/Unlit.glsl"

class Object;
class Camera;
class Material;

class Shader : public ProgramObject
{
private:
    std::string m_filePath;

public:
    //  std::shared_ptr<ShaderParams> shaderParams;
    Shader(const char* filePath = SHADER_LIT);
    std::string GetFilePath() { return m_filePath; };
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

private:
    struct ShaderProgramSource
    {
        std::string vertex, fragment;
    };

    ShaderProgramSource ParseShader(const std::string& filePath);

    void CheckCompileErrors(unsigned int shader, std::string type);
};
