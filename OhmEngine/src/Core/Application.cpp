#include <OhmEngine/Core/Application.hpp>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_metal.h>

namespace OHE
{
    Application::Application(int argc, char** argv)
        : m_Argc(argc), m_Argv(argv)
    {
        s_Instance = this;
    }

    Application::~Application()
    {

        // Just a try to prove that Vulkan can run on MacOS
        VkInstance instance;
        VkInstanceCreateInfo info = {};

        VkResult result = vkCreateInstance(&info, NULL, &instance);

        if (result == VK_SUCCESS) {
            OHE_ENGINE_INFO("VK running successfully");
        } else {
            OHE_ENGINE_ERROR("VK instance not runnning : {}", (int)result);
        }
    }

    bool Application::Update()
    {
        return true;
    }

    int Application::Run()
    {

        /*while (1)
        {
        }*/
        OHE_ENGINE_TRACE("Game ended sucessfully");
        return 0;
    }

    Application *Application::s_Instance = nullptr;
}