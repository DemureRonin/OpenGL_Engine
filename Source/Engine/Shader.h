#pragma once
#include <string>
#include <ostream>


#include <fstream>
#include <iostream>

#include "glad/glad.h"
#include "glm/vec4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <sstream>

#include "Asset.h"
#include "DirectionalLight.h"

#include "ProgramObject.h"

class Prefab;
class Camera;
class Material;

class Shader : public ProgramObject, public Asset
{
private:

public:
    Shader(const std::string& filePath, Engine::GUID inGUID);
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
    void SetCameraUniforms(const Camera& camera);
    void SetObjectUniforms(const Camera& camera, const Prefab& object) const;
    void SetDirectionalLightUniforms(const DirectionalLight& dirLight) const;

    bool CompiledSuccessfully() const { return loadedSuccessfully; }
};
