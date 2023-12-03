#include "uart.h"
using namespace kernel;
extern "C" void startKernel() {
  Uart uart;
  uart.init();
  uart.puts("123\n");
  while (1) {
  }
}