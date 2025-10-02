# Building the Wurkkos TS21x2 firmware

To build the Wurkkos TS21x2 firmware variant locally:

1. Install the AVR toolchain packages:
   ```bash
   sudo apt-get update
   sudo apt-get install gcc-avr binutils-avr avr-libc make
   ```
2. Download the required Atmel device family packs:
   ```bash
   ./make dfp
   ```
3. Compile the TS21x2 target:
   ```bash
   ./make ts21x2
   ```

The successful build produces `hex/anduril.wurkkos-ts21x2.hex` containing the updated ramping profile for the dual-7135 hardware configuration.

In stepped ramping the discrete stops are spaced to land directly on the linear-to-FET crossover, giving levels of `20, 37, 54, 71, 88, 105, 122` so the last purely regulated output is available as a stable preset. Smooth ramping adds a 500 ms “crossover gate” dwell at the same MAX_1x7135 level so the light pauses briefly before opening the FET. Moon mode always engages at the lowest smooth-ramp floor, even when the stepped ramp style is active, so a true moonlight level is available regardless of UI mode.
