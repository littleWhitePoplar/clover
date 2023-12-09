#include "allocator.h"

#include "format.h"
#include "types.h"
#include "uart.h"

namespace kernel {

void Allocator::resize(Int32 pages) {
  if (pages > m_pages) {
    auto ptr = (Uint8 *)mallocPages(pages);
    if (m_ptr != nullptr) {
      for (auto i = 0ul; i < m_pages << PAGE_BITS; i++) {
        ptr[i] = m_ptr[i];
      }
      freePages(m_ptr, m_pages);
    }
    m_ptr = ptr;
    m_pages = pages;
    m_bitmap.resize((pages << PAGE_BITS) >> 3);
  }
}

void *Allocator::malloc(Int32 bytes) {
  // find a continuous space of size in bitmap
  for (auto i = 0; i < m_pages << PAGE_BITS; i++) {
    auto flag = true;
    for (auto j = i; j < (i + bytes) && j < (m_pages << PAGE_BITS); j++) {
      if (m_bitmap.isSet(j)) {
        flag = false;
        break;
      }
    }
    if (flag) {
      for (auto j = i; j < i + bytes; j++) {
        m_bitmap.set(j);
      }
      m_ptrAndSizePairs.add(m_ptr + i, bytes);
      return reinterpret_cast<void *>(m_ptr + i);
    }
  }
  if (m_pages == 0) {
    // m_pages = 1;
    resize(1);
  } else {
    resize(m_pages << 1);
  }
  return malloc(bytes);
}
void Allocator::free(void *ptr) {
  auto bytes = m_ptrAndSizePairs.getSize(ptr);
  for (auto i = (Uint8 *)ptr - m_ptr, j = 0l; j < bytes; j++) {
    m_bitmap.clear(i + j);
  }
}
static Allocator g_allocator;
void *malloc(Int32 bytes) { return g_allocator.malloc(bytes); }
void free(void *ptr) { g_allocator.free(ptr); }
}  // namespace kernel