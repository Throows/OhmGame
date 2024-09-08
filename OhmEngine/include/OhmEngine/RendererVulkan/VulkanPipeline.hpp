#pragma once

#include <vulkan/vulkan.h>
#include <OhmEngine/RendererVulkan/VertexBuffer.hpp>

namespace OHE {

    class VulkanPipeline {
    public:
        VulkanPipeline(VkDevice &device, const std::string &vertFile, const std::string &fragFile);
        ~VulkanPipeline();

        VulkanPipeline(const VulkanPipeline &) = delete;
        VulkanPipeline &operator=(const VulkanPipeline &) = delete;

        void CreateGraphicsPipeline(VkRenderPass &renderPass);
        void DestroyGraphicsPipeline();

        VkPipeline GetGraphicsPipeline() { return graphicsPipeline; }

    private:
        VkDevice& device;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        std::string vertFile;
        std::string fragFile;

        static std::vector<char> ReadFile(const std::string &filename);
        VkShaderModule CreateShaderModule(const std::vector<char> &code);
    };
}