#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(500, 100, width-100, height-100);
}
class GLFWInitializer
{
public:
    
    static GLFWwindow* InitGLFW()
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
            std::cout << "[GLFW] Failed to create GLFW window" << '\n';
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        return window;
    }
};
