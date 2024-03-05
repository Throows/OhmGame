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

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    static std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
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
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    };
} // namespace OHE