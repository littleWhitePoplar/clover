#pragma once
#include "platform.h"
#include "types.h"
namespace kernel {
class Uart {
 private:
  struct Regs {
    Uint32 UARTDR;
    Uint32 UARTRSR;
    Uint32 reserved0[4];
    const Uint32 UARTFR;
    Uint32 reserved;
    Uint32 UARTILPR;
    Uint32 UARTIBRD;
    Uint32 UARTFBRD;
    Uint32 UARTLCR_H;
    Uint32 UARTCR;
    Uint32 UARTIFLS;
    Uint32 UARTIMSC;
    Uint32 UARTRIS;
    Uint32 UARTMIS;
    Uint32 UARTICR;
    Uint32 UARTDMACR;
  };
  Regs *regs;
  static constexpr Uint32 UARTLCR_8BIT = (3 << 5);
  static constexpr Uint32 UARTLCR_ENABLE_FIFO = (1 << 4);
  static constexpr Uint32 UARTCR_UARTEN = (1 << 0);
  static constexpr Uint32 UARTCR_TXE = (1 << 8);
  static constexpr Uint32 UARTCR_RXE = (1 << 9);
  static constexpr Uint32 UARTFR_TXFF = (1 << 5);
  //   Uint32 getUartRegValue(Uint32 reg) { return *((Uint32 *)(UART + reg)); }
  //   void setUartRegValue(Uint32 reg, Uint32 value) {
  //     *((Uint32 *)(UART + reg)) = value;
  //   }

 public:
  void init();
  void putChar(char ch);
  void puts(const char *s);
};
void initUart();
void putChar(char ch);
void puts(const char *s);
}  // namespace kernel