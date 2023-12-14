#include "allocator.h"

#include "format.h"
#include "memory.h"
#include "types.h"

namespace kernel {

bool Allocator::resize(Int32 pages) {
  if (pages > m_pages) {
    if (!m_bitmap.resize((pages << PAGE_BITS) >> 3)) {
      return false;
    }
    auto ptr = (Uint8 *)mallocPages(pages);
    if (ptr == nullptr) {
      return false;
    }
    if (m_ptr != nullptr) {
      for (auto i = 0ul; i < m_pages << PAGE_BITS; i++) {
        ptr[i] = m_ptr[i];
      }
      freePages(m_ptr);
    }
    m_ptr = ptr;
    m_pages = pages;
  } else {
  }
  return true;
}

void *Allocator::malloc(Int32 bytes) {
  if (bytes <= 0) {
    return nullptr;
  }
  if (m_pages &&
      ((bytes >> PAGE_BITS) + (bytes & PAGE_MASK) ? 1 : 0) <= m_pages) {
    for (auto i = 0; i < (m_pages << PAGE_BITS); i++) {
      if (i + bytes > (m_pages << PAGE_BITS)) {
        break;
      }
      auto flag = true;
      for (auto j = i; j < (i + bytes); j++) {
        if (m_bitmap.isSet(j)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        if (!m_mallocRecord.add(m_ptr + i, bytes)) {
          return nullptr;
        }
        for (auto j = i; j < i + bytes; j++) {
          m_bitmap.set(j);
        }
        return reinterpret_cast<void *>(m_ptr + i);
      }
    }
  }
  auto pages = (bytes >> PAGE_BITS) + ((bytes & PAGE_MASK) ? 1 : 0);
  if (resize(pages > m_pages ? pages : m_pages << 1)) {
    return malloc(bytes);
  }
  return nullptr;
}
void Allocator::free(void *ptr) {
  auto bytes = m_mallocRecord.getBytesAndErase(ptr);
  for (auto i = (Uint8 *)ptr - m_ptr, j = 0l; j < bytes; j++) {
    m_bitmap.clear(i + j);
  }
}
static Allocator g_allocator;
void *malloc(Int32 bytes) { return g_allocator.malloc(bytes); }
void free(void *ptr) { g_allocator.free(ptr); }
}  // namespace kernel