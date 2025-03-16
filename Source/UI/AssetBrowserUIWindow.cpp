#include "AssetBrowserUIWindow.h"

#include "IconsFontAwesome5.h"
#include "../Engine/Types.h"
#include "../Engine/Managers/AssetLoader.h"

AssetBrowserUIWindow::AssetBrowserUIWindow(const char* inName, Engine::UIID inUIID,
                                           const std::shared_ptr<UIManager>& inUIManager): UIWindow(
    inName, inUIID, inUIManager)
{
    assetsPath = AssetLoader::projectAssetsPath;
    currentPath = assetsPath;
}


void AssetBrowserUIWindow::RenderWindow()
{
    RenderPopUp();
    if (ImGui::Begin(windowName.c_str()))
    {
        if (currentPath != assetsPath)
        {
            if (ImGui::Button("< Back"))
            {
                currentPath = std::filesystem::path(currentPath).parent_path().string();
            }
        }

        ImGui::Separator();

        for (const auto& entry : std::filesystem::directory_iterator(currentPath))
        {
            std::string name = entry.path().filename().string();
            if (entry.path().extension() == ".meta")
                continue;

            if (entry.is_directory())
            {
                if (ImGui::Selectable((name + "/").c_str(), false))
                {
                    ImGui::SetItemDefaultFocus();
                    currentPath = entry.path().string();
                }
            }
            else
            {
                if (ImGui::Selectable(name.c_str(), false))
                {
                    selectedAssetPath = entry.path().string();
                    uiManager->UpdateInspectorWindows([this]() { RenderInspectorMaterialInfo(); });
                    uiManager->ResetHierarchyActiveObject();
                }

                if (entry.path().extension() == ".fbx" || entry.path().extension() == ".obj")
                {
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
                    {
                        std::string metaFilePath = entry.path().string() + ".meta";
                        auto GUID = AssetLoader::ReadGUIDFromMetaFile(metaFilePath.c_str());
                        ImGui::SetDragDropPayload("MODEL_PATH", GUID.c_str(), GUID.size() + 1);
                        ImGui::Text("Dragging: %s", name.c_str());
                        ImGui::EndDragDropSource();
                    }
                }
            }
        }
        ImGui::End();
    }
}

void AssetBrowserUIWindow::RenderInspectorMaterialInfo() const
{
    auto extention = std::filesystem::path(selectedAssetPath).filename().extension();
    if (extention != ".mat") return;

    std::string metaFilePath = std::filesystem::path(selectedAssetPath).string() + ".meta";
    auto GUID = AssetLoader::ReadGUIDFromMetaFile(metaFilePath.c_str());
    auto material = TYPEOF(Material)(AssetLoader::GetAsset(Engine::GUID::FromString(GUID)));


    if (material == nullptr) return;


    std::string name;
    if (material->shader != nullptr)
    {
        name = material->shader->name;
    }
    ImGui::Text("Material: %s", material->name.c_str());
    ImGui::Text("Shader: %s", name.c_str());

    for (auto& [name, value] : material->shaderParams->textureParameters)
    {
        ImGui::Text(name.c_str());
        ImGui::SameLine();
        ImGui::Text(":");
        ImGui::SameLine();
        ImGui::Text(value->name.c_str());
        ImGui::SameLine();
        if (ImGui::Button(std::string(ICON_FA_RECORD_VINYL + std::string("##") + value->name).c_str()))
        {
            ImGui::OpenPopup(std::string("Texture Selection Popup" + std::string("##") + value->name).c_str());
        }
        if (ImGui::BeginPopup(std::string("Texture Selection Popup" + std::string("##") + value->name).c_str()))
        {
            for (auto& it : AssetLoader::textures)
            {
                ImTextureID textureID = it.second->GetRendererID();
                ImGui::Image(textureID, ImVec2(32, 32));

                ImGui::SameLine();
                std::string label = it.second->name + "###" + it.first.ToString();
                if (ImGui::MenuItem(label.c_str()))
                {
                    value = it.second;
                }
            }

            ImGui::EndPopup();
        }
    }

    // Int Parameters (Clamp between 0 and 1, though int might not be ideal for this)
    for (auto& [name, value] : material->shaderParams->intParameters)
    {
        value = glm::clamp(value, 0, 1); // Ensure value stays in range
        ImGui::DragInt(name.c_str(), &value, 1, 0, 1); // Step = 1, range [0, 1]
    }

    // Float Parameters (Slow drag, range 0 - 1)
    for (auto& [name, value] : material->shaderParams->floatParameters)
    {
        ImGui::DragFloat(name.c_str(), &value, 0.001f, 0.0f, 1.0f, "%.4f"); // Step 0.001, more precise
    }

    // Vec2 Parameters (Slow drag, range 0 - 1)
    for (auto& [name, value] : material->shaderParams->vec2Parameters)
    {
        ImGui::DragFloat2(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
    }

    // Vec3 Parameters (Slow drag, range 0 - 1)
    for (auto& [name, value] : material->shaderParams->vec3Parameters)
    {
        ImGui::DragFloat3(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
    }

    // Vec4 Parameters (Slow drag, range 0 - 1)
    for (auto& [name, value] : material->shaderParams->vec4Parameters)
    {
        ImGui::DragFloat4(name.c_str(), &value[0], 0.001f, 0.0f, 1.0f, "%.4f");
    }
}
