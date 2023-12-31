add_rules("mode.debug", "mode.releasedbg", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

set_allowedplats("windows") --"linux", "macosx")
set_allowedmodes("debug", "releasedbg", "release")
set_defaultmode("debug")
set_runtimes("MD")

set_languages("c17", "cxx23")
set_rundir("./bin/$(plat)_$(arch)_$(mode)")
set_symbols("debug", "hidden")
set_targetdir("./bin/$(plat)_$(arch)_$(mode)")
set_warnings("allextra")

set_optimize("fast")

set_project("OhmGame")

includes("OhmEngine/*.lua")
includes("OhmJourney/*.lua")
