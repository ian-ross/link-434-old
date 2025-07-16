  .area main

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


  ;; Timer running at 48 MHz: 16 bits => 1.365 ms

  ;; F_TIMER0 = F_SYSCLK / (2^16 - TH0:TL0)
  ;; 1000 = 48000000 / (2^16 - TH0:TL0)
  ;; 2^16 - TH0:TL0 = 48000
  ;; 65536 - 48000 = TH0:TL0
  ;; TH0:TL0 = 17536
