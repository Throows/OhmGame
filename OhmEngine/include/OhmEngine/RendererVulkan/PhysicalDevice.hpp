#pragma once
#include <OhmEngine/RendererVulkan/WindowSurface.hpp>

namespace OHE
{

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

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
        PhysicalDevice(VkSurfaceKHR &surface);
        ~PhysicalDevice();

        void PickPhysicalDevice(VkInstance &instance);
        void CreateLogicalDevice(bool enableValidationLayers);
        void DestroyLogicalDevice();

        void WaitIdle() { vkDeviceWaitIdle(device); };

        //Temporary
        VkDevice &GetLogicalDevice() { return device; }
        VkPhysicalDevice &GetPhysicalDevice() { return physicalDevice; }

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

        std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };

        const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation",
            //"VK_LAYER_LUNARG_api_dump",
            //"VK_LAYER_KHRONOS_profiles",
            //"VK_LAYER_KHRONOS_synchronization2",
            //"VK_LAYER_KHRONOS_shader_object",
        };

        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

        VkQueue GetGraphicsQueue() { return graphicsQueue; }
        VkQueue GetPresentQueue() { return presentQueue; }

    private: 
        VkSurfaceKHR &surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        bool IsDeviceSuitable(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    };

} // namespace OHE
