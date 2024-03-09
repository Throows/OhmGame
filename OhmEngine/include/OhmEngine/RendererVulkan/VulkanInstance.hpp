#pragma once 

#include <OhmEngine/RendererVulkan/PhysicalDevice.hpp>
#include <OhmEngine/RendererVulkan/WindowSurface.hpp>
#include <OhmEngine/RendererVulkan/SwapChain.hpp>
#include <OhmEngine/RendererVulkan/RenderPass.hpp>
#include <OhmEngine/RendererVulkan/VulkanPipeline.hpp>
#include <OhmEngine/RendererVulkan/FrameBuffer.hpp>
#include <OhmEngine/RendererVulkan/CommandBuffer.hpp>
#include <OhmEngine/RendererVulkan/Fence.hpp>

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

        bool Initialize(GLFWwindow *window);
        bool Cleanup();

        VkInstance &GetInstance() { return instance; }
        PhysicalDevice &GetPhysicalDevice() { return physicalDevice; }
        WindowSurface &GetWindowSurface() { return windowSurface; }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

        void VulkanInstance::DrawFrame();

    private:
        VkInstance instance;
        WindowSurface windowSurface;
        PhysicalDevice physicalDevice;
        SwapChain swapChain;
        RenderPass renderPass;
        std::unique_ptr<VulkanPipeline> vulkanPipeline;
        FrameBuffer frameBuffer;
        CommandBuffer commandBuffer;
        Fence fence;

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

        const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation",
            //"VK_LAYER_LUNARG_api_dump",
            //"VK_LAYER_KHRONOS_profiles",
            //"VK_LAYER_KHRONOS_synchronization2",
            //"VK_LAYER_KHRONOS_shader_object",
        };
    };
} // Namespace OHE
