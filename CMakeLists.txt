cmake_minimum_required(VERSION 3.12)

project(clover)
set(ARCH "aarch64" CACHE STRING "Target architecture: aarch64, riscv, etc.")

# set compile args
set(CMAKE_CXX_FLAGS "-nostdlib -fno-builtin")

# arch is valid?
if(NOT (ARCH STREQUAL "riscv" OR ARCH STREQUAL "aarch64"))
    message(FATAL_ERROR "Unsupported target architecture: ${ARCH}")
endif()

set_source_files_properties(src/arch/${ARCH}/start.S PROPERTIES LANGUAGE CXX)

# enable asm
enable_language(ASM)

# add kernel
add_executable(kernel
    src/arch/${ARCH}/start.S
    src/arch/${ARCH}/uart.cpp
    src/base/kernel.cpp
    src/util/util.cpp
)

target_include_directories(kernel PRIVATE ${CMAKE_SOURCE_DIR}/src/arch/${ARCH} ${CMAKE_SOURCE_DIR}/src/base ${CMAKE_SOURCE_DIR}/src/util)

# link os.ld
set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/arch/${ARCH}/os.ld")
# set out name
set_target_properties(kernel PROPERTIES OUTPUT_NAME "kernel.elf")
install(TARGETS kernel DESTINATION ${CMAKE_SOURCE_DIR}/build)