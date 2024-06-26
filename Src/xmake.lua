add_rules("mode.debug", "mode.release")

target("test-protocol")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc", "Test/Inc")
    add_files("Library/Src/protocol.c")
    add_files("Test/Src/protocol_test.c")
    
target("test-byte_operator")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc", "Test/Inc")
    add_files("Library/Src/byte_operator.c")
    add_files("Test/Src/byte_operator_test.c")

target("test-motor")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc", "Test/Inc")
    add_files("Library/Src/motor.c","Library/Src/motor_util.c")
    add_files("Test/Src/motor_test.c")