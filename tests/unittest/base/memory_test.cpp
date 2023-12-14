#include "memory.h"

#include <catch2/catch_test_macros.hpp>

#include "format.h"
#include "types.h"

using namespace kernel;

TEST_CASE("Simply test if malloc is available", "[Memory]") {
  auto ptr = mallocPages(1);
  REQUIRE(ptr == KERNEL_HEAP_BASE_ARRAY);
  freePages(ptr);
}

TEST_CASE("The allocated page can no longer be allocated", "[Memory]") {
  auto ptr = mallocPages(1);
  auto ptr2 = mallocPages(1);
  REQUIRE(ptr2 == KERNEL_HEAP_BASE_ARRAY + PAGE_SIZE);
  freePages(ptr);
  freePages(ptr2);
}

TEST_CASE("free pages can be reassigned", "[Memory]") {
  freePages(mallocPages(1));
  auto ptr = mallocPages(1);
  REQUIRE(ptr == KERNEL_HEAP_BASE_ARRAY);
  freePages(ptr);
}

TEST_CASE(
    "The remaining space cannot be allocated to the number of pages requested "
    "by malloc",
    "[Memory]") {
  auto ptr = mallocPages(KERNEL_HEAP_SIZE / PAGE_SIZE);
  REQUIRE(mallocPages(1) == nullptr);
  freePages(ptr);
}

TEST_CASE("The requested page size exceeds the heap page size", "[Memory]") {
  REQUIRE(mallocPages(KERNEL_HEAP_SIZE / PAGE_SIZE + 1) == nullptr);
}

TEST_CASE("Allocatwe 0 pages", "[Memory]") {
  REQUIRE(mallocPages(0) == nullptr);
}