add_rules("mode.debug", "mode.release")

target("test")
    add_defines("TEST", "NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc", "Test/Inc")
    add_files("Test/Src/*.c")
    add_files("Library/Src/*.c")
