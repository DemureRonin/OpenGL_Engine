#include "TextureManager.h"
std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::textures{};

std::shared_ptr<Texture> TextureManager::LoadTexture(const std::string& filePath)
{
    auto existingTexture = GetTexture(filePath);
    if (existingTexture)
        return existingTexture;

    std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(filePath);
    if (!newTexture)
    {
        newTexture = std::make_shared<Texture>(WHITE_TEXTURE);
        std::cout << TEXTURE_MANAGER_LOG "Texture " << filePath << " failed to load" << '\n';
    }
    textures[filePath] = newTexture;
    return newTexture;
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& filePath)
{
    auto it = textures.find(filePath);
    if (it != textures.end())
    {
        std::cout << TEXTURE_MANAGER_LOG "Texture " << filePath << " exists, returning" << '\n';
        return it->second;
    }
    return nullptr;
}
