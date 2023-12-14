#include "allocator.h"

#include <catch2/catch_test_macros.hpp>

#include "format.h"
#include "platform.h"
#include "types.h"

TEST_CASE("Simply test if allocate is available", "[Allocator]") {
  auto ptr = (Uint8 *)kernel::malloc(128);
  REQUIRE(ptr != nullptr);
  kernel::free(ptr);
}

TEST_CASE("The allocated bytes can no longer be allocated", "[Allocator]") {
  auto ptr = (Uint8 *)kernel::malloc(128);
  auto ptr2 = (Uint8 *)kernel::malloc(128);
  REQUIRE(ptr2 == ptr + 128);
  kernel::free(ptr);
  kernel::free(ptr2);
}

TEST_CASE("free bytes can be reassigned", "[Allocator]") {
  auto ptr = (Uint8 *)kernel::malloc(128);
  kernel::free(ptr);
  auto ptr2 = (Uint8 *)kernel::malloc(128);
  REQUIRE(ptr2 == ptr);
  kernel::free(ptr2);
}

TEST_CASE(
    "The remaining space cannot be allocated to the number of bytes requested "
    "by malloc",
    "[Allocator]") {
  auto ptr = kernel::malloc(0xE0000);
  auto ptr2 = kernel::malloc(1);
  REQUIRE(ptr2 == nullptr);
  kernel::free(ptr);
}

TEST_CASE("The requested page size exceeds the heap page size", "[Allocator]") {
  auto ptr = kernel::malloc(0xE0001);
  REQUIRE(ptr == nullptr);
}

TEST_CASE("Allocate 0 bytes", "[Allocator]") {
  auto ptr = kernel::malloc(0);
  REQUIRE(ptr == nullptr);
}