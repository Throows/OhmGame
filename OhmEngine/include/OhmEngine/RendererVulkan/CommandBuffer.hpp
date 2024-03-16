#pragma once
#include <OhmEngine/RendererVulkan/SwapChain.hpp>
#include <OhmEngine/RendererVulkan/RenderPass.hpp>
#include <OhmEngine/RendererVulkan/VulkanPipeline.hpp>

namespace OHE
{
    class CommandBuffer
    {
        public:
            CommandBuffer(VkDevice &device, SwapChain &swapChain, RenderPass &renderPass, VulkanPipeline &pipeline);
            ~CommandBuffer();

            CommandBuffer(const CommandBuffer&) = delete;
            CommandBuffer& operator=(const CommandBuffer&) = delete;

            void CreateCommandPool(uint32_t queueFamilyIndex);
            void CreateCommandBuffers();
            void DestroyCommandPool();

            void ResetAndRecordCommandBuffer(int frame, uint32_t imageIndex);

            VkCommandBuffer *GetCommandBuffer(uint32_t index) { return &m_commandBuffers[index]; }
            
        private: 
            VkDevice &device;
            SwapChain &swapChain;
            RenderPass &renderPass;
            VulkanPipeline &pipeline;

            VkCommandPool m_commandPool;
            std::vector<VkCommandBuffer> m_commandBuffers;

            void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    };
}