#pragma once

#include "Transform.h"

#include "Model.h"
#include "Material.h"


class Prefab : public std::enable_shared_from_this<Prefab>, public Asset
{
private:


public:
    Prefab(Engine::GUID inGUID, const std::string& name, glm::vec3 position = glm::vec3(0),
           glm::vec3 rotation = glm::vec3(0),
           glm::vec3 scale = glm::vec3(1), const std::string& filePath = "")
        : Asset(filePath, AssetType::Object, inGUID), name(name), transform(position, rotation, scale)

    {
        transform.ApplyTranslation(glm::mat4(1.0f));
    }

    bool operator==(const Prefab& other) const
    {
        return GetGUID() == other.GetGUID();
    }


    std::shared_ptr<Prefab> GetSharedPtr()
    {
        return shared_from_this();
    }

    void SetParent(const std::shared_ptr<Prefab>& inParent);
    void AddChild(const std::shared_ptr<Prefab>& child);
    void ApplyTransformations();
    bool HasChildren() const { return !children.empty(); }
    bool HasParent() const { return parent != nullptr; }

    std::string name = "Object";

    Transform transform;
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Material> material = nullptr;
    std::shared_ptr<Prefab> parent = nullptr;
    std::vector<std::shared_ptr<Prefab>> children{};
    glm::mat4 objectMatrix = glm::mat4(1);

    void Draw() const;

    void SetMesh(const std::shared_ptr<Mesh>& newMesh);

    void SetMaterial(const std::shared_ptr<Material>& newMaterial);
};
