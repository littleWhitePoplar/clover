#include "uart.h"
namespace kernel {
Uart::Uart() {
  disableInterrupts();
  iniBaudRate();
  iniCommunicationFormat();
}
void Uart::puts(const char *s) {
  while (*s) {
    putChar(*s++);
  }
}
}  // namespace kernel