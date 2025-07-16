  .include "thunderboard.inc"

  .area code1 (abs)
  .org 0x0000

  ljmp start


  .area main (rel,con)

  .globl delay

start:
  mov WDTCN, #0xDE
  mov WDTCN, #0xAD

  mov P1MDOUT, #(1 << 4 | 1 << 5 | 1 << 6)
  mov P1SKIP, #(1 << 4 | 1 << 5 | 1 << 6)
  mov XBR2, #(1 << 6)

loop:
  clr THB_LED_B
  jnb THB_PB0, button
  mov a, #250
  lcall delay

  setb THB_LED_B
  jnb THB_PB0, button
  mov a, #250
  lcall delay

  sjmp loop

  MORSE = 150
  SWRSF = 1 << 4

gap:
  mov a, #MORSE
  lcall delay
  ret

dash:
  clr THB_LED_G
  acall gap
  acall gap
  acall gap
  setb THB_LED_G
  acall gap
  ret

dot:
  clr THB_LED_G
  acall gap
  setb THB_LED_G
  acall gap
  ret

button:
  acall gap
  acall gap

  ;; B = -...
  acall dash
  acall dot
  acall dot
  acall dot

  acall gap
  acall gap

  mov r0, #0xA5
  mov RSTSRC, #SWRSF
  sjmp loop
