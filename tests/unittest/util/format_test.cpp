#include "format.h"

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <string>

TEST_CASE("format is vaild", "[Format]") {
  kernel::Format format;
  REQUIRE(std::string("abc") == format.format("abc"));
  REQUIRE(std::string("123") == format.format("{}", 123));
  REQUIRE(std::string("abc123") == format.format("abc{}", 123));
  REQUIRE(std::string("2147483647") == format.format("{}", 2147483647));
  REQUIRE(std::string("0") == format.format("{}", 0));
  REQUIRE(std::string("-2147483648") == format.format("{}", -2147483648));
  REQUIRE(std::string("123+456=579") ==
          format.format("{}+{}={}", 123, 456, 579));
  REQUIRE(std::string("{") == format.format("{{"));
  REQUIRE(std::string("}") == format.format("}}"));
  REQUIRE(std::string("{}") == format.format("{{}}"));
  REQUIRE(std::string("I'm Bob,I'm 23 years old\n") ==
          kernel::getFormat().format("I'm {},I'm {} years old\n", "Bob", 23));
}