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

    static std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
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

    private : 
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        const int MAX_FRAMES_IN_FLIGHT = 2;
        uint32_t currentFrame = 0;

        bool IsDeviceSuitable(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
} // namespace OHE