#pragma once 

#include <OhmEngine/RenderVulkan/PhysicalDevice.hpp>
#include <OhmEngine/RenderVulkan/WindowSurface.hpp>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace OHE
{

    static const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    class VulkanInstance
    {
    public:
        VulkanInstance();
        ~VulkanInstance();

        bool Initialize(GLFWwindow *window);
        bool Cleanup();

        VkInstance &GetInstance() { return instance; }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

    private:
        VkInstance instance;
        PhysicalDevice physicalDevice;
        VkDebugUtilsMessengerEXT debugMessenger;

        void CreateInstance();
        bool CheckValidationLayerSupport();
        std::vector<const char *> GetRequiredExtensions();
        void SetupDebugMessenger();
        VkResult CreateDebugUtilsMessengerEXT(  VkInstance instance,
                                                const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                const VkAllocationCallbacks *pAllocator,
                                                VkDebugUtilsMessengerEXT *pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT( VkInstance instance, 
                                            VkDebugUtilsMessengerEXT debugMessenger,
                                            const VkAllocationCallbacks *pAllocator);

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    };
} // Namespace OHE
