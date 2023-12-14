add_subdirectory(../../third_party/Catch2 build)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(unittest
    util/format_test.cpp
    ${CMAKE_SOURCE_DIR}/src/util/util.cpp
    ${CMAKE_SOURCE_DIR}/src/util/string_util.cpp
    ${CMAKE_SOURCE_DIR}/src/util/format.cpp
    base/memory_test.cpp
    ${CMAKE_SOURCE_DIR}/src/base/memory.cpp
    base/allocator_test.cpp
    ${CMAKE_SOURCE_DIR}/src/base/allocator.cpp
)

target_compile_options(unittest PRIVATE -g -O0)
target_link_options(unittest PRIVATE -g -O0)

target_include_directories(unittest PRIVATE ${CMAKE_SOURCE_DIR}/src/util ${CMAKE_SOURCE_DIR}/src/base base)

target_link_libraries(unittest PRIVATE Catch2::Catch2WithMain)
