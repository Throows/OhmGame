#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#ifdef _WIN32
#include <vulkan/vulkan_win32.h>
#elif __APPLE__
#include <vulkan/vulkan_metal.h>
#endif

#include "OhmEngine/Core/Logger.hpp"