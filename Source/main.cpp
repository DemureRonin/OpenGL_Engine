#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>


#include <iostream>
#include <glm/glm.hpp>

#include "InputProcessor.h"
#include "Engine/LitShader.h"
#include "Engine/Mesh.h"
#include "Engine/Initialization/GLADInitializer.h"
#include "Engine/Initialization/GLFWInitializer.h"
#include "Engine/Initialization/ImGUIInitializer.h"
#include "Engine/Time/Time.h"
#include "Utils/Primitives/CubePositions.h"
#include "Parsers/MaterialParser.h"

#include "Parsers/ObjectParser.h"
#include "UI/DirectionalLightUIWindow.h"
#include "UI/HierarchyUIWindow.h"
#include "UI/MaterialUIWindow.h"

#include "UI/ObjectUIWindow.h"
#include "UI/RendererUIWindow.h"

#include "Utils/Primitives/PlanePositions.h"

int main()
{
    auto window = GLFWInitializer::InitGLFW();
    if (!window) return -1;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    InputProcessor::InitCallbacks(window, camera);

    ImGuiIO io;
    ImGUIInitializer::InitImGUI(window, io);

    if (GLADInitializer::InitGLAD()) return -1;
    Renderer::SetBackfaceCulling();
    auto planeMesh = std::make_shared<Mesh>(planeVertices, planeIndices);
    std::vector<std::shared_ptr<Object>> object_hierarchy = {};
    LitShader litShader;
    DirectionalLight dirLight;

    std::shared_ptr<Object> object = ObjectParser::LoadObject("Source/Extentions/Object.object", litShader);
    std::shared_ptr<Object> sphere = ObjectParser::LoadObject("Source/Extentions/Object1.object", litShader);
    std::shared_ptr<Object> plane = ObjectParser::LoadObject("Source/Extentions/Object2.object", litShader);
    // std::shared_ptr<Object> plane  = ObjectParser::LoadObject("Source/Extentions/Object2.object", litShader);

    object->SetMaterial(sphere->material);
    plane->SetMaterial(sphere->material);

    object_hierarchy.push_back(object);
    object_hierarchy.push_back(sphere);
    object_hierarchy.push_back(plane);

    std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Object>>> materialObjectMap;
    for (const auto& obj : object_hierarchy)
    {
        materialObjectMap[obj->material].push_back(obj);
    }

    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        ImGUIInitializer::NewFrame();

        Renderer::Clear();
        Renderer::SetPolygonMode();
        InputProcessor::ProcessInput(window, camera);

        litShader.shader->Bind();
        litShader.SetDirectionalLightUniforms(dirLight);
        
        for (const auto& pair : materialObjectMap)
        {
            std::shared_ptr<Material> material = pair.first;
            std::vector<std::shared_ptr<Object>> objs = pair.second;
            litShader.SetMaterialUniforms(material);

            for (const auto& obj : objs)
            {
                if (obj->mesh == nullptr) continue;
                litShader.SetObjectUniforms(*camera, *obj);
                obj->Draw();
            }
        }
      

        ObjectUIWindow::Render();
        HierarchyUIWindow::Render(object_hierarchy);
        RendererUIWindow::Render();
        DirectionalLightUIWindow::Render(dirLight);
        MaterialUIWindow::Render(*object->material);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    for (const auto& obj : object_hierarchy)
    {
        ObjectParser::SaveObject(obj->GetFilePath().c_str(), obj);
    }
    ImGUIInitializer::ShutdownImGUI();

    glfwTerminate();
    return 0;
}
