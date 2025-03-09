#pragma once

#include <optional>
#include <iostream>
#include <unordered_map>

#include "../../Engine/GUID.h"
#include "../../Engine/Asset.h"
#include "../../Engine/Model.h"

#define SHADER_UNLIT_GUID "00000000-0000-0000-0000-000000000001"
#define TEXTURE_WHITE_1X1 "00000000-0000-0000-0000-000000000002"
#define TEXTURE_MATERIAL_ERROR "00000000-0000-0000-0000-000000000003"
#define MATERIAL_ERROR "00000000-0000-0000-0000-000000000004"
#define VIEWPORT_RENDER_QUAD "00000000-0000-0000-0000-000000000005"

class AssetLoader
{
private:
    static std::string ReadGUIDFromMetaFile(const char* metaFilePath);
    static void CreateMetaFile(const char* metaFilePath, const char* metaFileName);
    static void LoadResources();

public:
    static std::unordered_map<Engine::GUID, std::shared_ptr<Asset>> assets;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Model>> models;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Texture>> textures;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Material>> materials;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Shader>> shaders;
    static std::unordered_map<Engine::GUID, std::shared_ptr<Object>> objects;

    static void LoadAssets();
    static std::shared_ptr<Asset> GetAsset(Engine::GUID guid) { return assets[guid]; }
};
