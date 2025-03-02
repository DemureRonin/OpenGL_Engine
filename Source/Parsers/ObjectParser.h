#pragma once
#include <memory>
#include "../Engine/Object.h"
#include "../Engine/LitShader.h"
class ObjectParser
{
public:
    static std::shared_ptr<Object> ParseObject(const char* filePath, LitShader& shader);
};
