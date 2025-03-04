#pragma once
#include <memory>
#include "../Engine/Object.h"
#include "../Engine/LitShader.h"

class ObjectParser
{
public:
    static std::shared_ptr<Object> LoadObject(const char* filePath, LitShader& shader);
    static int SaveObject(const char* filePath, std::shared_ptr<Object> object);
};
