#include "Asset.h"
#include <filesystem>

Asset::Asset(std::string assetPath, AssetType assetType, Engine::GUID guid) : m_GUID(guid),
                                                                              m_AssetPath(std::move(assetPath)),
                                                                              m_AssetType(assetType)
{
    name = std::filesystem::path(m_AssetPath).filename().string();
}

const char* Asset::ToString(AssetType type)
{
    switch (type)
    {
    case AssetType::Unknown: return "Unknown";
    case AssetType::Model: return "Model";
    case AssetType::Texture: return "Texture";
    case AssetType::Shader: return "Shader";
    case AssetType::Material: return "Material";
    case AssetType::Object: return "Object";
    case AssetType::Font: return "Font";
    case AssetType::Scene: return "Engine Scene";
    }
    return "ERRORTYPE";
}

const std::unordered_map<std::string, AssetType> Asset::extensionMap = {
    {".obj", AssetType::Model}, {".fbx", AssetType::Model},
    {".png", AssetType::Texture}, {".jpg", AssetType::Texture}, {".jpeg", AssetType::Texture},
    {".object", AssetType::Object},
    {".glsl", AssetType::Shader},
    {".mat", AssetType::Material},
    {".ttf", AssetType::Font},
    {".scene", AssetType::Scene},
};
