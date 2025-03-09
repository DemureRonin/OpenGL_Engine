#include "AssetLoader.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "../../Utils/json.h"

#include "../../Parsers/MaterialParser.h"
#include "../../Parsers/ObjectParser.h"

std::unordered_map<Engine::GUID, std::shared_ptr<Asset>> AssetLoader::assets{};
std::unordered_map<Engine::GUID, std::shared_ptr<Model>> AssetLoader::models{};
std::unordered_map<Engine::GUID, std::shared_ptr<Texture>> AssetLoader::textures{};
std::unordered_map<Engine::GUID, std::shared_ptr<Material>> AssetLoader::materials{};
std::unordered_map<Engine::GUID, std::shared_ptr<Shader>> AssetLoader::shaders{};
std::unordered_map<Engine::GUID, std::shared_ptr<Object>> AssetLoader::objects{};
std::string AssetLoader::projectRootPath;
std::string AssetLoader::projectAssetsPath;

static std::filesystem::path FindProjectRoot()
{
    std::filesystem::path path = std::filesystem::current_path();

    while (!path.empty())
    {
        if (std::filesystem::exists(path / "Assets"))
        {
            AssetLoader::projectRootPath = path.string();
            AssetLoader::projectAssetsPath = path.string() + "/Assets";
            return AssetLoader::projectRootPath;
        }
        path = path.parent_path();
    }

    return {};
}

void AssetLoader::LoadResources()
{
    Engine::GUID guid;

    guid = Engine::GUID::FromString(std::string(SHADER_UNLIT));
    shaders[guid] = std::make_shared<Shader>((projectRootPath + "/Resources/Unlit.glsl").c_str(), guid);
    assets[guid] = shaders[guid];

    guid = Engine::GUID::FromString(std::string(SHADER_LIT));
    shaders[guid] = std::make_shared<Shader>((projectRootPath + "/Resources/Lit.glsl").c_str(), guid);
    assets[guid] = shaders[guid];

    guid = Engine::GUID::FromString(std::string(SHADER_POSTPROCESSING));
    shaders[guid] = std::make_shared<Shader>((projectRootPath + "/Resources/PostProcessing.glsl").c_str(), guid);
    assets[guid] = shaders[guid];

    guid = Engine::GUID::FromString(std::string(TEXTURE_WHITE_1X1));
    textures[guid] = std::make_shared<Texture>(projectRootPath + "/Resources/1x1_white.jpeg", guid);
    assets[guid] = textures[guid];

    guid = Engine::GUID::FromString(std::string(TEXTURE_FLAT_NORMAL_1X1));
    textures[guid] = std::make_shared<Texture>(projectRootPath + "/Resources/1x1_flat_normal.png", guid);
    assets[guid] = textures[guid];


    guid = Engine::GUID::FromString(std::string(TEXTURE_MATERIAL_ERROR));
    textures[guid] = std::make_shared<Texture>(projectRootPath + "/Resources/200px-Debugempty.png", guid);
    assets[guid] = textures[guid];


    guid = Engine::GUID::FromString(std::string(MATERIAL_ERROR));
    materials[guid] =
        MaterialParser::ParseMaterial((projectRootPath + "/Resources/ErrorMaterial.mat").c_str(), guid);
    assets[guid] = materials[guid];

    guid = Engine::GUID::FromString(std::string(MATERIAL_LIT));
    materials[guid] =
        MaterialParser::ParseMaterial((projectRootPath + "/Resources/LitMaterial.mat").c_str(), guid);
    assets[guid] = materials[guid];

    guid = Engine::GUID::FromString(std::string(MATERIAL_UNLIT));
    materials[guid] =
        MaterialParser::ParseMaterial((projectRootPath + "/Resources/UnlitMaterial.mat").c_str(), guid);
    
    assets[guid] = materials[guid];

    guid = Engine::GUID::FromString(std::string(VIEWPORT_RENDER_QUAD));
    models[guid] = std::make_shared<Model>(projectRootPath + "/Resources/quad.obj", guid);
    assets[guid] = models[guid];


    guid = Engine::GUID::FromString(std::string(PRIMITIVE_CUBE));
    std::string name = projectRootPath + "/Resources/cube.obj";
    models[guid] = std::make_shared<Model>(name.c_str(), guid);
    assets[guid] = models[guid];

    guid = Engine::GUID::FromString(std::string(PRIMITIVE_SPHERE));
    name = projectRootPath + "/Resources/sphere.obj";
    models[guid] = std::make_shared<Model>(name.c_str(), guid);
    assets[guid] = models[guid];

    guid = Engine::GUID::FromString(std::string(PRIMITIVE_PLANE));
    name = projectRootPath + "/Resources/plane.obj";
    models[guid] = std::make_shared<Model>(name.c_str(), guid);
    assets[guid] = models[guid];
}

void AssetLoader::LoadAssets()
{
    FindProjectRoot();
    LoadResources();

    const std::string directoryPath = projectAssetsPath;
    if (!std::filesystem::exists(directoryPath) || !std::filesystem::is_directory(directoryPath))
    {
        std::cerr << "Directory not found: " << directoryPath << std::endl;
        return;
    }
    std::vector<std::pair<Engine::GUID, std::string>> shaderFiles;
    std::vector<std::pair<Engine::GUID, std::string>> textureFiles;
    std::vector<std::pair<Engine::GUID, std::string>> materialFiles;
    std::vector<std::pair<Engine::GUID, std::string>> modelFiles;
    std::vector<std::pair<Engine::GUID, std::string>> objectFiles;


    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
    {
        if (!entry.is_regular_file()) continue;
        std::string extension = entry.path().extension().string();
        if (entry.path().extension() == ".meta")
        {
            continue;
        }
        std::string assetFilePath = entry.path().string();
        std::string metaFilePath = assetFilePath + ".meta";

        if (!std::filesystem::exists(metaFilePath))
        {
            CreateMetaFile(metaFilePath.c_str(), entry.path().filename().string().c_str());
        }

        Engine::GUID guid = Engine::GUID::FromString(ReadGUIDFromMetaFile(metaFilePath.c_str()));
        if (assets.contains(guid))
        {
            continue;
        }
        auto it = Asset::extensionMap.find(extension);
        AssetType type = it != Asset::extensionMap.end() ? it->second : AssetType::Unknown;

        switch (type)
        {
        case AssetType::Shader: shaderFiles.emplace_back(guid, assetFilePath);
            break;
        case AssetType::Texture: textureFiles.emplace_back(guid, assetFilePath);
            break;
        case AssetType::Material: materialFiles.emplace_back(guid, assetFilePath);
            break;
        case AssetType::Model: modelFiles.emplace_back(guid, assetFilePath);
            break;
        case AssetType::Object: objectFiles.emplace_back(guid, assetFilePath);
            break;
        default: break;
        }
    }

    for (auto& [guid, path] : shaderFiles)
    {
        shaders[guid] = std::make_shared<Shader>(path.c_str(), guid);
        assets[guid] = shaders[guid];
    }

    for (auto& [guid, path] : textureFiles)
    {
        textures[guid] = std::make_shared<Texture>(path, guid);
        assets[guid] = textures[guid];
    }

    for (auto& [guid, path] : materialFiles)
    {
        materials[guid] = MaterialParser::ParseMaterial(path.c_str(), guid);
        assets[guid] = materials[guid];
    }

    for (auto& [guid, path] : modelFiles)
    {
        models[guid] = std::make_shared<Model>(path, guid);
        assets[guid] = models[guid];
    }

    for (auto& [guid, path] : objectFiles)
    {
        objects[guid] = ObjectParser::ParseObject(path.c_str(), guid);
        assets[guid] = objects[guid];
    }
}

void AssetLoader::Save()
{
    for (auto& [guid, obj] : objects)
    {
        ObjectParser::SaveObject(obj->GetAssetPath().c_str(), obj);
    }
    for (auto& [guid, mat] : materials)
    {
        MaterialParser::SaveMaterial(mat, mat->GetAssetPath().c_str());
    }
}


std::string AssetLoader::ReadGUIDFromMetaFile(const char* metaFilePath)
{
    std::ifstream metaFile(metaFilePath);

    if (!metaFile.is_open())
    {
        std::cerr << "Error: Could not open meta file: " << metaFilePath << std::endl;
        return std::string();
    }

    try
    {
        nlohmann::json metaData;
        metaFile >> metaData;
        metaFile.close();

        if (metaData.contains("GUID") && metaData["GUID"].is_string())
        {
            return metaData["GUID"].get<std::string>();
        }
        else
        {
            std::cerr << "Error: GUID not found or invalid in meta file: " << metaFilePath << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing meta file: " << metaFilePath << " - " << e.what() << std::endl;
    }

    return std::string();
}

void AssetLoader::CreateMetaFile(const char* metaFilePath, const char* metaFileName)
{
    std::cout << " (No meta file, creating one...)";

    Engine::GUID guid;
    do
    {
        guid = Engine::GUID::Generate();
    }
    while (assets.contains(guid));

    nlohmann::json metaData;
    metaData["GUID"] = guid.ToString();

    std::ofstream metaFile(metaFilePath);
    if (metaFile.is_open())
    {
        metaFile << metaData.dump(4);
        metaFile.close();
        std::cout << " [Created " << metaFileName << " with GUID: " << guid.ToString() << "]";
    }
    else
    {
        std::cerr << "Error: Could not create meta file: " << metaFileName << std::endl;
    }
    std::cout << std::endl;
}
