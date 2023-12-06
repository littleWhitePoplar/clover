#include "string_util.h"
namespace kernel {
class Format {
 private:
  char m_buf[1024];
  int m_bufIndex = 0;
  void appendString(const char* s) {
    while (*s) {
      m_buf[m_bufIndex++] = *s++;
    }
  }
  enum class FormatType { COMMON, INVALID, PLACEHOLDER };
  FormatType formatOnce(const char*& fmt) {
    if (*fmt == '{') {
      fmt++;
      if (*fmt == '{') {
        m_buf[m_bufIndex++] = '{';
        fmt++;
      } else {
        fmt++;
        return FormatType::PLACEHOLDER;
      }
    } else if (*fmt == '}') {
      fmt++;
      if (*fmt == '}') {
        m_buf[m_bufIndex++] = '}';
        fmt++;
      } else {
        return FormatType::INVALID;
      }
    } else {
      m_buf[m_bufIndex++] = *fmt++;
    }
    return FormatType::COMMON;
  }

 public:
  char* format(const char* fmt) {
    while (*fmt) {
      switch (formatOnce(fmt)) {
        case FormatType::COMMON:
          break;
        case FormatType::INVALID:
          return nullptr;
        case FormatType::PLACEHOLDER:
          return nullptr;
      }
    }
    m_buf[m_bufIndex] = '\0';
    m_bufIndex = 0;
    return m_buf;
  }
  template <typename T>
  char* format(const char* fmt, T value) {
    while (*fmt) {
      switch (formatOnce(fmt)) {
        case FormatType::COMMON:
          break;
        case FormatType::INVALID:
          return nullptr;
        case FormatType::PLACEHOLDER:
          appendString(toString(value));
          return format(fmt);
      }
    }
    return nullptr;
  }
  template <typename T, typename... Args>
  char* format(const char* fmt, T value, Args... args) {
    while (*fmt) {
      switch (formatOnce(fmt)) {
        case FormatType::COMMON:
          break;
        case FormatType::INVALID:
          return nullptr;
        case FormatType::PLACEHOLDER:
          appendString(toString(value));
          return format(fmt, args...);
      }
    }
    return nullptr;
  }
};

Format& getFormat();
}  // namespace kernel