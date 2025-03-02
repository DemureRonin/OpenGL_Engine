#pragma once
#include <unordered_map>

#include "../Texture.h"
#include "glad/glad.h"
#define TEXTURE_MANAGER_LOG "[TEXTURE_MANAGER] "

class TextureManager
{
private:
    static std::vector<std::shared_ptr<Texture>> textures;

public:
    static std::shared_ptr<Texture> LoadTexture(const std::string& filePath);
};
