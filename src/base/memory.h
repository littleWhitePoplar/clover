#pragma once

#include "platform.h"
#include "types.h"
namespace kernel {
constexpr Int32 PAGE_SIZE = 4096;
constexpr Int32 PAGE_BITS = 12;
constexpr Int32 PAGE_MASK = PAGE_SIZE - 1;

struct PageFlag {
  bool m_assignable : 1;

  bool isAssignable() { return m_assignable; }

  void setAssignable(bool assignable) { m_assignable = assignable; }
};

class Memory {
 private:
  PageFlag m_pageFlags[KERNEL_HEAP_SIZE / PAGE_SIZE];
  struct MallocRecord {
    struct PtrAndPages {
      void *m_ptr;
      Int32 m_pages;
    };
    PtrAndPages m_ptrAndPages[KERNEL_HEAP_SIZE / PAGE_SIZE];
    Int32 m_count = 0;
    void add(void *ptr, Int32 pages) {
      m_ptrAndPages[m_count].m_ptr = ptr;
      m_ptrAndPages[m_count].m_pages = pages;
      m_count++;
    }

    Int32 getPagesAndErase(void *ptr) {
      for (Int32 i = 0; i < m_count; i++) {
        if (m_ptrAndPages[i].m_ptr == ptr) {
          for (Int32 j = i; j < m_count - 1; j++) {
            m_ptrAndPages[j] = m_ptrAndPages[j + 1];
          }
          m_count--;
          return m_ptrAndPages[i].m_pages;
        }
      }
      return 0;
    }
  };
  MallocRecord m_mallocRecord;
  void flushPage(Int64 page);

 public:
  void *mallocPages(Int32 pages);
  bool freePages(void *ptr);
};

void *mallocPages(Int32 pages);
bool freePages(void *ptr);

}  // namespace kernel