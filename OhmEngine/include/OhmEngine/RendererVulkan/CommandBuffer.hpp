#pragma once
#include <OhmEngine/RendererVulkan/SwapChain.hpp>
#include <OhmEngine/RendererVulkan/RenderPass.hpp>
#include <OhmEngine/RendererVulkan/VulkanPipeline.hpp>
#include <OhmEngine/RendererVulkan/VertexBuffer.hpp>

namespace OHE
{
    class CommandBuffer
    {
        public:
            CommandBuffer(VkDevice &device, SwapChain &swapChain, RenderPass &renderPass, VulkanPipeline &pipeline, VertexBuffer &vertexBuffer);
            ~CommandBuffer();

            CommandBuffer(const CommandBuffer&) = delete;
            CommandBuffer& operator=(const CommandBuffer&) = delete;

            void CreateCommandPool(uint32_t queueFamilyIndex);
            void CreateCommandBuffers();
            void DestroyCommandPool();

            void ResetAndRecordCommandBuffer(int frame, uint32_t imageIndex);

            VkCommandBuffer *GetCommandBuffer(uint32_t index) { return &m_commandBuffers[index]; }

            VkCommandPool &GetCommandPool() { return m_commandPool; };
            VkPipeline GetGraphicsPipeline() { return pipeline.GetGraphicsPipeline(); }
            
        private: 
            VkDevice &device;
            SwapChain &swapChain;
            RenderPass &renderPass;
            VulkanPipeline &pipeline;
            VertexBuffer &vertexBuffer;

            VkCommandPool m_commandPool;
            std::vector<VkCommandBuffer> m_commandBuffers;

            void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    };
}