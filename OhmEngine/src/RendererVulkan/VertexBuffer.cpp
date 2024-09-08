#include <OhmEngine/RendererVulkan/VertexBuffer.hpp>

namespace OHE 
{

    VertexBuffer::VertexBuffer(PhysicalDevice& physicalDevice) : physicalDevice(physicalDevice)
    {
    }

    VertexBuffer::~VertexBuffer()
    {
    }

    void VertexBuffer::CreateVertexBuffer()
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = sizeof(vertices[0]) * vertices.size();
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(physicalDevice.GetLogicalDevice(), &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(physicalDevice.GetLogicalDevice(), vertexBuffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = physicalDevice.FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        if (vkAllocateMemory(physicalDevice.GetLogicalDevice(), &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(physicalDevice.GetLogicalDevice(), vertexBuffer, vertexBufferMemory, 0);

        void *data;
        vkMapMemory(physicalDevice.GetLogicalDevice(), vertexBufferMemory, 0, bufferInfo.size, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferInfo.size);
        vkUnmapMemory(physicalDevice.GetLogicalDevice(), vertexBufferMemory);
    }

    void VertexBuffer::CleanupVertexBuffer()
    {
        vkDestroyBuffer(physicalDevice.GetLogicalDevice(), vertexBuffer, nullptr);
        vkFreeMemory(physicalDevice.GetLogicalDevice(), vertexBufferMemory, nullptr);
    }

} // Namespace OHE