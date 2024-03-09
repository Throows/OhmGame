#pragma once

namespace OHE
{
    class CommandBuffer
    {
        public:
            CommandBuffer(VkDevice &device);
            ~CommandBuffer();

            CommandBuffer(const CommandBuffer&) = delete;
            CommandBuffer& operator=(const CommandBuffer&) = delete;

            void CreateCommandPool(uint32_t queueFamilyIndex);
            void CreateCommandBuffers();
            void DestroyCommandPool();

            void CommandBuffer::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        private: 
            VkDevice &device;
            VkCommandPool m_commandPool;
            std::vector<VkCommandBuffer> m_commandBuffers;
    };
}