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
    static std::vector<std::shared_ptr<Object>> object_hierarchy;
    static void AddObject(const std::shared_ptr<Object>& object);
    static void AddObjectToRender(const std::shared_ptr<Object>& object);
    static void LoadObject(const char* filename);
    static void LoadObjectFromFile();
    static void AddEmpty(std::string& name);
    static void InitMaterialMap();

};
