#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
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

int main()
{
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    InputProcessor::InitCallbacks(window, camera);

    ImGuiIO io;
    ImGUIInitializer::InitImGUI(window, io);

    if (GLADInitializer::InitGLAD()) return -1;

    Renderer::EnableDepthTest(true);

    DirectionalLight dirLight;

    ObjectManager::LoadObject("Assets/Objects/Object.object");
    // ObjectManager::LoadObject("Assets/Objects/Object1.object");
    //ObjectManager::LoadObject("Assets/Objects/Object2.object");

    PostProcessing postProcessing = PostProcessing();
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        ImGUIInitializer::NewFrame();


        Renderer::SetPolygonMode();
        Renderer::SetBackfaceCulling(true);
        InputProcessor::ProcessInput(window, camera);

        if (!Renderer::polygonMode)
            postProcessing.FBO.Bind();
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

        if (!Renderer::polygonMode)
            postProcessing.RenderPostProcessing();


        ObjectUIWindow::Render();
        HierarchyUIWindow::Render(ObjectManager::object_hierarchy);
        RendererUIWindow::Render();
        DirectionalLightUIWindow::Render(dirLight);
        if (ObjectUIWindow::activeUIObject && ObjectUIWindow::activeUIObject->material)
            MaterialUIWindow::Render(*ObjectUIWindow::activeUIObject->material);


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
