#pragma once

#include "../imgui/imgui.h"
#include <filesystem>
#include <string>


class ProjectUIWindow
{
public:
    static void RenderAssetBrowser(const std::string& assetsPath);
};
