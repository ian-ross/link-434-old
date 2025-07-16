  .include "thunderboard.inc"

  .area code1 (abs)
  .org 0x0000

  ljmp start


  .org 0x0100

start::
  mov WDTCN, #0xDE
  mov WDTCN, #0xAD

  mov P1MDOUT, #(1 << 4 | 1 << 5 | 1 << 6)
  mov P1SKIP, #(1 << 4 | 1 << 5 | 1 << 6)
  mov XBR2, #(1 << 6)

loop:
  clr THB_LED_G
  mov a, #250
  lcall delay

  setb THB_LED_G
  mov a, #250
  lcall delay

  sjmp loop


delay:
  mov r7, a
1$:
  lcall delay_ms
  djnz r7, 1$

  ret


;; At 24.5/8 MHz, 1 ms is 3062 clock cycles (50 x 15 x 4 = 3000).

delay_ms:
  mov r6, #50
1$:
  mov r5, #15
2$:
  nop
  nop
  djnz r5, 2$
  djnz r6, 1$

  ret
