#include <OhmEngine/RenderVulkan/VulkanInstance.hpp>

namespace OHE
{
    VulkanInstance::VulkanInstance(/* args */)
    {
    }

    void VulkanInstance::CreateInstance(uint32_t glfwExtensionCount, const char **glfwExtensions)
    {
        VkApplicationInfo appInfos{};
        appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfos.pApplicationName = "Ohm Journey";
        appInfos.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfos.pEngineName = "OhmEngine";
        appInfos.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfos.apiVersion = VK_API_VERSION_1_0;

        std::vector<const char*> requiredExtensions;
        for(uint32_t i = 0; i < glfwExtensionCount; i++) 
        {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfos;
        instanceInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        instanceInfo.ppEnabledExtensionNames = requiredExtensions.data();
        instanceInfo.enabledLayerCount = 0;
        instanceInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

        VkResult result = vkCreateInstance(&instanceInfo, nullptr, &this->instance);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    VulkanInstance::~VulkanInstance()
    {
    }

    bool VulkanInstance::Initialize(uint32_t glfwExtensionCount, const char **glfwExtensions)
    {
        VulkanInstance::CreateInstance(glfwExtensionCount, glfwExtensions);
        return false;
    }

    bool VulkanInstance::Cleanup()
    {
        return false;
    }

} // namespace OHE

