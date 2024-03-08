#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace OHE
{

struct FrameBufferSize
{
    int width;
    int height;
};

class RendererWindow
{
public:
    RendererWindow(std::string name, unsigned int width = 800, unsigned int height = 600);
    ~RendererWindow();

    RendererWindow(const RendererWindow &) = delete;
    RendererWindow &operator=(const RendererWindow &) = delete;

    void InitializeWindow();
    void DestroyWindow();

    bool ShouldClose() { return glfwWindowShouldClose(window); }
    FrameBufferSize GetFrameBufferSize();

    GLFWwindow *GetWindow() { return window; }

private:
    unsigned int m_width;
    unsigned int m_height;
    std::string m_windowName;

    GLFWwindow *window;

};
    
} // namespace OHE
