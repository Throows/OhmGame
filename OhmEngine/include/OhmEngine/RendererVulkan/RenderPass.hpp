#pragma once

namespace OHE
{
    class RenderPass
    {
    public:
        RenderPass(/* args */);
        ~RenderPass();

        void CreateRenderPass();
        void DestroyRenderPass();

        VkRenderPass &GetRenderPass() { return renderPass; }

    private:
        VkRenderPass renderPass;
    };
}