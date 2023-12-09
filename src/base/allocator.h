
#include "memory.h"
#include "types.h"
namespace kernel {
class BitMap {
 private:
  Uint64 *m_bitmap = nullptr;
  Uint64 m_bytes = 0;
  Uint64 m_pages = 0;

 public:
  void set(Uint64 i) { m_bitmap[i >> 6] |= (1ULL << (i & 0x3F)); }
  void clear(Uint64 i) { m_bitmap[i >> 6] &= ~(1ULL << (i & 0x3F)); }
  bool isSet(Uint64 i) {
    return (m_bitmap[i / 64] & (1ULL << (i & 0x3F))) != 0;
  };
  void resize(Uint64 bytes) {
    if (bytes <= m_bytes) {
      return;
    }
    auto pages = (bytes >> PAGE_BITS) + (bytes & PAGE_MASK) ? 1 : 0;
    auto bitmap = (Uint64 *)mallocPages(pages);
    if (m_bitmap != nullptr) {
      for (Int32 i = 0; i < m_bytes >> 3; i++) {
        bitmap[i] = m_bitmap[i];
      }
      freePages(m_bitmap, m_pages);
    }
    m_bytes = bytes;
    m_pages = pages;
    m_bitmap = bitmap;
  }
};

class Allocator {
 private:
  class PtrAndSizePairs {
    struct PtrAndSizePair {
      void *ptr = nullptr;
      Uint64 size = 0;
    };
    constexpr static Int32 S_SIZE = PAGE_SIZE / sizeof(PtrAndSizePair);
    Uint64 m_current = 0;
    PtrAndSizePair m_ptrs[S_SIZE];

   public:
    void add(void *ptr, Uint64 size) {
      m_ptrs[m_current].ptr = ptr;
      m_ptrs[m_current].size = size;
      m_current = (m_current + 1) % S_SIZE;
    }
    Uint64 getSize(void *ptr) {
      for (Uint64 i = 0; i < S_SIZE; i++) {
        if (m_ptrs[i].ptr == ptr) {
          return m_ptrs[i].size;
        }
      }
      return 0;
    }
  };
  Uint8 *m_ptr = nullptr;
  Int32 m_pages = 0;
  BitMap m_bitmap;
  PtrAndSizePairs m_ptrAndSizePairs;
  void resize(Int32 pages);

 public:
  void *malloc(Int32 bytes);
  void free(void *ptr);
};
void *malloc(Int32 bytes);
void free(void *ptr);
}  // namespace kernel