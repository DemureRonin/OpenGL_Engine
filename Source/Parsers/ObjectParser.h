#pragma once
#include <memory>
#include "../Engine/Object.h"


class ObjectParser
{
public:
    static std::shared_ptr<Object> CreateErrorObject();
    static int LoadObject(const char* filePath, std::shared_ptr<Object>& object);
    static int SaveObject(const char* filePath, const std::shared_ptr<Object>& object);

private:
    static const char* m_DebugName;
};
