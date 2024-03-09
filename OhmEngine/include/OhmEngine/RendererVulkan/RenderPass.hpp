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

    private:
        VkRenderPass renderPass;
    };
}