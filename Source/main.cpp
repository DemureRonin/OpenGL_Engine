#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>

#include "InputProcessor.h"

#include "Engine/PostProcessing.h"
#include "Engine/Buffers/FBO/FrameBuffer.h"
#include "Engine/Buffers/RBO/RenderBufferObject.h"

#include "Engine/Initialization/GLADInitializer.h"
#include "Engine/Initialization/GLFWInitializer.h"
#include "Engine/Initialization/ImGUIInitializer.h"
#include "Engine/Managers/ObjectManager.h"
#include "Engine/Managers/ShaderManager.h"
#include "Engine/Time/Time.h"
#include "nativefiledialog/nfd.h"
#include "Utils/Primitives/CubePositions.h"
#include "Parsers/MaterialParser.h"
#include "Parsers/MeshParser.h"

#include "Parsers/ObjectParser.h"
#include "UI/DirectionalLightUIWindow.h"
#include "UI/HierarchyUIWindow.h"
#include "UI/MaterialUIWindow.h"

#include "UI/ObjectUIWindow.h"
#include "UI/RendererUIWindow.h"
#include "UI/SceneWindow.h"
#include "UI/Toolbar.h"
#include "Utils/Colors.h"
void SetModernDarkTheme();

int main()
{
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    camera->aspectX = (width);
    camera->aspectY = (height);

    InputProcessor::InitCallbacks(window, camera);

    ImGuiIO io;

    ImGUIInitializer::InitImGUI(window, io);
    io.Fonts->AddFontFromFileTTF("Assets/Fonts/0xProtoNerdFontMono-Regular.ttf", 15.0f);

    if (GLADInitializer::InitGLAD()) return -1;

    Renderer::EnableDepthTest(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DirectionalLight dirLight;

    ShaderManager::LoadShaders("Source/Shaders");


    ObjectManager::LoadObject("Assets/Objects/Object.object");
    // ObjectManager::LoadObject("Assets/Objects/Object1.object");
    //ObjectManager::LoadObject("Assets/Objects/Object2.object");

    PostProcessing postProcessing = PostProcessing();
    SetModernDarkTheme();
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.3f;
    ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg].w = 0.3f;
    SceneWindow::InitializeSceneWindow(width, height - 100);


    int x, y;
    glfwGetFramebufferSize(window, &x, &y);
    y -= 21;
    int posX = 0, posY = 0;
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        ImGUIInitializer::NewFrame();

        SceneWindow::RenderSceneWindow(x, y, posX, posY);

        camera->aspectX = (x);
        camera->aspectY = (y);
        // std::cout << camera->aspectX << ", " << camera->aspectY << std::endl;
        int newPosX = 0, newPosY = 0;
        glfwGetFramebufferSize(window, &newPosX, &newPosY);
        Renderer::SetViewport(posX, newPosY - y - posY -Toolbar::toolBarHeight , x, y);
        std::cout << y - posY << ", "  << std::endl;
        Toolbar::Render();

        Renderer::SetPolygonMode();
        Renderer::SetBackfaceCulling(true);
        InputProcessor::ProcessInput(window, camera);

        // if (!Renderer::polygonMode)
        //    postProcessing.FBO.Bind();
        Renderer::EnableDepthTest(true);
        Renderer::Clear();


        for (const auto& pair : ObjectManager::materialObjectMap)
        {
            std::shared_ptr<Material> material = pair.first;
            std::vector<std::shared_ptr<Object>> objs = pair.second;
            material->shader->Bind();
            material->shader->SetMaterialUniforms(material);
            material->shader->SetDirectionalLightUniforms(dirLight);


            for (const auto& obj : objs)
            {
                if (obj->mesh == nullptr) continue;
                material->shader->SetObjectUniforms(*camera, *obj);
                obj->Draw();
            }
        }

        //  if (!Renderer::polygonMode)
        //     postProcessing.RenderPostProcessing();


        //std::cout << x << ", " << y << std::endl;
        // ObjectUIWindow::Render();
        //HierarchyUIWindow::Render(ObjectManager::object_hierarchy);
        //  RendererUIWindow::Render();
        //  DirectionalLightUIWindow::Render(dirLight);
        //  if (ObjectUIWindow::activeUIObject && ObjectUIWindow::activeUIObject->material)
        //     MaterialUIWindow::Render(*ObjectUIWindow::activeUIObject->material);

        // glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    for (const auto& obj : ObjectManager::object_hierarchy)
    {
        //  ObjectParser::SaveObject(obj->GetFilePath().c_str(), obj);
    }
    ImGUIInitializer::ShutdownImGUI();

    glfwTerminate();
    return 0;
}

void SetModernDarkTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Dark background
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.30f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.35f, 0.40f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.40f, 0.45f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);

    style.FrameRounding = 4.0f; // Rounded corners
    style.WindowRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
}
