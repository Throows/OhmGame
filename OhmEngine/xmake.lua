add_requires("spdlog", "glfw", "glad", "glm", "nlohmann_json", "fmt")

if is_plat("windows") then
  add_requires("vulkansdk")
end

target("OhmEngine")
  set_version("0.0.0")
  set_kind("static")
  add_headerfiles("**.hpp")
  add_includedirs("include")
  add_files("src/**.cpp")
  set_pcxxheader("OEpch.hpp")
  add_packages("spdlog", "glfw", "glm", "glad", "nlohmann_json", "fmt")

  if is_plat("macosx") then
    local vulkan_sdk_path = os.getenv("VK_SDK_PATH")
    add_includedirs(vulkan_sdk_path .. "/include")
    add_linkdirs(vulkan_sdk_path .. "/lib")
    add_links("vulkan")
    add_rpathdirs(vulkan_sdk_path .. "/lib")
    add_defines("VK_USE_PLATFORM_METAL_EXT")
    add_defines("GLFW_EXPOSE_NATIVE_COCOA")
    --add_frameworks("quartzcore", "AppKit")
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