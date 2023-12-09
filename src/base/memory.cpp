#include "memory.h"

#include "format.h"
#include "platform.h"
#include "types.h"
#include "uart.h"
namespace kernel {
static Memory memory;

void Memory::flushPage(Int64 page) {
  Int64* ptr = reinterpret_cast<Int64*>(KERNEL_HEAP_BASE + page * PAGE_SIZE);
  for (Int32 i = 0; i < PAGE_SIZE; i += 8) {
    ptr[i] = 0;
  }
}
void* Memory::mallocPages(Int32 pages) {
  for (Uint32 i = 0; i < sizeof(m_pageFlags); i++) {
    Uint32 count = 0;
    for (Int32 j = i; count < pages && j < sizeof(m_pageFlags); j++, count++) {
      if (m_pageFlags[j].isAssignable()) {
        break;
      }
    }
    if (count == pages) {
      for (Int32 j = i; j < i + count; j++) {
        m_pageFlags[j].setAssignable(true);
        flushPage(j);
      }

      return reinterpret_cast<void*>(KERNEL_HEAP_BASE + i * PAGE_SIZE);
    }
  }
  return nullptr;
}

void Memory::freePages(void* ptr, Int32 pages) {
  if ((Uint64)ptr < KERNEL_HEAP_BASE ||
      (Uint64)ptr >= KERNEL_HEAP_BASE + KERNEL_HEAP_SIZE) {
    return;
  }
  Uint64 page = (((Uint64)ptr) - KERNEL_HEAP_BASE) / PAGE_SIZE;
  for (Int32 i = 0; i < pages; i++) {
    m_pageFlags[page + i].setAssignable(false);
  }
}
void* mallocPages(Int32 pages) { return memory.mallocPages(pages); }
void freePages(void* ptr, Int32 pages) { memory.freePages(ptr, pages); }
}  // namespace kernel