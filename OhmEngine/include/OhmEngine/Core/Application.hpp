#pragma once
#include <OhmEngine/RendererVulkan/VulkanInstance.hpp>
#include <OhmEngine/RendererVulkan/RendererWindow.hpp>

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

        // Temporary
        GLFWwindow* GetWindow() { return renderWindow.GetWindow(); }

    private:
        int m_Argc;
        char** m_Argv;

        static Application* s_Instance;
        VulkanInstance vulkan_instance;
        RendererWindow renderWindow;
        
    };
} // namespace OHE
