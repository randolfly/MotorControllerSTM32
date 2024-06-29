add_rules("mode.debug", "mode.release")

target("test-ringbuffer")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Test/Inc")
    add_files("Library/Src/Util/ringbuffer.c")
    add_files("Test/Src/Util/ringbuffer_test.c")

target("test-byte_operator")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Test/Inc")
    add_files("Library/Src/Util/byte_operator.c")
    add_files("Test/Src/Util/byte_operator_test.c")

target("test-task_scheduler")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Test/Inc")
    add_files("Library/Src/Util/task_scheduler.c")
    add_files("Test/Src/Util/task_scheduler_test.c")
    
target("test-protocol")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Test/Inc")
    add_files("Library/Src/Util/*.c", "Library/Src/Protocol/protocol.c")
    add_files("Test/Src/Protocol/protocol_test.c")

target("test-protocol_parser")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Test/Inc")
    add_files("Library/Src/Util/*.c", "Library/Src/Protocol/*.c")
    add_files("Test/Src/Protocol/protocol_parser_test.c")

target("test-encoder_velocity_diff")
    add_defines("TEST_RANDOLF","NON_STM32")
    set_kind("binary")
    add_includedirs("Library/Inc/", "Matlab/" , "Test/Inc")
    add_files("Library/Src/Controller/*.c", "Matlab/EncoderVelocityDiff.c")
    add_files("Test/Src/Controller/encoder_velocity_diff_test.c")