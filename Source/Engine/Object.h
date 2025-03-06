#pragma once
#include "Mesh.h"
#include "Transform.h"


class Object
{
private:
    std::string m_FilePath;
public:
    Object(std::string& name, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0),
           glm::vec3 scale = glm::vec3(1), bool loadedSuccessfully = true, std::string filePath = "")
        : m_FilePath(filePath), name(name), transform(position, rotation, scale), loadedSuccessfully(loadedSuccessfully)
    {
        transform.ApplyTranslation();
    }

    std::string name = "Object";
   
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    bool loadedSuccessfully;
    std::string GetFilePath() { return m_FilePath; }
    void Draw()
    {
        transform.ApplyTranslation();
        mesh->Draw();
    }

    void SetMesh(const std::shared_ptr<Mesh> newMesh)
    {
       
        this->mesh = newMesh;
    }

    void SetMaterial(const std::shared_ptr<Material> newMaterial)
    {
        
        this->material = newMaterial;
    }
};
