# Simon Says

Simple pattern copying game.

## Gameplay

Game starts immediately on reset.

Red LED = "right" = button `BTN0`
Green LED = "left" = button `BTN1`

Thunderboard plays a sequence of red/green LED blinks. Player has to
replicate sequence on buttons. Sequence length starts at 3, increases
by one (adding to the end of the previous sequence) each round, up to
a limit of 10.

Successfully replicating the 10 blink sequence wins the round (rainbow
win display). Sequence starts again at length 3, with faster blink
frequency.

Failing to replicate sequence (pressing wrong button or exceeding
timeout) loses round (fading red LED lose display).


## Software structure

Simple state machine; all transitions driven off 1 ms timer tick; each
state has associated tick count.

### FSM states

Blink (`blink-ms`) and pause (`pause-ms`) durations depend on `speed`.

BEFORE-DISPLAY([1000ms], sequence, speed)
 Entry:
  - All LEDs off.
 Events:
  - Tick timeout => DISPLAY-BLINK([blink-ms], sequence, speed, 0)

DISPLAY-BLINK([blink-ms], sequence, speed, index)
 Entry:
  - LED corresponding to sequence[index] on.
  - Other LEDs off.
 Events:
  - Tick timeout => DISPLAY-PAUSE([blink-ms], sequence, speed, 0)

DISPLAY-PAUSE([blink-ms], sequence, speed, index)
 Entry:
  - All LEDs off.
 Events:
  - Tick timeout =>
      if index+1 < len(sequence):
        DISPLAY-BLINK([blink-ms], sequence, blink-ms, index+1)
      else:
        BUTTON-WAIT([10 * blink-ms], sequence, blink-ms, 0)

BUTTON-WAIT([10 * blink-interval-ms], sequence, blink-interval-ms, blink-index)
 Events:
  - Tick timeout => LOSE
  - Button =>

ROUND-WIN([5000ms], sequence, blink-interval-ms)
 Events:
  - Tick timeout => BEFORE-DISPLAY([1000ms], sequence:new-value, speed+1)

LOSE([no-timeout])


## Sub-tasks

 - 1 ms timer tick => blinky using tick timer
    * Get 48 MHz clock initialisation working
    * Set up 1 ms timer tick
    * In ISR, increment timer count
    * Use timer count to time blinky

 - Random number generation => random count blinky
    * Build on previous
    * Generate random integer N in [1, 10]
    * Blink N times at fixed rate (100-250 ms)
    * Wait 1000 ms
    * Repeat

 - Random sequence generation and play
    * Generate random 10-bit bit sequence
    * Play sequence at selected rate on red/green LEDs
    * Wait 1000 ms
    * Repeat

 - Button debouncing
    * Generate random integer N in [1, 5]
    * Blink red LED N times
    * Wait for N button presses
    * Long blink green LED
    * Repeat

 - Detect button press sequence with timeout
 - State machine
 - Full game


## 1 ms timer tick => blinky using tick timer

### Get 48 MHz clock initialisation working (`clock-setup`)

There's a specific sequence of operations you need to follow to get
the MCU running on the 48 MHz HFOSC1 oscillator. This is because the
EFM8UB3 has some restrictions on transitions between different clock
setups, and there's some additional configuration you need to do for
high-speed operation.

When the MCU is restarted, it runs from the HFOSC0 24.5 MHz oscillator
with a prescaler of 8, meaning that the system clock is running at
24.5/8 = 3.0625 MHz. To switch from this state to a state where the
MCU is running off the 48 MHz HFOSC1 oscillator requires three steps:

1. You must put the MCU into a state where its clock is running at a
   frequency of 24 MHz or more. The EFM8UB3 reference manual (Section
   8.4.1) says: "This device family has restrictions when switching to
   clock sources that are greater than 25 MHz. SYSCLK must be running
   at a frequency of 24 MHz or greater before switching the CLKSL
   field to HFOSC1. When transitioning from slower clock frequencies,
   firmware should make two writes to CLKSEL."

   The easiest thing to do here is to switch to using the 24.5 MHz
   HFOSC0 oscillator with a prescaler of 1, which gives a system clock
   of 24.5 MHz, fast enough to allow us to switch to a higher
   frequency. We do this as follows (we need to wait for the clock
   setup to stabilise after changing the value of the `CLKSEL` clock
   source selection SFR):

```
  ;; Clock = 24.5 MHz (HFOSC0 / 1).
  mov   CLKSEL, #0
3$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 3$
```

2. Before we can activate the 48 MHz HFOSC1 oscillator, we need to
   make one additional change. This is to enable the prefetch engine
   in the MCU core. This is a piece of circuitry that helps to deal
   with differences in speed between the MCU core and the EFM8UB3's
   internal flash memory. The prefetch engine batch fetches
   multiple instructions from flash memory, allowing the processor
   core to run at full speed (for code without branches).

   To set the prefetch engine up (Sections 10.3.2 and 10.4.7 in the
   EFM8UB3 reference manual), we need to write a particular value to
   the `PFE0CN` SFR. This register is on SFR page `0x10`, so we need
   to use the `SFRPAGE` register to switch pages:

```
  ;; Prefetch control for high-speed operation.
  mov SFRPAGE, #0x10
  mov PFE0CN, #(1 << 4)
  mov SFRPAGE, #0x00
```

3. Finally, we can set up the `CLKSEL` register to use the 48 MHz
   HFOSC1 oscillator with a prescaler of 1, so the system clock will
   be 48 MHz (again, we need to wait for the oscillator system to
   stabilise):

```
  ;; Clock = 48 MHz (HFOSC1 / 1).
  mov   CLKSEL, #3
4$:                             ; Wait for stabilisation.
  mov   a, CLKSEL
  jnb   acc.7, 4$
```


### 1 ms timer tick (`1ms-tick`)

There are three steps to get this going:

**THERE IS WORKING C CODE IN ~/SS5/EFM8UB3_Timer0_16bit**

1. Set up a 1 ms timer tick: this is

#### In ISR, increment timer count

#### Use timer count to time blinky
