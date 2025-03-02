#include "dependencies.h"
#include "Engine.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>

#include "Positions.h"
#include "Engine/LitShader.h"
#include "Engine/Mesh.h"
#include "Engine/CubeMarching.h"
#include "Engine/Model.h"
#include "glm/gtc/noise.hpp"

struct ImGuiIO;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void init_imgui(GLFWwindow* window, ImGuiIO& io);
void setup_ui_terrain_window(ImGuiIO io, Object& terrain);

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::vector<Vertex> convertedVertices;

std::vector<Vertex> ConvertToVertexData(std::vector<float>& data)
{
    std::vector<Vertex> vertices;
    for (size_t i = 0; i < data.size(); i += 8) // Step by 8 (Position, Normal, UV)
    {
        Vertex vertex;
        vertex.Position = glm::vec3(data[i], data[i + 1], data[i + 2]);
        vertex.Normal = glm::vec3(data[i + 3], data[i + 4], data[i + 5]);
        vertex.UV = glm::vec2(data[i + 6], data[i + 7]);

        vertices.push_back(vertex);
    }
    return vertices;
}

std::vector<std::shared_ptr<Texture>> InitializeTextures(std::vector<std::string> texturePaths);
void InitializeShaders();
void InitializeMaterials();

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    ImGuiIO io;
    init_imgui(window, io);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    std::vector<std::string> texturePaths{};
    auto textures = InitializeTextures(texturePaths);
    // textures[0]->m_Type = ALBEDO;
    //textures[1]->m_Type = SPECULAR;

    std::vector<Vertex> vertexData = ConvertToVertexData(cubeData);
    auto mesh = std::make_shared<Mesh>(vertexData, cubeIndicies);

    LitShader litShader;
    auto material = std::make_shared<Material>(litShader.shader, textures);
    material->shininess = 64;


    char modelPath[100] = "Source/Models/suzanne_blender_monkey.glb";
    Model model(modelPath);
    auto modelMesh = std::make_shared<Mesh>(model.meshes[0]->vertices, model.meshes[0]->indices);
    std::shared_ptr<Object> monkey = std::make_shared<Object>();
    monkey->SetMaterial(material);
    monkey->SetMesh(modelMesh);

    DirectionalLight dirLight;
    Renderer renderer;

    std::shared_ptr<Object> cube = std::make_shared<Object>();
    cube->SetMaterial(material);
    cube->SetMesh(mesh);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        renderer.Clear(glm::vec4(0.529, 0.808, 0.922, 1.0f));
        processInput(window);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        litShader.SetDirectionalLightUniforms(dirLight);
        litShader.SetMaterialUniforms(*material);

        litShader.SetObjectUniforms(camera, *cube);

        monkey->Draw();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

std::vector<std::shared_ptr<Texture>> InitializeTextures(std::vector<std::string> texturePaths)
{
    std::vector<std::shared_ptr<Texture>> textures;
    if (texturePaths.empty())
    {
        auto texture = std::make_shared<Texture>(WHITE_TEXTURE);
        textures.push_back(texture);
    }
    else
    {
        for (size_t i = 0; i < texturePaths.size(); i++)
        {
            auto texture = std::make_shared<Texture>(texturePaths[i]);
            textures.push_back(texture);
        }
    }
    return textures;
}


bool rightButtonPressed = false;
bool shiftPressed = false;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!rightButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            rightButtonPressed = true;
        }
    }
    else
    {
        if (rightButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            rightButtonPressed = false;
            firstMouse = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        if (!shiftPressed)
        {
            camera.MovementSpeed = 5;
            shiftPressed = true;
        }
    }
    else
    {
        if (shiftPressed)
        {
            camera.MovementSpeed = 10;
            shiftPressed = false;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!rightButtonPressed) return;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init_imgui(GLFWwindow* window, ImGuiIO& io)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 

    
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init();
}
