add_requires("spdlog", "glfw", "glad", "glm")

if is_plat("windows") then 
  add_requires("vulkansdk")
end

target("OhmJourney")
  set_version("0.0.0")
  set_kind("binary")
  add_deps("OhmEngine")
  add_files("src/**.cpp")
  add_includedirs("../OhmEngine/include")
  add_packages("spdlog", "glfw", "glm", "glad")

  if is_plat("macosx") then
    -- don't use the xmake package thing I KNOW ugly ... need invastigation bc vulkansdk doesn't seems compatible with macos
    local vulkan_sdk_path = os.getenv("VK_SDK_PATH")
    add_includedirs(vulkan_sdk_path .. "macOS/include")
    add_linkdirs(vulkan_sdk_path .. "macOS/lib")
    add_links("vulkan")
    add_rpathdirs(vulkan_sdk_path .. "macOS/lib")
    add_defines("VK_USE_PLATFORM_METAL_EXT")
    add_frameworks("quartzcore", "AppKit")
  elseif is_plat("windows") then
    add_packages("vulkansdk")
    add_defines("NOMINMAX")
    add_defines("VK_USE_PLATFORM_WIN32_KHR")
    add_defines("GLFW_EXPOSE_NATIVE_WIN32")
	  add_syslinks("User32")
  end 

  after_install(function (target)
	end)
target_end()