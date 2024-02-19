#pragma once 
#include <vulkan/vulkan.h>

namespace OHE
{
    class VulkanInstance
    {
    public:
        VulkanInstance();
        ~VulkanInstance();

        bool Initialize(uint32_t glfwExtensionCount, const char **glfwExtensions);
        bool Cleanup();

        VkInstance &GetInstance() { return instance; }

    private:
        VkInstance instance;

        void CreateInstance(uint32_t glfwExtensionCount, const char **glfwExtensions);
    };
} // Namespace OHE
