#pragma once
#include "memory.h"
#include "types.h"
namespace kernel {
class BitMap {
 private:
  Uint64 *m_bitmap = nullptr;
  Uint64 m_bytes = 0;

 public:
  void set(Uint64 i) { m_bitmap[i >> 6] |= (1ULL << (i & 0x3F)); }
  void clear(Uint64 i) { m_bitmap[i >> 6] &= ~(1ULL << (i & 0x3F)); }
  bool isSet(Uint64 i) {
    return (m_bitmap[i / 64] & (1ULL << (i & 0x3F))) != 0;
  };
  bool resize(Uint64 bytes) {
    if (bytes <= m_bytes) {
      return true;
    }
    auto pages = (bytes >> PAGE_BITS) + ((bytes & PAGE_MASK) ? 1 : 0);
    auto bitmap = (Uint64 *)mallocPages(pages);
    if (bitmap == nullptr) {
      return false;
    }
    if (m_bitmap != nullptr) {
      for (Int32 i = 0; i < m_bytes >> 3; i++) {
        bitmap[i] = m_bitmap[i];
      }
      freePages(m_bitmap);
    }
    m_bytes = bytes;
    m_bitmap = bitmap;
    return true;
  }
};

class Allocator {
 private:
  class MallocRecord {
    struct MallocRecordEntry {
      void *ptr = nullptr;
      Uint64 bytes = 0;
    };
    MallocRecordEntry *m_entries;
    Uint64 m_size = 0;
    Uint64 getPages(Uint64 size) {
      return (size * sizeof(MallocRecordEntry)) >> PAGE_BITS;
    }
    bool resize(Uint64 size) {
      if (size <= m_size) {
        return true;
      }
      auto ptr = (MallocRecordEntry *)mallocPages(getPages(size));
      if (ptr == nullptr) {
        return false;
      }
      for (Uint64 i = 0; i < m_size; i++) {
        ptr[i] = m_entries[i];
      }
      freePages(m_entries);
      m_entries = ptr;
      m_size = size;
      return true;
    }

   public:
    bool add(void *ptr, Uint64 bytes) {
      for (Uint64 i = 0; i < m_size; i++) {
        if (m_entries[i].ptr == nullptr) {
          m_entries[i].ptr = ptr;
          m_entries[i].bytes = bytes;
          return true;
        }
      }
      auto beforeSize = m_size;
      if (!resize(m_size == 0 ? PAGE_SIZE / sizeof(MallocRecordEntry)
                              : m_size << 1)) {
        return false;
      }
      m_entries[beforeSize].ptr = ptr;
      m_entries[beforeSize].bytes = bytes;
      return true;
    }
    Uint64 getBytesAndErase(void *ptr) {
      for (Uint64 i = 0; i < m_size; i++) {
        if (m_entries[i].ptr == ptr) {
          m_entries[i].ptr = nullptr;
          return m_entries[i].bytes;
        }
      }
      return 0;
    }
  };
  Uint8 *m_ptr = nullptr;
  Int32 m_pages = 0;
  BitMap m_bitmap;
  MallocRecord m_mallocRecord;
  bool resize(Int32 pages);

 public:
  void *malloc(Int32 bytes);
  void free(void *ptr);
};
void *malloc(Int32 bytes);
void free(void *ptr);
}  // namespace kernel