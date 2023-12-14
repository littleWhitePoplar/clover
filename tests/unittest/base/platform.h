#pragma once
#include "types.h"
constexpr Uint64 KERNEL_HEAP_SIZE = MIB;
inline Uint8 KERNEL_HEAP_BASE_ARRAY[KERNEL_HEAP_SIZE];
const Uint64 KERNEL_HEAP_BASE = (Uint64)KERNEL_HEAP_BASE_ARRAY;