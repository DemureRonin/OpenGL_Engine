#pragma once
#include "Camera.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Object.h"
#include "Shader.h"

class LitShader
{
public:
    LitShader()
    {
        shader = Shader(SHADER_LIT);
        shader.Bind();
    }

    Shader shader;

    void SetDirectionalLightUniforms(const DirectionalLight& directionalLight) const
    {
        shader.SetVec3("directionalLight.direction", directionalLight.direction);
        shader.SetVec3("directionalLight.ambient", directionalLight.ambient);
        shader.SetVec3("directionalLight.diffuse", directionalLight.diffuse);
        shader.SetVec3("directionalLight.specular", directionalLight.specular);
    }

    void SetMaterialUniforms(const Material& material) const
    {
        shader.SetFloat("material.shininess", material.shininess);
        shader.SetInt("material.texture", 0);
        shader.SetVec4("material.tint",  material.tint);
    }

    void SetObjectUniforms(const Camera& camera, const Object &object)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1920 / (float)1080, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 Mmat4 = object.transform.modelMatrix;
        glm::mat4 Vmat4 = view;
        glm::mat4 MVmat4 = view * Mmat4;
        glm::mat4 MVPmat4 = projection * MVmat4;
        
        shader.SetMat4(Mmat4, "Mmat4");
        shader.SetMat4(Vmat4, "Vmat4");
        shader.SetMat4(MVmat4, "MVmat4");
        shader.SetMat4(MVPmat4, "MVPmat4");
        shader.SetVec3("cameraPosition", camera.Position.x, camera.Position.y, camera.Position.z);
    }
};
