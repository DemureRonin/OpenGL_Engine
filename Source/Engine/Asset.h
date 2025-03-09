#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "../Engine/GUID.h"

class Asset;

enum class AssetType : std::uint8_t
{
    Unknown = 0,
    Model,
    Texture,
    Shader,
    Material,
    Object,
    Font
};


static const std::unordered_map<std::string, AssetType> extensionMap = {
    {".obj", AssetType::Model}, {".fbx", AssetType::Model},
    {".png", AssetType::Texture}, {".jpg", AssetType::Texture}, {".jpeg", AssetType::Texture},
    {".object", AssetType::Object},
    {".glsl", AssetType::Shader},
    {".mat", AssetType::Material},
    {".ttf", AssetType::Font},
};
static const std::unordered_map<AssetType, std::function<std::shared_ptr<Asset>(const std::string&)>> factoryMap = {

};

class Asset
{
public:
    Asset(std::string assetPath, AssetType assetType, Engine::GUID guid) : guid(guid),
                                                                           assetPath(std::move(assetPath)),
                                                                           assetType(assetType)
    {
    }

    Engine::GUID guid;
    std::string assetPath;
    AssetType assetType;
    virtual ~Asset() = default;

    static const char* ToString(AssetType type)
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
        }
        return "ERRORTYPE";
    }
};
