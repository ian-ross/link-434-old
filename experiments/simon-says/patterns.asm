  .include "thunderboard.inc"
  .include "state-machine.inc"

  .area main

  MORSE = 150
  SWRSF = 1 << 4

button::
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
  ret

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
