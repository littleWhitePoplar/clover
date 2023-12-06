#include "string_util.h"

namespace kernel {
static char buf[13];
const char* toString(int number) {
  static constexpr int INT_MIN = -2147483648;
  static constexpr char INT_MIN_CHARS[] = "-2147483648";
  int index = 0;
  if (number == INT_MIN) {
    for (int i = 0; i < sizeof(INT_MIN_CHARS); ++i) {
      buf[index++] = INT_MIN_CHARS[i];
    }
    buf[index] = 0;
    return buf;
  }

  if (number == 0) {
    buf[index++] = '0';
    buf[index] = 0;
    return buf;
  }

  if (number < 0) {
    buf[index++] = '-';
    number = -number;
  }

  char temp[12];
  int tempIndex = 0;
  while (number > 0) {
    temp[tempIndex++] = '0' + (number % 10);
    number /= 10;
  }

  while (tempIndex > 0) {
    buf[index++] = temp[--tempIndex];
  }

  buf[index] = '\0';
  return buf;
}

const char* toString(const char* s) { return s; }

}  // namespace kernel