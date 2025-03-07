#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>

#include "InputProcessor.h"

#include "Engine/RenderTexture.h"
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
#include "UI/Toolbar.h"
#include "Utils/Colors.h"
#include "imgui/imgui.h"


int main()
{
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(window, glm::vec3(0.0f, 0.0f, 3.0f));

    InputProcessor::InitCallbacks(window, camera);

    ImGuiIO io;
    ImGUIInitializer::InitImGUI(window, io);


    if (GLADInitializer::InitGLAD()) return -1;

    Renderer::EnableDepthTest(true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DirectionalLight dirLight;

    ShaderManager::LoadShaders("Source/Shaders");


    ObjectManager::LoadObject("Assets/Objects/Object.object");


    RenderTexture renderTexture = RenderTexture();
    int width = 1600, height = 900;
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();
        Renderer::NewFrame();
        ImGUIInitializer::NewFrame();
         
        ImGui::DockSpaceOverViewport();

        Toolbar::Render();
        renderTexture.NewFrame(width, height);
        ObjectUIWindow::Render();
        camera->SetAspect(width, height);
        renderTexture.Bind();

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
                if (obj->mesh == nullptr) continue;
                material->shader->SetObjectUniforms(*camera, *obj);
                obj->Draw();
            }
        }

        renderTexture.BindTexture();
        ImGui::Begin("Scene");

        ImGui::Image(renderTexture.FBO.GetColorBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
        width = ImGui::GetWindowWidth();
        height = ImGui::GetWindowHeight();
        std::cout << width << " m" << height << std::endl;
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGUIInitializer::ShutdownImGUI();

    glfwTerminate();
    return 0;
}
