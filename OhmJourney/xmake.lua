
target("OhmJourney")
  set_version("0.0.0")
  set_kind("binary")
  add_deps("OhmEngine")
  add_files("src/**.cpp")
  add_includedirs("../OhmEngine/include")
  add_packages("spdlog", "glfw", "vulkansdk", "glm", "glad") 

  after_install(function (target)
	end)
target_end()