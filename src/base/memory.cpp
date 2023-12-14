#include "memory.h"

#include "format.h"
#include "platform.h"
#include "types.h"
namespace kernel {
static Memory memory;

void Memory::flushPage(Int64 page) {
  Int64* ptr = reinterpret_cast<Int64*>(KERNEL_HEAP_BASE + page * PAGE_SIZE);
  for (Int32 i = 0; i < (PAGE_SIZE >> 3); i++) {
    ptr[i] = 0;
  }
}
void* Memory::mallocPages(Int32 pages) {
  if (pages == 0) {
    return nullptr;
  }
  for (Uint32 i = 0;
       i < sizeof(m_pageFlags) && pages <= sizeof(m_pageFlags) - i; i++) {
    Uint32 count = 0;
    for (Int32 j = i; count < pages && j < sizeof(m_pageFlags); j++) {
      if (m_pageFlags[j].isAssignable()) {
        break;
      }
      count++;
    }
    if (count == pages) {
      for (Int32 j = i; j < i + count; j++) {
        m_pageFlags[j].setAssignable(true);
        flushPage(j);
      }
      auto ret = reinterpret_cast<void*>(KERNEL_HEAP_BASE + i * PAGE_SIZE);
      m_mallocRecord.add(ret, pages);
      return reinterpret_cast<void*>(KERNEL_HEAP_BASE + i * PAGE_SIZE);
    }
  }
  return nullptr;
}

bool Memory::freePages(void* ptr) {
  if ((Uint64)ptr < KERNEL_HEAP_BASE ||
      (Uint64)ptr >= KERNEL_HEAP_BASE + KERNEL_HEAP_SIZE) {
    return false;
    ;
  }
  Uint64 page = (((Uint64)ptr) - KERNEL_HEAP_BASE) / PAGE_SIZE;
  auto pages = m_mallocRecord.getPagesAndErase(ptr);
  for (Int32 i = 0; i < pages; i++) {
    m_pageFlags[page + i].setAssignable(false);
  }
  return true;
}
void* mallocPages(Int32 pages) { return memory.mallocPages(pages); }
bool freePages(void* ptr) { return memory.freePages(ptr); }
}  // namespace kernel