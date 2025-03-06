#include "SceneWindow.h"

#include <iostream>
#include <ostream>

#include "Toolbar.h"
ImVec2 SceneWindow::windowSize = ImVec2(0, 0);
ImVec2 SceneWindow::dddd = ImVec2(0, 0);

void SceneWindow::InitializeSceneWindow(int x, int y)
{
    windowSize = ImVec2(x, y);
}

void SceneWindow::RenderSceneWindow(int& width, int& height, int& posX, int& posY)
{
    ImGui::SetNextWindowPos(ImVec2(posX, 21 + posY));
    std::cout << "X"<< Toolbar::toolBarHeight + posY << std::endl;
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 prevSize = ImGui::GetContentRegionAvail();
    ImVec2 contentPos = ImGui::GetCursorScreenPos();
    ImGuiStyle& style = ImGui::GetStyle();
    float topBorderHeight = ImGui::GetFontSize() + style.FramePadding.y * 2 + style.WindowBorderSize;

    //std::cout << "Top border height: " << topBorderHeight << std::endl;

    float rightBorderWidth = style.WindowBorderSize;
    

   // std::cout << "Right border width: " << rightBorderWidth << std::endl;
    width = prevSize.x + 16;
    height = prevSize.y + 37;
    posX = contentPos.x - 8;
    posY = contentPos.y - 50;
   // std::cout <<"W"<< width << "H" << width << std::endl;
    
    ImGui::End();
    ImGui::PopStyleColor();
}
