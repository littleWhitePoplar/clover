#include "format.h"
#include "uart.h"
using namespace kernel;
extern "C" void startKernel() {
  initUart();
  puts("123\n");
  puts(getFormat().format("I'm {},I'm {} years old\n", "Bob", 23));
  while (1) {
  }
}