  .area main (rel,con)

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
  mov r5, #15
2$:
  nop
  nop
  djnz r5, 2$
  djnz r6, 1$

  ret
