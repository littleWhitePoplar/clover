#pragma once
#include "platform.h"
namespace kernel {
/*
 * about uart:
 * [1] http://byterunner.com/16550.html
 */
class Uart {
 private:
  static constexpr Uint8 RHR = 0;  // Receive Holding Register(READ MODE)
  static constexpr Uint8 THR = 0;  // Transmit Holding Register(WRITE MODE)
  static constexpr Uint8 DLL =
      0;  // LSB of Divisor Latch when Enabled(WRITE MODE)
  static constexpr Uint8 IER = 1;  // Interrupt Enable Register(WRITE MODE)
  static constexpr Uint8 DLM =
      1;  // MSB of Divisor Latch when Enabled(WRITE MODE)
  static constexpr Uint8 FCR = 2;  // FIFO control Register(WRITE MODE)
  static constexpr Uint8 ISR = 2;  // Interrupt Status Register(READ MODE)
  static constexpr Uint8 LCR = 3;  // Line Control Register(WRITE MODE)
  static constexpr Uint8 MCR = 4;  // Modem Control Register(WRITE MODE)
  static constexpr Uint8 LSR = 5;  // Line Status Register(READ MODE)
  static constexpr Uint8 MSR = 6;  // Modem Status Register(READ MODE)
  static constexpr Uint8 SPR = 7;  //  Scratchpad Register Read/Write

  static constexpr Uint8 LSR_TX_IDLE = (1 << 5);

  static constexpr Uint8 ENABLE_DIVISOR_LATCH = (1 << 7);

  Uint8 getUartRegValue(Uint8 reg) { return *((Uint8 *)(UART + reg)); }
  void setUartRegValue(Uint8 reg, Uint8 value) {
    *((Uint8 *)(UART + reg)) = value;
  }

  bool lsrTxIdle() { return getUartRegValue(LSR) & LSR_TX_IDLE; }

  void disableInterrupts() { setUartRegValue(IER, 0x0); }

  void enableDivisorLatch() {
    setUartRegValue(LCR, getUartRegValue(LCR) | ENABLE_DIVISOR_LATCH);
  }
  /*
   * Set the Divisor Latch to 0x0001 to bring the baud rate up to 115.2K
   * see[1] "BAUD RATE GENERATOR PROGRAMMING TABLE"
   */
  void iniBaudRate() {
    enableDivisorLatch();
    setUartRegValue(DLL, 0x01);
    setUartRegValue(DLM, 0x00);
  }
  /*
   * Setting the async data communication format
   * number of the word length: 8 bits
   * number of stop bits: 1
   * disable parity
   * disable break
   * disable divisor latch
   */
  void iniCommunicationFormat() { setUartRegValue(LCR, 0x3); }

  void putChar(char ch) {
    while (!lsrTxIdle()) {
    };
    setUartRegValue(THR, ch);
  }

 public:
  Uart();
  void puts(const char *s);

 private:
  Uart(const Uart &) = delete;
  Uart &operator=(const Uart &) = delete;
};
}  // namespace kernel