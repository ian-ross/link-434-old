  .include "thunderboard.inc"
  .include "setup.inc"
  .include "state-machine.inc"
  .include "patterns.inc"


  ;; RESET VECTOR

  .area vectors (code,abs)
  .org 0x0000

  ljmp start


  ;; MAIN PROGRAM

  .area main


start:
  mov sp, #0x1F
  lcall setup

loop:
  jb THB_PB0, 1$
  lcall button
1$:
  sjmp loop


;; loop:
;;   clr THB_LED_R
;;   jb THB_PB0, 1$
;;   lcall button
;; 1$:
;;   mov a, #25
;;   lcall delay

;;   setb THB_LED_R
;;   jb THB_PB0, 2$
;;   lcall button
;; 2$:
;;   mov a, #250
;;   lcall delay
;;   mov a, #225
;;   lcall delay

;;   sjmp loop
