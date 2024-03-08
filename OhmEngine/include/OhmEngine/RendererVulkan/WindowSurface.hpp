#pragma once

#include <GLFW/glfw3native.h>

namespace OHE
{

    class WindowSurface
    {
    public:
        WindowSurface();
        ~WindowSurface();

        void CreateSurface(VkInstance &instance, GLFWwindow *window);
        void CleanWindowSurface(VkInstance &instance);
        VkSurfaceKHR &GetSurface() { return surface; }

    private:
        VkSurfaceKHR surface;
    };    
}