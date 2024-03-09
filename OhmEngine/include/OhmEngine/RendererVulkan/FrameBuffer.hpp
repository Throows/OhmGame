#pragma once 

namespace OHE
{
    class FrameBuffer
    {
        public:
            FrameBuffer();
            ~FrameBuffer();

            FrameBuffer(const FrameBuffer&) = delete;
            FrameBuffer& operator=(const FrameBuffer&) = delete;

            void CreateFramebuffers();
            void DestroyFramebuffers();

        private: 
            std::vector<VkFramebuffer> m_swapChainFramebuffers;
    };
}