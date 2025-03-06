#pragma once
#include <unordered_map>

#include "../Texture.h"
#include "glad/glad.h"
#define TEXTURE_MANAGER_LOG "[TEXTURE_MANAGER] "

class TextureManager
{
private:
    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

public:
    static std::shared_ptr<Texture> LoadTexture(const std::string& filePath);
    static std::shared_ptr<Texture> GetTexture(const std::string& filePath);
};
