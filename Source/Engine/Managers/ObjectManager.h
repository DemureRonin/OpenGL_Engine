#pragma once
#include <map>
#include <memory>
#include <vector>
#include "../../Engine/Material.h"
#include "../../Engine/Object.h"

#include "../../Source/Parsers/ObjectParser.h"
#include "../../Source/nativefiledialog/nfd.h"
#include <filesystem>

class ObjectManager
{
public:
    static std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Object>>> materialObjectMap;
    static std::vector<std::shared_ptr<Object>> objectHierarchy;
    static void AddObject(const std::shared_ptr<Object>& object);
    static void AddObjectToRender(const std::shared_ptr<Object>& object);
    static void LoadObjectFromFile();
    static std::shared_ptr<Object> AddEmpty(std::string& name);
    static void RemoveObjectFromRender(const std::shared_ptr<Object>& object, const std::shared_ptr<Material>& material);
    static void CreatePrimitive(Engine::GUID guid);
    static void RemoveObject(const std::shared_ptr<Object>& object);
    static void UpdateObjectMaterial(const std::shared_ptr<Object>& object,
                                     const std::shared_ptr<Material>& oldMaterial,
                                     const std::shared_ptr<Material>& newMaterial);
};
