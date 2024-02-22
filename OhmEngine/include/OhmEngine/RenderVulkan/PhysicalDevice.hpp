#pragma once

namespace OHE
{

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class PhysicalDevice
    {
    public:
        PhysicalDevice();
        ~PhysicalDevice();

        void PickPhysicalDevice(VkInstance &instance);
        void CreateLogicalDevice(bool enableValidationLayers);
        void DestroyLogicalDevice();

    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;

        bool IsDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
} // namespace OHE