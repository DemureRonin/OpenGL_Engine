#include "TextureManager.h"
std::vector<std::shared_ptr<Texture>> TextureManager::textures {};
std::shared_ptr<Texture> TextureManager::LoadTexture(const std::string& filePath)
{
    for (size_t i = 0; i < textures.size(); i++)
    {
        if (textures[i]->m_FilePath == filePath)
        {
            std::cout << TEXTURE_MANAGER_LOG "Texture " << filePath << " exists, returning" << '\n';
            return textures[i];
        }
    }
    std::cout << TEXTURE_MANAGER_LOG "Texture " << filePath << " doesn't exist, loading" << '\n';
    auto texture = std::make_shared<Texture>(filePath);
    if (!texture->IsLoaded())
    {
        texture.reset();
        std::cerr << TEXTURE_MANAGER_LOG "\033[31mFailed to load texture " << filePath << ", falling back to white\033[0m" << '\n';
        texture = std::make_shared<Texture>(WHITE_TEXTURE);
    }
    textures.push_back(texture);
    std::cout << TEXTURE_MANAGER_LOG "Texture " << filePath << " loaded" << '\n';
    return texture;
}
