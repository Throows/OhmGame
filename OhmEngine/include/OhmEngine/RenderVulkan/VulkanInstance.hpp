#pragma once 

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace OHE
{
    class VulkanInstance
    {
    public:
        VulkanInstance();
        ~VulkanInstance();

        bool Initialize();
        bool Cleanup();

        VkInstance &GetInstance() { return instance; }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

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
