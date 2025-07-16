  .include "thunderboard.inc"
  .include "macros.inc"

  .area main

  SYSCLK = 48000000             ; System clock.
  T0CLK = SYSCLK / 12           ; Timer 0 clock.
  FTICK = 20000                 ; Timer tick frequency.
  TICK = 65536 - T0CLK / FTICK  ; Tick timer reload value.


;;; Set up clocks and all peripherals.

setup::
  ;; Disable watchdog -- feed it once and wait a little while first
  ;; (erratum WDT_E102).
;;   mov   WDTCN, #0xA5
;;   mov   r0, #30
;; 1$:
;;   nop
;;   djnz  r0, 1$
;;   mov   c, EA
;;   clr   EA
  mov   WDTCN, #0xDE
  mov   WDTCN, #0xAD
  ;; mov   EA, c

  ;; LEDs as outputs.
  mov   P1MDOUT, #(1 << 4 | 1 << 5 | 1 << 6)
  mov   P1SKIP, #(1 << 4 | 1 << 5 | 1 << 6)
  mov   XBR2, #(1 << 6)

  ;; Buttons as inputs.
;;; TODO: FILL IN

  ;; Clock = 24.5 MHz (HFOSC0 / 1).
  mov   CLKSEL, #0
2$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 2$

  ;; Prefetch control for high-speed operation.
  mov SFRPAGE, #0x10
  mov PFE0CN, #(1 << 4)
  mov SFRPAGE, #0x00

  ;; Clock = 48 MHz (HFOSC1 / 1).
  mov   CLKSEL, #3
3$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 3$

  ;; 1 kHz tick timer.
  mov   CKCON0, #0              ; TIM0: runs off SYSCLK/12 (4 MHz).
  mov   TMOD, #1                ; TIM0: 16-bit timer.
  mov   TH0, #0xFF              ; TIM0: immediate overflow.
  mov   TL0, #0xFF
  setb  TR0                     ; TIM0: run.
  setb  ET0
  setb  EA

  ret


  ;; TIM0 INTERRUPT VECTOR

  .area xdata (XDATA)

ms::
  .ds 2
last_ms::
  .ds 2


  .area vectors (abs,code)
  .org 0x000B

  ljmp  tick


  .area main

  FLASH_MS = 100

tick:
  ;; save acc, dpl, dph, ar7, ar6, ar5, ar4, psw
  push  acc
  push  dpl
  push  dph
  push  ar7
  push  ar6
  push  ar5
  push  ar4
  push  psw
  mov   psw, #0

  ;; Reset timer.
  mov   TH0, #>TICK
  mov   TL0, #<TICK

  ;; Increment 16-bit ms counter.
  incx16 ms

  ;;  Check for passing FLASH_MS ms since last change of LED state.
  loadx16 r7, r6, last_ms       ; r7:r6 = last_ms
  loadx16 r5, r4, ms            ; r5:r4 = ms
  sub16   r7, r6, r5, r4        ; r7:r6 = ms - last_ms
  test16 r7, r6, FLASH_MS       ; Test r7:r6 - FLASH_MS
  jc    1$                      ; C => r7:r6 < FLASH_MS

  ;; No C => ms - last_ms >= FLASH_MS

  ;; Toggle blue LED.
  cpl   THB_LED_B

  ;; Save last LED toggle time.
  storex16  last_ms, r5, r4     ; lastms = r5:r4

1$:
  ;; restore acc, dpl, dph, ar7, ar6, ar5, ar4, psw
  pop   psw
  pop   ar4
  pop   ar5
  pop   ar6
  pop   ar7
  pop   dph
  pop   dpl
  pop   acc

  reti
