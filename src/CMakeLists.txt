# enable asm
enable_language(ASM)

# add kernel
add_executable(kernel
    base/start.S
    base/main.S
    dev/uart.S
)

target_compile_options(kernel PRIVATE -nostdlib -fno-builtin -g -O0)
target_link_options(kernel PRIVATE -nostdlib -fno-builtin -g -O0)
set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/base/os.ld")
set_target_properties(kernel PROPERTIES OUTPUT_NAME "kernel.elf")