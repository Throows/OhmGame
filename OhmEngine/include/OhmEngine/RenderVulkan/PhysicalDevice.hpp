#pragma once
#include <OhmEngine/RenderVulkan/WindowSurface.hpp>

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

    static const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
    };

    class PhysicalDevice
    {
    public:
        PhysicalDevice();
        ~PhysicalDevice();

        WindowSurface &GetWindowSurface() { return windowSurface; }
        void PickPhysicalDevice(VkInstance &instance);
        void CreateLogicalDevice(bool enableValidationLayers);
        void DestroyLogicalDevice();

    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        WindowSurface windowSurface;

        bool IsDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
} // namespace OHE