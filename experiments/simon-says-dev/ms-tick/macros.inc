
  ar0 = 0x00
  ar1 = 0x01
  ar2 = 0x02
  ar3 = 0x03
  ar4 = 0x04
  ar5 = 0x05
  ar6 = 0x06
  ar7 = 0x07

  .macro loadx16  rhi, rlo, addr
  mov   dptr, #addr
  movx  a, @dptr
  mov   rlo, a
  inc   dptr
  movx  a, @dptr
  mov   rhi, a
  .endm

  .macro storex16  addr, rhi, rlo
  mov   dptr, #addr
  mov   a, rlo
  movx  @dptr, a
  mov   a, rhi
  inc   dptr
  movx  @dptr, a
  .endm

  .macro sub16  rhi1, rlo1, rhi2, rlo2
  mov   a, rlo2
  clr   c
  subb  a, rlo1
  mov   rlo1, a
  mov   a, rhi2
  subb  a, rhi1
  mov   rhi1, a
  .endm

  .macro test16  rhi, rlo, cmp
  clr   c
  mov   a, rlo
  subb  a, #<cmp
  mov   a, rhi
  subb  a, #>cmp
  .endm

  .macro incx16  addr
  mov   dptr, #addr
  movx  a, @dptr
  add   a, #1
  movx  @dptr, a
  inc   dptr
  movx  a, @dptr
  addc  a, #0
  movx  @dptr, a
  .endm

  ;; .macro saveregs  a1, a2, a3
  ;;   .irp arg ^/a1/, ^/a2/, ^/a3/
  ;;     .ifnb ^/arg/
  ;;       push arg
  ;;     .endif
  ;;   .endm
  ;; .endm
