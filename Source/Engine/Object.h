#pragma once

#include "Transform.h"

#include "Model.h"
#include "Material.h"


class Object : public std::enable_shared_from_this<Object>, public Asset
{
private:


public:
    Object(Engine::GUID inGUID, std::string& name, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0),
           glm::vec3 scale = glm::vec3(1), bool loadedSuccessfully = true, const std::string& filePath = "")
        : Asset(filePath, AssetType::Object, inGUID), name(name), transform(position, rotation, scale),
          loadedSuccessfully(loadedSuccessfully)
    {
        transform.ApplyTranslation();
    }

    

    std::shared_ptr<Object> GetSharedPtr()
    {
        return shared_from_this();
    }

    std::string name = "Object";

    Transform transform;
    std::shared_ptr<Model> model = nullptr;
    std::shared_ptr<Material> material = nullptr;
    bool loadedSuccessfully;
 

    void Draw();

    void SetModel(const std::shared_ptr<Model>& newModel);

    void SetMaterial(const std::shared_ptr<Material>& newMaterial);
};
