#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace OHE
{

class RendererWindow
{
public:
    RendererWindow(std::string name, unsigned int width = 800, unsigned int height = 600);
    ~RendererWindow();

    void InitializeWindow();
    void DestroyWindow();

    GLFWwindow *GetWindow() { return window; }

private:
    unsigned int m_width;
    unsigned int m_height;
    std::string m_windowName;

    GLFWwindow *window;

};
    
} // namespace OHE
