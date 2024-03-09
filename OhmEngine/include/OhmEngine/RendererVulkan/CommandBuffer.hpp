#pragma once

namespace OHE
{
    class CommandBuffer
    {
        public:
            CommandBuffer();
            ~CommandBuffer();

            CommandBuffer(const CommandBuffer&) = delete;
            CommandBuffer& operator=(const CommandBuffer&) = delete;

            void CreateCommandPool();
            void CreateCommandBuffers();
            void DestroyCommandPool();

            void CommandBuffer::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        private: 
            VkCommandPool m_commandPool;
            std::vector<VkCommandBuffer> m_commandBuffers;
    };
}