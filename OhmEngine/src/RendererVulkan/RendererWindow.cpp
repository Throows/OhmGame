#include <OhmEngine/RendererVulkan/RendererWindow.hpp>
#include <OhmEngine/RendererVulkan/VulkanInstance.hpp>

namespace OHE
{

    static void FramebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        (void)width;
        (void)height;
        auto app = reinterpret_cast<VulkanInstance*>(glfwGetWindowUserPointer(window));
        app->GetSwapChain().SetFrameBufferResized(true);
    }

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

    void RendererWindow::SetFrameBufferSizeUserData(void *user_data)
    {
        glfwSetWindowUserPointer(this->window, user_data);
        glfwSetFramebufferSizeCallback(this->window, OHE::FramebufferResizeCallback);
    }

    FrameBufferSize RendererWindow::GetFrameBufferSize()
    {
        FrameBufferSize size;
        glfwGetFramebufferSize(this->window, (int *)&size.width, (int *)&size.height);
        return size;
    }

} // namespace OHE
