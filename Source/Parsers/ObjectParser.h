#pragma once
#include <memory>

#include "MaterialParser.h"
#include "../Engine/Object.h"


class ObjectParser
{
public:
    static std::shared_ptr<Object> ParseObject(const char* filePath, Engine::GUID inGUID);
    static int SaveObject(const char* filePath, const std::shared_ptr<Object>& object);
    static glm::vec3 ParseVec3(const json& j, const std::string& key);

private:
    static const char* m_DebugName;
};
