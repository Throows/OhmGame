#include <OhmEngine/RendererVulkan/VertexBuffer.hpp>

#include <OhmEngine/RendererVulkan/CommandBuffer.hpp>

namespace OHE 
{

    VertexBuffer::VertexBuffer(PhysicalDevice& physicalDevice, CommandBuffer &commandBuffer) 
        : physicalDevice(physicalDevice), m_commandBuffer(commandBuffer)
    {
    }

    VertexBuffer::~VertexBuffer()
    {
    }

    void VertexBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(physicalDevice.GetLogicalDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(physicalDevice.GetLogicalDevice(), buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = physicalDevice.FindMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(physicalDevice.GetLogicalDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(physicalDevice.GetLogicalDevice(), buffer, bufferMemory, 0);
    }

    void VertexBuffer::CreateVertexBuffer()
    {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        VertexBuffer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void *data;
        vkMapMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory);

        VertexBuffer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
        VertexBuffer::CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(physicalDevice.GetLogicalDevice(), stagingBuffer, nullptr);
        vkFreeMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory, nullptr);
    }

    void VertexBuffer::CreateIndexBuffer()
    {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        VertexBuffer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void *data;
        vkMapMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vkUnmapMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory);

        VertexBuffer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
        VertexBuffer::CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(physicalDevice.GetLogicalDevice(), stagingBuffer, nullptr);
        vkFreeMemory(physicalDevice.GetLogicalDevice(), stagingBufferMemory, nullptr);
    }

    void VertexBuffer::CleanupVertexBuffer()
    {
        vkDestroyBuffer(physicalDevice.GetLogicalDevice(), vertexBuffer, nullptr);
        vkFreeMemory(physicalDevice.GetLogicalDevice(), vertexBufferMemory, nullptr);
    }

    void VertexBuffer::CleanupIndexBuffer()
    {
        vkDestroyBuffer(physicalDevice.GetLogicalDevice(), indexBuffer, nullptr);
        vkFreeMemory(physicalDevice.GetLogicalDevice(), indexBufferMemory, nullptr);
    }

    void VertexBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = m_commandBuffer.GetCommandPool();
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(physicalDevice.GetLogicalDevice(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(physicalDevice.GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(physicalDevice.GetGraphicsQueue());

        vkFreeCommandBuffers(physicalDevice.GetLogicalDevice(), m_commandBuffer.GetCommandPool(), 1, &commandBuffer);
    }

} // Namespace OHE