#pragma once
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class GLADInitializer
{
public:
    static int InitGLAD()
    {
        if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
        {
            std::cout << "[GLAD] Failed to initialize GLAD" << '\n';
            return -1;
        }
        glEnable(GL_DEPTH_TEST);
        return 0;
    }
};
