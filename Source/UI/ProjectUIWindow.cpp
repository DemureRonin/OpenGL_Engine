#include "ProjectUIWindow.h"

void ProjectUIWindow::RenderAssetBrowser(const std::string& assetsPath)
{
    static std::string currentPath = assetsPath;
    if (ImGui::Begin("Asset Browser"))
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
            if (entry.is_directory())
            {
                if (ImGui::Selectable((name + "/").c_str(), false))
                {
                    currentPath = entry.path().string();
                }
            }
            else
            {
                ImGui::Text("%s", name.c_str());
            }
        }
    }
    ImGui::End();
}
