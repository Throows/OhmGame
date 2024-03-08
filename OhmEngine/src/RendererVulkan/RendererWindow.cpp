#include <OhmEngine/RendererVulkan/RendererWindow.hpp>

namespace OHE
{
    RendererWindow::RendererWindow(std::string name, unsigned int width, unsigned int height)
        : m_width(width), m_height(height), m_windowName(name)
    {
    }

    RendererWindow::~RendererWindow()
    {
    }

    void RendererWindow::InitializeWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        this->window = glfwCreateWindow(this->m_width, this->m_height, this->m_windowName.c_str(), nullptr, nullptr);

        if (glfwVulkanSupported() == GLFW_TRUE)
        {
            OHE_ENGINE_INFO("Vulkan is available with GLFW");
        } 
        else 
        {
            OHE_ENGINE_ERROR("Vulkan is not available with GLFW");
        }
    }

    void RendererWindow::DestroyWindow()
    {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    FrameBufferSize RendererWindow::GetFrameBufferSize()
    {
        FrameBufferSize size;
        glfwGetFramebufferSize(this->window, (int *)&size.width, (int *)&size.height);
        return size;
    }

} // namespace OHE
