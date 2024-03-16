#include <OhmEngine/RendererVulkan/VulkanInstance.hpp>

namespace OHE
{
    VulkanInstance::VulkanInstance(RendererWindow &window) 
        : rendererWindow(window)
    {
    }

    void VulkanInstance::CreateInstance()
    {
        if (enableValidationLayers && !CheckValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfos{};
        appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfos.pApplicationName = "Ohm Journey";
        appInfos.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfos.pEngineName = "OhmEngine";
        appInfos.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfos.apiVersion = VK_API_VERSION_1_2;

        std::vector<const char*> requiredExtensions = GetRequiredExtensions();
        requiredExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef __APPLE__
        requiredExtensions.emplace_back(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
        requiredExtensions.emplace_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);


        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfos;
        instanceInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
        instanceInfo.ppEnabledExtensionNames = requiredExtensions.data();
        instanceInfo.enabledLayerCount = 0;
        instanceInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers)
        {
            instanceInfo.enabledLayerCount = static_cast<uint32_t>(this->physicalDevice.validationLayers.size());
            instanceInfo.ppEnabledLayerNames = this->physicalDevice.validationLayers.data();
            VulkanInstance::PopulateDebugMessengerCreateInfo(debugCreateInfo);
            instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        }
        else
        {
            instanceInfo.enabledLayerCount = 0;
            instanceInfo.pNext = nullptr;
        }

        VkResult result = vkCreateInstance(&instanceInfo, nullptr, &this->instance);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    VulkanInstance::~VulkanInstance()
    {
    }

    bool VulkanInstance::Initialize()
    {
        VulkanInstance::CreateInstance();
        VulkanInstance::SetupDebugMessenger();
        this->windowSurface.CreateSurface(this->instance, this->rendererWindow.GetWindow());
        this->physicalDevice.PickPhysicalDevice(this->instance);
        this->physicalDevice.CreateLogicalDevice(enableValidationLayers);
        this->swapChain.CreateSwapChain();
        this->swapChain.CreateImageViews();
        this->renderPass.CreateRenderPass(this->swapChain.GetSwapChainImageFormat());
        this->vulkanPipeline.CreateGraphicsPipeline(this->renderPass.GetRenderPass());
        this->swapChain.CreateFramebuffers();
        //TEMPORARY
        QueueFamilyIndices indices = this->physicalDevice.FindQueueFamilies(this->physicalDevice.GetPhysicalDevice());
        this->commandBuffer.CreateCommandPool(indices.graphicsFamily.value());
        this->commandBuffer.CreateCommandBuffers();
        this->fence.CreateSyncObjects();
        return false;
    }

    bool VulkanInstance::Cleanup()
    {
        this->fence.CleanupSyncObjects();
        this->commandBuffer.DestroyCommandPool();
        this->swapChain.DestroyFramebuffers();
        this->vulkanPipeline.DestroyGraphicsPipeline();
        this->renderPass.DestroyRenderPass();
        this->swapChain.DestroyImageViews();
        this->swapChain.DestroySwapChain();
        this->physicalDevice.DestroyLogicalDevice();
        if (enableValidationLayers)
        {
            VulkanInstance::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        this->windowSurface.CleanWindowSurface(this->instance);
        vkDestroyInstance(instance, nullptr);
        return false;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::DebugCallback(   VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
                                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                                    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                                    void *pUserData)
    {
        OHE_ENGINE_TRACE("(Vulkan) : {0}", pCallbackData->pMessage);
        return VK_FALSE;
    }

    bool VulkanInstance::CheckValidationLayerSupport()
    {   
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *validationLayer : this->physicalDevice.validationLayers)
        {
            bool layerFound = false;
            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(validationLayer, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound) return false;
        }
        return true;
    }

    std::vector<const char *> VulkanInstance::GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if (enableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    void VulkanInstance::SetupDebugMessenger()
    {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        PopulateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to set up debug messenger!");
        }

    }

    VkResult VulkanInstance::CreateDebugUtilsMessengerEXT(  VkInstance instance, 
                                                            const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                            const VkAllocationCallbacks *pAllocator,
                                                            VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        } 
    }

    void VulkanInstance::DestroyDebugUtilsMessengerEXT( VkInstance instance,
                                                        VkDebugUtilsMessengerEXT debugMessenger,
                                                        const VkAllocationCallbacks *pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }

    void VulkanInstance::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = VulkanInstance::DebugCallback;
        createInfo.pUserData = nullptr;
    }

    void VulkanInstance::DrawFrame()
    {
        int frame = this->fence.GetCurrentFrame();
        this->fence.WaitForFences();
        uint32_t imageIndex = this->fence.AquireNextFrame(this->swapChain.GetSwapChain());
        //imageIndex = imageIndex % Fence::MAX_FRAMES_IN_FLIGHT;

        this->commandBuffer.ResetAndRecordCommandBuffer(frame, imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {this->fence.GetImageAvailableSemaphore()};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = this->commandBuffer.GetCommandBuffer(frame);

        VkSemaphore signalSemaphores[] = {this->fence.GetRenderFinishedSemaphore()};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(this->physicalDevice.GetGraphicsQueue(), 1, &submitInfo, this->fence.GetInFlightFence()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain.GetSwapChain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(this->physicalDevice.GetPresentQueue(), &presentInfo);

        fence.NextFrame();
    }

} // namespace OHE
