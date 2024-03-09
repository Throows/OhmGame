#pragma once

namespace OHE
{
    class Fence
    {
    public:
        Fence();
        ~Fence();

        void CreateSyncObjects();
        void CleanupSyncObjects();

    private:
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
    };
}