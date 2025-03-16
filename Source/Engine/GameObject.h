#pragma once
#include "Transform.h"

#include "Model.h"
#include "Material.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject(std::string& name, glm::vec3 position = glm::vec3(0),
               glm::vec3 rotation = glm::vec3(0),
               glm::vec3 scale = glm::vec3(1),
               const std::string& filePath = ""): name(name), transform(position, rotation, scale)

    {
        transform.ApplyTranslation(glm::mat4(1.0f));
    }


    std::shared_ptr<GameObject> GetSharedPtr()
    {
        return shared_from_this();
    }

    std::string name;

    Transform transform;
    std::shared_ptr<Model> model = nullptr;
    std::shared_ptr<Material> material = nullptr;
    
    std::shared_ptr<Prefab> parent;
    std::vector<std::shared_ptr<Prefab>> children;

    void Draw();

    void SetModel(const std::shared_ptr<Model>& newModel);

    void SetMaterial(const std::shared_ptr<Material>& newMaterial);
};
