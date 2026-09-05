---@diagnostic disable: undefined-global, undefined-field
require"vendor/river2D/premake5"

workspace("marino")
    configurations({"debug", "asan", "release"})
    platforms({"linux", "windows"})
    location("build")
    architecture("x86_64")

project("marino")
    language("C")
    cdialect("C99")
    warnings("Extra")
    targetname("marino")
    kind("ConsoleApp")
    libdirs({"./vendor/river2D/bin/%{cfg.buildcfg}/",
             "./vendor/river2D/vendor/imgsurf/bin/%{cfg.buildcfg}/"})
    includedirs({"./include/",
                 "/usr/include/",
                 "./vendor/river2D/include/",
                 "./vendor/river2D/vendor/imgsurf/include",
                 "./vendor/river2D/vendor/imgsurf/vendor/puddle/include"})
    debugdir("./")
    buildoptions({"-Wextra", "-Wall", "-Wpedantic", "-Wconversion", "-Wshadow",
                  "-Wsign-compare", "-Wtype-limits", "-Wunused"})
    links({"river2Dcommon:static", "imgsurf:static"})

    filter("configurations:asan")
        defines{"ASAN"}

    filter("configurations:debug")
        defines{"DEBUG"}

    filter("configurations:debug or asan")
        runtime("debug")
        symbols("On")
        optimize("Off")
        buildoptions({"-g", "-O0"})
        linkoptions({"-g", "-O0"})

    filter("configurations:release")
        defines{"NDEBUG"}
        staticruntime("off")
        runtime("release")
        symbols("Off")
        optimize("Speed")

    filter("platforms:linux")
        system("linux")
        defines("BUILD_LINUX")
        targetdir("bin/%{cfg.buildcfg}")
        objdir("obj/%{cfg.buildcfg}")
        files({"./src/linux_marino*",
               "./include/linux_marino*",
               "./src/marino_*",
               "./include/marino_*",
               "./vendor/river2D/vendor/imgsurf/vendor/puddle/src/linux*"})
        links({"river2Dcommon:static", "imgsurf:static"})
        linkoptions({"-lX11", "-lXrender", "-lXcursor", "-lm", "-fuse-ld=mold"})

    filter("platforms:windows")
        system("windows")
        defines("BUILD_WINDOWS")
        targetdir("bin/%{cfg.buildcfg}")
        objdir("obj/")
        files({"./src/win32_marino*",
               "./include/win32_marino*",
               "./src/marino_*",
               "./include/marino_*",
               "./vendor/river2D/vendor/imgsurf/vendor/puddle/src/win32*"})
        links({"river2Dcommon.lib", "imgsurf.lib"})

    filter({"platforms:windows", "configurations:release"})
        kind("WindowedApp")

    filter({"platforms:linux", "configurations:debug or asan"})
        buildoptions({"-gfull"})
        linkoptions({"-gfull"})

    filter({"platforms:windows", "configurations:debug or asan"})
        buildoptions({"-gcodeview"})
        linkoptions({"-gcodeview"})

    filter({"platforms:linux", "configurations:asan"})
        buildoptions({"-fsanitize=address,leak,undefined", "-fno-omit-frame-pointer",
                      "-static-libasan"})
        linkoptions({"-fsanitize=address,leak,undefined", "-fno-omit-frame-pointer",
                     "-static-libasan"})

    filter({"platforms:windows", "configurations:asan"})
        toolset("clang-cl")
        buildoptions({"/fsanitize=address", "/Zi", "/INCREMENTAL:NO"})
        linkoptions{"/link clang_rt.asan_dynamic-x86_64.lib clang_rt.asan_dynamic_runtime_thunk-x86_64.lib"}
        editandcontinue("Off")
