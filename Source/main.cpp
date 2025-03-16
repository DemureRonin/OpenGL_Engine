#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>

#include "InputProcessor.h"
#include "Engine/RenderTexture.h"
#include "Engine/Initialization/GLADInitializer.h"
#include "Engine/Initialization/GLFWInitializer.h"
#include "Engine/Scene.h"
#include "Engine/Initialization/ImGUIInitializer.h"
#include "Engine/Managers/AssetLoader.h"

#include "Engine/Time/Time.h"
#include "imgui/imgui.h"
#include "Parsers/MaterialParser.h"
#include "UI/DirectionalLightUIWindow.h"
#include "UI/HierarchyUIWindow.h"
#include "UI/InspectorUIWindow.h"
#include "UI/MaterialUIWindow.h"
#include "UI/AssetBrowserUIWindow.h"
#include "UI/SceneUIWindow.h"
#include "UI/Toolbar.h"

int main()
{
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(window, glm::vec3(0.0f, 0.0f, 3.0f));

    InputProcessor::InitCallbacks(window, camera);

    if (GLADInitializer::InitGLAD()) return -1;


    Renderer::EnableDepthTest(true);
    AssetLoader::LoadAssets();

    ImGuiIO io;
    ImGUIInitializer::InitImGUI(window, io);


    DirectionalLight dirLight;
    auto scene = std::make_shared<Scene>(AssetLoader::projectAssetsPath + "/Scenes/Scene.scene",
                                         Engine::GUID::Generate(), camera, dirLight);
    auto uiManager = std::make_shared<UIManager>(scene, camera, Renderer::GetViewport().x, Renderer::GetViewport().y);
    uiManager->CreateBasicLayout();
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();
        Renderer::NewFrame();
        ImGUIInitializer::NewFrame();

        uiManager->RenderUI();
        uiManager->SceneNewFrame();

        Renderer::SetPolygonMode();
        Renderer::SetBackfaceCulling(true);
        InputProcessor::ProcessInput(window, camera);


        Renderer::EnableDepthTest(true);
        Renderer::Clear();
        scene->Render();
        uiManager->RenderScene();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    AssetLoader::Save();
    ImGUIInitializer::ShutdownImGUI();

    glfwTerminate();
    return 0;
}
