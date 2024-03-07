#include <OhmEngine/Core/Application.hpp>

namespace OHE
{
    Application::Application(int argc, char** argv)
        : m_Argc(argc), m_Argv(argv)
    {
        s_Instance = this;
    }

    Application::~Application()
    {
    }

    bool Application::InitializeApplication()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        this->window_instance = glfwCreateWindow(WIDTH, HEIGHT, "OhmJourney - The Electronic Game", nullptr, nullptr);

        if (glfwVulkanSupported() == GLFW_TRUE)
        {
            OHE_ENGINE_INFO("Vulkan is available with GLFW");
        } 
        else 
        {
            OHE_ENGINE_ERROR("Vulkan is not available with GLFW");
        }

        vulkan_instance.Initialize(this->window_instance);
        return false;
    }

    bool Application::Update()
    {
        return false;
    }

    int Application::Run()
    {
        while(!glfwWindowShouldClose(this->window_instance))
        {
            glfwPollEvents();
        }
        OHE_ENGINE_TRACE("Game ended sucessfully");
        return 0;
    }

    bool Application::Cleanup()
    {
        vulkan_instance.Cleanup();
        glfwDestroyWindow(this->window_instance);
        glfwTerminate();
        return true;
    }

    Application *Application::s_Instance = nullptr;
}