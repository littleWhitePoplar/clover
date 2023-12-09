#pragma once
#include "types.h"
namespace kernel {
constexpr Uint64 UART = 0x09000000;
constexpr Uint64 STACK_BOTTOM = GIB + 4 * MIB;
constexpr Uint64 KERNEL_HEAP_BASE = STACK_BOTTOM;
constexpr Uint64 KERNEL_HEAP_SIZE = GIB + 128 * MIB - KERNEL_HEAP_BASE;
}  // namespace kernel