  .include "thunderboard.inc"

  ;; RESET VECTOR

  .area vectors (code,abs)
  .org 0x0000

  ljmp start


  ;; MAIN PROGRAM

  .area main


start:

  ;; DEBUGGER PAUSE

  ;; Start-up pause to give debugger a chance (150,000 cycles at 24.5/8
  ;; MHz is approx. 50 ms, which is about what we get here).
  mov r7, #150
1$:
  mov r6, #0xFF
2$:
  nop
  nop
  djnz r6, 2$                   ; 4 cycles x 255 = 1020 cycles = 330 us.
  djnz r7, 1$


  ;; BASIC SETUP

  mov sp, #0x1F

  mov   WDTCN, #0xDE
  mov   WDTCN, #0xAD

  mov P1MDOUT, #(1 << 4 | 1 << 5 | 1 << 6)
  mov P1SKIP, #(1 << 4 | 1 << 5 | 1 << 6)
  mov XBR2, #(1 << 6)


  ;; CLOCK SETUP

  ;; Clock = 24.5 MHz (HFOSC0 / 1).
  mov   CLKSEL, #0
3$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 3$

  ;; Prefetch control for high-speed operation.
  mov SFRPAGE, #0x10
  mov PFE0CN, #(1 << 4)
  mov SFRPAGE, #0x00

  ;; Clock = 48 MHz (HFOSC1 / 1).
  mov   CLKSEL, #3
4$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 4$


  ;;  BLINKY

loop:
  clr THB_LED_B
  mov a, #250
  lcall delay

  setb THB_LED_B
  mov a, #250
  lcall delay

  sjmp loop


delay::
  mov r7, a
1$:
  lcall delay_ms
  djnz r7, 1$

  ret


;; At 24.5/8 MHz, 1 ms is 3062 clock cycles (50 x 15 x 4 = 3000).

delay_ms:
  mov r6, #50
1$:
  ;; mov r5, #15
  mov r5, #120
2$:
  nop
  nop
  djnz r5, 2$
  djnz r6, 1$

  ret
