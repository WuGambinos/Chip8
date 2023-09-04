workspace "Chip8"
    configurations {"Debug", "Release"}

project "Chip8"
    links {"raylib"}
    links {"m"}
    links {"dl"}
    kind "WindowedApp"
    language "C"
    cdialect "C11"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj"

    files {"include/*.h"}
    files {"src/*.c"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
