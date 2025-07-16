# Attempt to unbrick Silicon Labs EFM8UB3 Thunderboard dev board

## Situation

My EFM8UB3 Thunderboard has stopped responding to any form of
programming software. It seems that it's possible to get the chip into
a state where it's not possible for the C2 debugger on the board to
program it, possibly because the debugger is too slow at halting the
processor after resetting it.

I think that the problem has arisen because I was messing around with
clock settings on the EFM8. On the Silicon Labs forums, people
recommend putting a 100 ms or so software pause in after reset before
changing any clock settings, to give the debugger a chance to connect
to the chip.

According to the datasheet, there's a 50 μs window after releasing the
reset pin before the processor starts executing code. Maybe by being
quick we can halt the processor in that window and so erase the flash
and get it back into a working state?

I'm going to use an Arduino MKR WiFi 1010 board to try to do this.


## Resources

 - EFM8UB3 Thunderboard User Guide: https://www.silabs.com/documents/public/user-guides/ug308-sltb005a-user-guide.pdf
 - Arduino MKR WiFi 1010 pinout: https://store.arduino.cc/arduino-mkr-wifi-1010
 - EFM8 Arduino programmer code: https://github.com/conorpp/efm8-arduino-programmer



## Connections

### Thunderboard

According to the schematics for the Thunderboard, it should be
possible to use the `VMCU` pin to power the board (at 3.3V), as long
as the power source selector is set to "`DBG USB`" and no USB cable is
connected to the debugger USB port.

 - `GND`: connect to `GND` on Arduino
 - `VMCU`: connect to `VCC` on Arduino
 - `RST`
 - `P2.0`

### Arduino MKR WiFi

The `VCC` pin is a 3.3V power output, so can be used to power the
Thunderboard.

 - `GND`: connect to `GND` on Thunderboard
 - `VCC`: connect to `VMCU` on Thunderboard
 - `0`: ???
 - `1`: ???


## Arduino firmware

### Pins

 - Assign `C2D` to pin `0`: Pin `0` on the Arduino is `PA22`, i.e.
   `PORTA`, pin `22`.
 - Assign `C2CK` to pin `1`: Pin `1` on the Arduino is `PA23`, i.e.
   `PORTA`, pin `23`.
