#include "MaterialParser.h"
unsigned int MaterialParser::m_IDCount = 0;
std::shared_ptr<Material> MaterialParser::ParseMaterial(const char* filePath, LitShader& shader)
{
    std::vector<std::string> textures;

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << '\n';
        return nullptr;
    }

    json data;
    file >> data;

    for (const auto& texture : data["textures"])
    {
        textures.push_back(texture.get<std::string>());
    }
    glm::vec4 tint = glm::vec4(data["tint"][0].get<float>(), data["tint"][1].get<float>(), data["tint"][2].get<float>(),
                               data["tint"][3].get<float>());
    float shininess = data["shininess"].get<float>();

    std::vector<std::shared_ptr<Texture>> textures_loaded;
    if (textures.empty())
    {
        textures_loaded.push_back(TextureManager::LoadTexture(WHITE_TEXTURE));
    }
    else
    {
        for (const auto& texture : textures)
        {
            textures_loaded.push_back(TextureManager::LoadTexture(texture));
        }
    }

    std::shared_ptr<Material> mat = std::make_shared<Material>(shader.shader, textures_loaded, m_IDCount++);
    mat->tint = tint;
    mat->shininess = shininess;
    return mat;
}
