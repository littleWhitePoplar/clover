#include "uart.h"

#include "util.h"
namespace kernel {
void Uart::init() {
  regs = (Regs *)UART;
  //  | UARTLCR_ENABLE_FIFO
  setReg32Value(regs->UARTLCR_H, UARTLCR_8BIT | UARTLCR_ENABLE_FIFO);
  auto reg = getReg32Value(regs->UARTCR);
  setReg32Value(regs->UARTCR, reg | UARTCR_UARTEN | UARTCR_TXE | UARTCR_RXE);
}

void Uart::putChar(char ch) {
  if (ch == '\n') putChar('\r');
  while (regs->UARTFR & UARTFR_TXFF) {
  }
  setReg32Value(regs->UARTDR, ch);
}
void Uart::puts(const char *s) {
  while (*s) {
    putChar(*s++);
  }
}
}  // namespace kernel