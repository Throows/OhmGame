#pragma once

namespace OHE
{
    class RenderPass
    {
    public:
        RenderPass(VkDevice &device);
        ~RenderPass();

        void CreateRenderPass(VkFormat format);
        void DestroyRenderPass();

        VkRenderPass &GetRenderPass() { return renderPass; }

    private:
        VkDevice &device;
        VkRenderPass renderPass;
    };
}