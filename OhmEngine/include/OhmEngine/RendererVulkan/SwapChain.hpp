#pragma once 

#include <OhmEngine/RendererVulkan/PhysicalDevice.hpp>
#include <OhmEngine/RendererVulkan/RendererWindow.hpp>

namespace OHE
{
    class SwapChain
    {
        public:
            SwapChain(VkDevice &device, PhysicalDevice &physicalDevice, VkSurfaceKHR &surface, RendererWindow &window, VkRenderPass &renderPass);
            ~SwapChain();

            SwapChain(const SwapChain&) = delete;
            SwapChain& operator=(const SwapChain&) = delete;

            void CreateSwapChain();
            void CreateFramebuffers();
            void CreateImageViews();
            void DestroySwapChain();
            void DestroyImageViews();
            void DestroyFramebuffers();

            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

            VkExtent2D GetSwapChainExtent() { return swapChainExtent; }
            VkFramebuffer GetSwapChainFramebuffer(uint32_t index) { return m_swapChainFramebuffers[index]; }
            VkFormat &GetSwapChainImageFormat() { return swapChainImageFormat; }
            VkSwapchainKHR GetSwapChain() { return swapChain; }


        private:
            VkDevice &device;
            PhysicalDevice &physicalDevice;
            VkSurfaceKHR &surface;
            RendererWindow &window;
            VkRenderPass &renderPass;

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkImageView> swapChainImageViews;

            std::vector<VkFramebuffer> m_swapChainFramebuffers;
    };

} // namespace OHE