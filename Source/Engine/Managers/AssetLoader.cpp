#include "AssetLoader.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "../../Utils/json.h"

#include "../../Parsers/MaterialParser.h"
#include "../../Parsers/ObjectParser.h"
#include "../Scene.h"
#include "../Types.h"
const char* AssetLoader::m_DebugName = "ASSET_LOADER";
std::unordered_map<Engine::GUID, std::shared_ptr<Asset>> AssetLoader::assets{};
std::unordered_map<Engine::GUID, std::shared_ptr<Model>> AssetLoader::models{};
std::unordered_map<Engine::GUID, std::shared_ptr<Texture>> AssetLoader::textures{};
std::unordered_map<Engine::GUID, std::shared_ptr<Material>> AssetLoader::materials{};
std::unordered_map<Engine::GUID, std::shared_ptr<Shader>> AssetLoader::shaders{};
std::unordered_map<Engine::GUID, std::shared_ptr<Prefab>> AssetLoader::objects{};
std::string AssetLoader::projectRootPath;
std::string AssetLoader::projectAssetsPath;
std::string AssetLoader::projectResourcesPath;;

template <typename T>
std::shared_ptr<Asset> AssetLoader::LoadAsset(const std::string& path, Engine::GUID guid)
{
    if constexpr (!std::is_base_of_v<Asset, T>)
    {
        ConsoleDebug::PrintError(m_DebugName, "Error: T must be derived from Asset");
        return nullptr;
    }
    auto asset = std::make_shared<T>(path, guid);
    if (!asset->loadedSuccessfully)
    {
        ConsoleDebug::PrintError(m_DebugName,
                                 (std::string("Asset ") + asset->GetAssetPath() +
                                     std::string(": loading error occured")).c_str());
    }
    else
    {
        ConsoleDebug::PrintMessage(m_DebugName, (std::string("Asset ") + asset->GetAssetPath() +
                                       std::string(": loaded successfully")).c_str());
    }
    return asset;
}


void AssetLoader::FindProjectRoot()
{
    std::filesystem::path path = std::filesystem::current_path();
    while (!path.empty())
    {
        if (std::filesystem::exists(path / "Assets") && std::filesystem::exists(path / "Resources"))
        {
            AssetLoader::projectRootPath = path.string();
            AssetLoader::projectAssetsPath = (path / "Assets").string();
            AssetLoader::projectResourcesPath = (path / "Resources").string();
            return;
        }
        path = path.parent_path();
    }
    ConsoleDebug::PrintError(m_DebugName, "Assets or Resources project folder missing");
    throw std::runtime_error("Assets or Resources project folder missing");
}


std::shared_ptr<Scene> AssetLoader::LoadScene(const std::string& path)
{
    /*if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        ConsoleDebug::PrintError(m_DebugName, "Scene file not found: ");
        return nullptr;
    }

    std::string metaFilePath = path + ".meta";
    if (!std::filesystem::exists(metaFilePath))
    {
        ConsoleDebug::PrintError(m_DebugName, "Missing meta file for scene: ");
        return nullptr;
    }

    Engine::GUID guid = Engine::GUID::FromString(ReadGUIDFromMetaFile(metaFilePath.c_str()));
    /*if (assets.contains(guid))
    {
        return std::static_pointer_cast<Scene>(assets[guid]);
    }#1#

    ConsoleDebug::PrintMessage(m_DebugName, "Scene GUID loaded: ");

    return TYPEOF(Scene)(LoadAsset<Scene>(path, guid));*/
    return nullptr;
}

void AssetLoader::LoadAssets()
{
    FindProjectRoot();
    // LoadDirectory(projectResourcesPath);
    LoadResources();
    LoadDirectory(projectAssetsPath);
}

void AssetLoader::LoadDirectory(const std::string& directory)
{
    const std::string directoryPath = directory;
    if (!std::filesystem::exists(directoryPath) || !std::filesystem::is_directory(directoryPath))
    {
        ConsoleDebug::PrintDirectoryError(m_DebugName, directoryPath.c_str(), " ");
        return;
    }
    ConsoleDebug::PrintMessage(m_DebugName, "Loading assets...");
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
        ConsoleDebug::PrintMessage(m_DebugName, std::string(std::string("Loading ") + entry.path().string()).c_str());
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
        shaders[guid] = std::static_pointer_cast<Shader>(LoadAsset<Shader>(path, guid));
        assets[guid] = shaders[guid];
    }

    for (auto& [guid, path] : textureFiles)
    {
        textures[guid] = std::static_pointer_cast<Texture>(LoadAsset<Texture>(path, guid));
        assets[guid] = textures[guid];
    }

    for (auto& [guid, path] : materialFiles)
    {
        materials[guid] = std::static_pointer_cast<Material>(LoadAsset<Material>(path, guid));
        assets[guid] = materials[guid];
    }

    for (auto& [guid, path] : modelFiles)
    {
        models[guid] = std::static_pointer_cast<Model>(LoadAsset<Model>(path, guid));
        assets[guid] = models[guid];
    }

    /*for (auto& [guid, path] : objectFiles)
    {
        objects[guid] = ObjectParser::ParseObject(path.c_str(), guid);
        assets[guid] = objects[guid];
    }*/
}

void AssetLoader::Save()
{
    /*for (auto& [guid, obj] : objects)
    {
        ObjectParser::SaveObject(obj->GetAssetPath().c_str(), obj);
    }
    for (auto& [guid, mat] : materials)
    {
        MaterialParser::SaveMaterial(mat, mat->GetAssetPath().c_str());
    }*/
}


std::string AssetLoader::ReadGUIDFromMetaFile(const char* metaFilePath)
{
    std::ifstream metaFile(metaFilePath);

    if (!metaFile.is_open())
    {
        ConsoleDebug::PrintFileError(m_DebugName, metaFilePath, " ");

        return {};
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
            ConsoleDebug::PrintError(m_DebugName, "GUID not found or invalid in meta file");
        }
    }
    catch (const std::exception& e)
    {
        std::string msg = "Error parsing meta file: " + std::string(e.what());
        ConsoleDebug::PrintError(m_DebugName, ("Error parsing meta file: " + std::string(e.what())).c_str());
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


    guid = Engine::GUID::FromString(std::string(TEXTURE_ERROR));
    textures[guid] = std::make_shared<Texture>(projectRootPath + "/Resources/200px-Debugempty.png", guid);
    assets[guid] = textures[guid];


    guid = Engine::GUID::FromString(std::string(MATERIAL_ERROR));
    materials[guid] =
        std::make_shared<Material>((projectRootPath + "/Resources/ErrorMaterial.mat").c_str(), guid);
    assets[guid] = materials[guid];

    guid = Engine::GUID::FromString(std::string(MATERIAL_LIT));
    materials[guid] =
        std::make_shared<Material>((projectRootPath + "/Resources/LitMaterial.mat").c_str(), guid);
    assets[guid] = materials[guid];

    guid = Engine::GUID::FromString(std::string(MATERIAL_UNLIT));
    materials[guid] =
        std::make_shared<Material>((projectRootPath + "/Resources/UnlitMaterial.mat").c_str(), guid);

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

    guid = Engine::GUID::FromString(std::string(MODEL_ERROR));
    name = projectRootPath + "/Resources/ErrorModel.fbx";
    models[guid] = std::make_shared<Model>(name.c_str(), guid);
    assets[guid] = models[guid];
}

void AssetLoader::CreateMetaFile(const char* metaFilePath, const char* metaFileName)
{
    ConsoleDebug::PrintMessage(m_DebugName, "Creating meta file");

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
        std::string msg = " [Created " + std::string(metaFileName) + " with GUID: " + guid.ToString() + "]";
        ConsoleDebug::PrintMessage(m_DebugName, msg.c_str());
    }
    else
    {
        ConsoleDebug::PrintError(m_DebugName, "Error: Could not create meta file ");
    }
}
