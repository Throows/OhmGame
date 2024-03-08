#include <OhmEngine/RendererVulkan/WindowSurface.hpp>

namespace OHE
{
    WindowSurface::WindowSurface()
    {
    }

    WindowSurface::~WindowSurface()
    {
    }

    void WindowSurface::CreateSurface(VkInstance &instance, GLFWwindow *window)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface!");
        }
    }

    void WindowSurface::CleanWindowSurface(VkInstance &instance)
    {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }
} // namespace OHE