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

        void NextFrame() { currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT; }

        static const int MAX_FRAMES_IN_FLIGHT = 2;

    private:
        VkDevice &device;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        
        uint32_t currentFrame = 0;
    };
}