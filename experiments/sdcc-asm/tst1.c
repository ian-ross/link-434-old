#include "8051.h"

__sfr __at(0xA9) CLKSEL;

__sfr __at(0xA5) P1MDOUT;
__sfr __at(0xD5) P1SKIP;

/* __sfr __at(0xE1) XBR0; */
/* __sfr __at(0xE2) XBR1; */
__sfr __at(0xE3) XBR2;

__sfr __at(0x8E) CKCON0;

__xdata unsigned int ms = 0;
__xdata unsigned int last_ms = 0;


#define SYSCLK 24500000
#define T0CLK (SYSCLK / 12)
#define FTICK 1000
#define TICK (65536 - T0CLK / FTICK)

// FLASH_MS=100 = 3s on/off cycle => FLASH_MS=1 = 15 ms
#define FLASH_MS 500

void timer_isr(void) __interrupt(1) {
  TH0 = TICK >> 8;
  TL0 = TICK & 0xFF;
  ++ms;
  if (ms - last_ms >= FLASH_MS) {
    P1 ^= 1 << 4;
    last_ms = ms;
  }
}

int main(void) {
  P1MDOUT = 1 << 4 | 1 << 5 | 1 << 6;
  P1SKIP = 1 << 4 | 1 << 5 | 1 << 6;
  XBR2 = 1 << 6;

  // CLKSEL:
  //
  //      7       6       5       4       3       2       1       0
  // | DIVRDY |        CLKDIV         |XXXXXXX|         CLKSL         |
  // |        |   0 => SYSCLK_DIV_1   |       |  3 => HFOSC1 (48 MHz) |

  // At reset, CLKDIV=3 (SYSCLK_DIV_8), CLKSL=0 (HFOSC0 => 24.5 MHz).
  // SYSCLK must be running at a frequency of 24 MHz or greater before
  // switching the CLKSL field to HFOSC1, so make two writes to
  // CLKSEL.

  // HFOSC0 / 1 = 24.5 MHz
  CLKSEL = 0;
  while (!(CLKSEL & 0x80)) { }
  // Can't get this to work yet...
  /* // HFOSC1 / 1 = 48 MHz */
  /* CLKSEL = 3; */
  /* while (!(CLKSEL & 0x80)) { } */

  // CKCON0:
  //
  //     7       6       5       4       3       2       1       0
  // | T3MH  | T3ML  | T2MH  | T2ML  |  T1M  |  T0M  |      SCA      |
  // |       |       |       |       |       |   0   |0 => SYSCLK/12 |
  //                                    0 => PRESCALE
  CKCON0 = 0;

  // TIM0: 16-bit timer
  TMOD = 1;

  // Trigger immediate interrupt.
  TH0 = 0xFF;
  TL0 = 0xFF;

  TR0 = 1;
  ET0 = 1;
  EA = 1;

  while (1) { }

  return 0;
}
