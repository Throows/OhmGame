#include <OhmEngine/Core/Application.hpp>

namespace OHE
{
    Application::Application(int argc, char** argv)
        : m_Argc(argc), m_Argv(argv), renderWindow{"OhmJourney - The Electronic Game", 800, 600}
    {
        s_Instance = this;
    }

    Application::~Application()
    {
    }

    bool Application::InitializeApplication()
    {
        this->renderWindow.InitializeWindow();
        vulkan_instance.Initialize(this->renderWindow.GetWindow());
        return false;
    }

    bool Application::Update()
    {
        return false;
    }

    int Application::Run()
    {
        while(!glfwWindowShouldClose(this->renderWindow.GetWindow()))
        {
            glfwPollEvents();
            vulkan_instance.GetPhysicalDevice().DrawFrame();
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