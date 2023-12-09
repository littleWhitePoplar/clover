#include <cstdlib>

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
  void flushPage(Int64 page);

 public:
  void *mallocPages(Int32 pages);
  void freePages(void *ptr, Int32 pages = 1);
};

void *mallocPages(Int32 pages);
void freePages(void *ptr, Int32 pages = 1);

}  // namespace kernel