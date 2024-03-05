#pragma once
#include <OhmEngine/RenderVulkan/VulkanInstance.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace OHE 
{
    class Application
    {
    public:
        Application(int argc, char** argv);
        ~Application();

        bool InitializeApplication();
        bool Update();
        int Run();
        bool Cleanup();

        static Application* Get() { return s_Instance; };

        GLFWwindow* GetWindow() { return window_instance; }

        const uint32_t WIDTH  = 800;
        const uint32_t HEIGHT = 600;

    private:
        int m_Argc;
        char** m_Argv;

        static Application* s_Instance;
        GLFWwindow *window_instance;
        VulkanInstance vulkan_instance;
        
    };
} // namespace OHE
