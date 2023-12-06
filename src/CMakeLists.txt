
set(ARCH "aarch64" CACHE STRING "Target architecture: aarch64, riscv, etc.")

# arch is valid?
if(NOT (ARCH STREQUAL "riscv" OR ARCH STREQUAL "aarch64"))
    message(FATAL_ERROR "Unsupported target architecture: ${ARCH}")
endif()

# enable asm
enable_language(ASM)

# add kernel
add_executable(kernel
    arch/${ARCH}/start.S
    arch/${ARCH}/uart.cpp
    base/kernel.cpp
    util/util.cpp
    util/string_util.cpp
    util/format.cpp
)

target_include_directories(kernel PRIVATE ${CMAKE_SOURCE_DIR}/src/arch/${ARCH} ${CMAKE_SOURCE_DIR}/src/base ${CMAKE_SOURCE_DIR}/src/util)
target_compile_options(kernel PRIVATE -nostdlib -fno-builtin -g -O0)
target_link_options(kernel PRIVATE -nostdlib -fno-builtin -g -O0)
# link os.ld
set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/arch/${ARCH}/os.ld")
set_target_properties(kernel PROPERTIES OUTPUT_NAME "kernel.elf")
set_source_files_properties(src/arch/${ARCH}/start.S PROPERTIES LANGUAGE CXX)