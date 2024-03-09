#pragma once 

namespace OHE
{

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class SwapChain
    {
        public:
            SwapChain();
            ~SwapChain();

            SwapChain(const SwapChain&) = delete;
            SwapChain& operator=(const SwapChain&) = delete;

            void CreateSwapChain();
            void DestroySwapChain();
            void CreateImageViews();
            void DestroyImageViews();

            SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        private:
            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkImageView> swapChainImageViews;
    };

} // namespace OHE