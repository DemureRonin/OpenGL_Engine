#pragma once
#include <memory>

#include "Asset.h"
#include "Prefab.h"

class Scene : public std::enable_shared_from_this<Scene>, public Asset
{
private:


public:
    std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Prefab>>> materialObjectMap;
    std::vector<std::shared_ptr<Prefab>> sceneObjects;
    std::vector<std::shared_ptr<Prefab>> rootObjects;
    Scene(const std::string& assetPath, Engine::GUID inGUID, const std::shared_ptr<Camera>& inCamera,
          const DirectionalLight& inDirLight);
    void ApplyObjectTransformations(const std::shared_ptr<Prefab>& obj) const;
    std::shared_ptr<Camera> camera;
    DirectionalLight dirLight;

    void Render() const;

    void AddObject(const std::shared_ptr<Prefab>& object);
    void RemoveObject(const std::shared_ptr<Prefab>& object);
    void AddObjectToRender(const std::shared_ptr<Prefab>& object);
    void RemoveObjectFromRender(const std::shared_ptr<Prefab>& object, const std::shared_ptr<Material>& material);
    std::shared_ptr<Prefab> CreatePrimitive(Engine::GUID guid);
    std::shared_ptr<Prefab> CreateEmpty(const std::string& inName);
    std::shared_ptr<Prefab> AddEmpty(const std::string& inName);
    void UpdateObjectMaterial(const std::shared_ptr<Prefab>& object,
                              const std::shared_ptr<Material>& oldMaterial,
                              const std::shared_ptr<Material>& newMaterial);
    std::shared_ptr<Scene> GetSharedPtr() { return shared_from_this(); }
    std::shared_ptr<Prefab> AddChild(const std::shared_ptr<Prefab>& parent, const std::string& inName = "Child");
    std::shared_ptr<Prefab> AddModel(const std::shared_ptr<Model>& model);
};
