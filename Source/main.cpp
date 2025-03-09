#define GLFW_INCLUDE_NONE

#include <algorithm>

#include <glm/glm.hpp>

#include "InputProcessor.h"
#include "Engine/GUID.h"

#include "Engine/RenderTexture.h"
#include "Engine/Buffers/FBO/FrameBuffer.h"
#include "Engine/Buffers/RBO/RenderBufferObject.h"

#include "Engine/Initialization/GLADInitializer.h"
#include "Engine/Initialization/GLFWInitializer.h"
#include "Engine/Initialization/ImGUIInitializer.h"
#include "Engine/Managers/AssetLoader.h"
#include "Engine/Managers/ObjectManager.h"

#include "Engine/Time/Time.h"
#include "nativefiledialog/nfd.h"
#include "Parsers/MaterialParser.h"
#include "Parsers/MeshParser.h"
#include "Utils/Primitives/CubePositions.h"

#include "Parsers/ObjectParser.h"
#include "UI/DirectionalLightUIWindow.h"
#include "UI/HierarchyUIWindow.h"
#include "UI/MaterialUIWindow.h"


#include <iostream>

#include "Engine/Test.h"
#include "imgui/imgui.h"
#include "UI/InspectorUIWindow.h"
#include "UI/ProjectUIWindow.h"
#include "UI/RendererUIWindow.h"
#include "UI/SceneUIWindow.h"
#include "UI/Toolbar.h"
#include "Utils/Colors.h"

int main()
{
    Test::PrintFilePath();
    while (true)
    {
        
    }
    return EXIT_SUCCESS;
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(window, glm::vec3(0.0f, 0.0f, 3.0f));

    InputProcessor::InitCallbacks(window, camera);

    ImGuiIO io;
    ImGUIInitializer::InitImGUI(window, io);
    if (GLADInitializer::InitGLAD()) return -1;
    AssetLoader::LoadAssets();

    Renderer::EnableDepthTest(true);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto it : AssetLoader::objects)
    {
        ObjectManager::AddObject(it.second);
    }
    DirectionalLight dirLight;

    SceneUIWindow scene(camera, Renderer::GetViewport().x, Renderer::GetViewport().y);

    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();
        Renderer::NewFrame();
        ImGUIInitializer::NewFrame();


        Toolbar::Render();
        InspectorUIWindow::Render();
        HierarchyUIWindow::Render(ObjectManager::object_hierarchy);
        ProjectUIWindow::RenderAssetBrowser("Assets");
        MaterialUIWindow::Render();
        scene.NewFrame();


        Renderer::SetPolygonMode();
        Renderer::SetBackfaceCulling(true);
        InputProcessor::ProcessInput(window, camera);


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
                if (obj->model == nullptr) continue;
                material->shader->SetObjectUniforms(*camera, *obj);
                obj->Draw();
            }
        }
        scene.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGUIInitializer::ShutdownImGUI();

    glfwTerminate();
    return 0;
}
