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
        shader = std::make_shared<Shader>(SHADER_LIT);
    }

    std::shared_ptr<Shader> shader;

    void SetDirectionalLightUniforms(const DirectionalLight& directionalLight) const
    {
        shader->SetVec3("directionalLight.direction", directionalLight.direction);
        shader->SetVec3("directionalLight.ambient", directionalLight.ambient);
        shader->SetVec3("directionalLight.diffuse", directionalLight.diffuse);
        shader->SetVec3("directionalLight.specular", directionalLight.specular);
    }

    void SetMaterialUniforms(const std::shared_ptr<Material>& material) const
    {
        shader->SetFloat("material.shininess", material->shininess);
        shader->SetVec4("material.tint", material->tint);
        for (unsigned int i = 0; i < material->textures.size(); i ++)
        {
            material->textures[i]->Bind(material->textures[i]->GetType());
            switch (material->textures[i]->GetType())
            {
            case ALBEDO:
                material->shader->SetInt("material.albedo", ALBEDO);
                break;
            case NORMAL:
                material->shader->SetInt("material.normal", NORMAL);
                break;
            case ROUGHNESS:
                material->shader->SetInt("material.roughness", ROUGHNESS);
                break;
            case METALLIC:
                material->shader->SetInt("material.metallic", METALLIC);
                break;
            case SPECULAR:
                material->shader->SetInt("material.specular", SPECULAR);
                break;
            }
        }
    }

    void SetObjectUniforms(const Camera& camera, const Object& object) const
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                static_cast<float>(1920) / static_cast<float>(1080), 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 Mmat4 = object.transform.modelMatrix;
        glm::mat4 Vmat4 = view;
        glm::mat4 MVmat4 = view * Mmat4;
        glm::mat4 MVPmat4 = projection * MVmat4;

        shader->SetMat4(Mmat4, "Mmat4");
        shader->SetMat4(Vmat4, "Vmat4");
        shader->SetMat4(MVmat4, "MVmat4");
        shader->SetMat4(MVPmat4, "MVPmat4");
        shader->SetVec3("cameraPosition", camera.Position.x, camera.Position.y, camera.Position.z);
    }
};
