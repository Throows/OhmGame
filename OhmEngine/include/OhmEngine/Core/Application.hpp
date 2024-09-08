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

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        bool InitializeApplication();
        bool Update();
        int Run();
        bool Cleanup();

        static Application* Get() { return s_Instance; };

        RendererWindow &GetRendererWindow() { return renderWindow; }

    private:
        [[maybe_unused]] int m_Argc;
        [[maybe_unused]] char** m_Argv;

        static Application* s_Instance;
        VulkanInstance vulkan_instance;
        RendererWindow renderWindow;
        
    };
} // namespace OHE
