#pragma once

#include <optional>
#include <iostream>
#include <unordered_map>

#include "../../Engine/EngineID/GUID.h"
#include "../../Engine/Asset.h"
#include "../../Engine/Model.h"

#define SHADER_UNLIT "00000000-0000-0000-0000-000000000001"
#define SHADER_LIT "00000000-0000-0000-0000-000000000002"
#define TEXTURE_WHITE_1X1 "00000000-0000-0000-0000-000000000003"
#define TEXTURE_FLAT_NORMAL_1X1 "00000000-0000-0000-0000-000000000004"
#define TEXTURE_MATERIAL_ERROR "00000000-0000-0000-0000-000000000005"
#define MATERIAL_ERROR "00000000-0000-0000-0000-000000000006"
#define MATERIAL_LIT "00000000-0000-0000-0000-000000000007"
#define VIEWPORT_RENDER_QUAD "00000000-0000-0000-0000-000000000008"
#define SHADER_POSTPROCESSING "00000000-0000-0000-0000-000000000009"
#define PRIMITIVE_PLANE "00000000-0000-0000-0000-00000000000A"
#define PRIMITIVE_SPHERE "00000000-0000-0000-0000-00000000000B"
#define PRIMITIVE_CUBE "00000000-0000-0000-0000-00000000000C"
#define MATERIAL_UNLIT "00000000-0000-0000-0000-00000000000D"

class AssetLoader
{
private:
    static std::string ReadGUIDFromMetaFile(const char* metaFilePath);
    static void CreateMetaFile(const char* metaFilePath, const char* metaFileName);
    static void LoadResources();

public:
    static std::string projectRootPath;
    static std::string projectAssetsPath;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Asset>> assets;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Model>> models;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Texture>> textures;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Material>> materials;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Shader>> shaders;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Object>> objects;

    static void LoadAssets();
    static std::shared_ptr<Asset> GetAsset(Engine::GUID guid) { return assets[guid]; }
    static void Save();
};
