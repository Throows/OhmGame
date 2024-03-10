#include <OhmEngine/Core/Application.hpp>

namespace OHE
{
    Application::Application(int argc, char** argv)
        : m_Argc(argc), m_Argv(argv), renderWindow{"OhmJourney - The Electronic Game", 800, 600}, vulkan_instance{renderWindow}
    {
        s_Instance = this;
    }

    Application::~Application()
    {
    }

    bool Application::InitializeApplication()
    {
        this->renderWindow.InitializeWindow();
        vulkan_instance.Initialize();
        return false;
    }

    bool Application::Update()
    {
        return false;
    }

    int Application::Run()
    {
        while(!this->renderWindow.ShouldClose())
        {
            glfwPollEvents();
            vulkan_instance.DrawFrame();
        }
        vulkan_instance.GetPhysicalDevice().WaitIdle();
        OHE_ENGINE_TRACE("Game ended sucessfully");
        return 0;
    }

    bool Application::Cleanup()
    {
        vulkan_instance.Cleanup();
        this->renderWindow.DestroyWindow();
        return true;
    }

    Application *Application::s_Instance = nullptr;
}