#pragma once
#include <OhmEngine/RendererVulkan/WindowSurface.hpp>

namespace OHE
{

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class PhysicalDevice
    {
    public:
        PhysicalDevice();
        ~PhysicalDevice();

        void PickPhysicalDevice(VkInstance &instance);
        void CreateLogicalDevice(bool enableValidationLayers);
        void DestroyLogicalDevice();

        void WaitIdle() { vkDeviceWaitIdle(device); };

        //Temporary
        VkDevice &GetLogicalDevice() { return device; }
        VkPhysicalDevice &GetPhysicalDevice() { return physicalDevice; }

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    private : 
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        bool IsDeviceSuitable(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

        std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };
    };

} // namespace OHE
