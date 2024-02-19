#include <OhmEngine/Core/Application.hpp>
//#include <vulkan/vulkan_metal.h>

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

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        vulkan_instance.Initialize(glfwExtensionCount, glfwExtensions);
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
        glfwDestroyWindow(this->window_instance);
        glfwTerminate();
        vulkan_instance.Cleanup();
        return true;
    }

    Application *Application::s_Instance = nullptr;
}