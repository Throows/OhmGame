#pragma once

namespace OHE
{
    class Fence
    {
    public:
        Fence(VkDevice &device);
        ~Fence();

        void CreateSyncObjects();
        void CleanupSyncObjects();

        void WaitForFences();
        void ResetFences();
        void NextFrame() { currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT; }
        uint32_t GetCurrentFrame() { return currentFrame; }

        VkSemaphore &GetImageAvailableSemaphore() { return imageAvailableSemaphores[currentFrame]; }
        VkSemaphore &GetRenderFinishedSemaphore() { return renderFinishedSemaphores[currentFrame]; }
        VkFence &GetInFlightFence() { return inFlightFences[currentFrame]; }

        static const int MAX_FRAMES_IN_FLIGHT = 2;

    private:
        VkDevice &device;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        
        uint32_t currentFrame = 0;
    };
}