add_requires("spdlog", "glfw", "glad", "glm", "vulkansdk", "nlohmann_json", "fmt")

target("OhmEngine")
  set_kind("static")
  add_headerfiles("**.hpp")
  add_includedirs("include")
  add_files("src/**.cpp")
  add_defines("VK_USE_PLATFORM_WIN32_KHR")
	add_syslinks("user32")
  set_pcxxheader("OEPCH.hpp")

  add_packages("spdlog", "glfw", "vulkansdk", "glm", "glad", "nlohmann_json", "fmt") 
  add_syslinks("vulkan-1")

  after_install(function (target)
	end)
  
target_end()