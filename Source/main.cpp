#include "dependencies.h"
#include "Engine.h"


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <algorithm>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Positions.h"
#include "Engine/LitShader.h"
#include "Engine/Mesh.h"
#include "Engine/CubeMarching.h"
#include "glm/gtc/noise.hpp"

struct ImGuiIO;

struct MatSettings
{
    glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    float shininess = 32;
};

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


void UpdateTerrain(bool cond);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);


    // Texture obj_texture("Textures/container2.png");

    LitShader litShader;
    DirectionalLight dirLight;
    Material material;

    Renderer renderer;

    auto start = std::chrono::high_resolution_clock::now();
    generateTerrain();
    generateMesh();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start; // Calculate elapsed time

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Vertex vertex;
        vertex.Position = vertices[i];
        vertex.Normal = normals[i];
        vertex.UV = UV[i];

        convertedVertices.push_back(vertex);
    }
    Object terrain(convertedVertices, indices);
    /*std::vector<Vertex> vertexData = ConvertToVertexData(cubeData);
    Object cube(vertexData, cubeIndicies);*/

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        renderer.Clear(glm::vec4(0.529, 0.808, 0.922, 1.0f));

        processInput(window);

        setup_ui_terrain_window(io, terrain);

        //obj_texture.Bind();
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        litShader.SetDirectionalLightUniforms(dirLight);
        // if (plane.transform.position.x < 1.0f) material.tint = glm::vec4(1.0f, .0f, .0f, 1);

        material.tint = glm::vec4(0.133, 0.545, 0.133, 1.0f);
        litShader.SetMaterialUniforms(material);
        // cube.transform.SetPosition(glm::vec3(i * 2, j * 2, k * 2));
        // plane.transform.ApplyTranslation();
        //std::cout << i << ", " << j << ", " << k << std::endl;
        litShader.SetObjectUniforms(camera, terrain);

        terrain.Draw(litShader.shader);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
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
            camera.MovementSpeed = 500;
            shiftPressed = true;
        }
    }
    else
    {
        if (shiftPressed)
        {
            camera.MovementSpeed = 100;
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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW
    // callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}


void UpdateTerrain(Object& terrain)
{
    ClearData();
    auto start = std::chrono::high_resolution_clock::now();

    generateTerrain();
    generateMesh();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start; // Calculate elapsed time

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    convertedVertices.clear();
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Vertex vertex;
        vertex.Position = vertices[i];
        vertex.Normal = normals[i];
        vertex.UV = UV[i];

        convertedVertices.push_back(vertex);
    }
    terrain.SetMesh(convertedVertices, indices);
}

void setup_ui_terrain_window(ImGuiIO io, Object& terrain)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    {
        ImGui::Begin("Terrain Settings");

        ImGui::SliderFloat("NoiseScale", &noiseScale, 0, 10);
        ImGui::SliderFloat("persistence", &persistence, 0, 1);
        ImGui::SliderFloat("lacunarity", &lacunarity, 0, 10);
        ImGui::SliderInt("octaves", &octaves, 1, 4);
        if (ImGui::Button("Update"))
        {
            UpdateTerrain(terrain);
        }


        ImGui::End();
    }

    ImGui::Render();
}
