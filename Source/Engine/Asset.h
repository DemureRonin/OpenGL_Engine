#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "../Engine/EngineID/GUID.h"

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


class Asset
{
public:
    Asset(std::string assetPath, AssetType assetType, Engine::GUID guid);
    virtual ~Asset() = default;

    static const char* ToString(AssetType type);
    const std::string& GetAssetPath() const { return m_AssetPath; }
    Engine::GUID GetGUID() const { return m_GUID; }
    AssetType GetAssetType() const { return m_AssetType; }
    
    static const std::unordered_map<std::string, AssetType> extensionMap;
private:
    Engine::GUID m_GUID;
    std::string m_AssetPath;
    AssetType m_AssetType;
};
