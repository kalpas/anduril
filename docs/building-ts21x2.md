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
