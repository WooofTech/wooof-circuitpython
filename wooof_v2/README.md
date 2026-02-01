# Wooof V2 CircuitPython Board

Custom CircuitPython board definition for the Wooof V2 Pet Health Monitor, based on the nRF52840 SoC.

## Features

- nRF52840 with BLE support (SoftDevice S140 v7.0.1)
- No USB (battery-optimized, BLE-only communication)
- Internal flash filesystem
- I2C for accelerometer
- UART for debug/programming
- PDM microphone support
- RGB status LED
- Battery monitoring with charge status

## Pin Mapping

| Function | Pin |
|----------|-----|
| LED (Red/Status) | P0.24 |
| LED (Green) | P0.04 |
| LED (Blue) | P0.05 |
| UART TX | P1.09 |
| UART RX | P1.08 |
| I2C SDA | P0.08 |
| I2C SCL | P0.13 |
| PDM CLK | P0.22 |
| PDM DATA | P0.21 |
| Button/Reset | P1.00 |
| Battery Enable | P0.14 |
| Battery Voltage | P0.31 |
| Charge Status | P0.17 |

## Pre-built Firmware

Pre-built hex files are available in the `firmware/` directory:

- `firmware.hex` - CircuitPython firmware only
- `s140_nrf52_7.0.1_softdevice.hex` - Nordic SoftDevice BLE stack
- `combined.hex` - Ready-to-flash combined image

## Building from Source

### Prerequisites (Fedora)

```bash
# Install build dependencies
sudo dnf install git git-lfs make gcc gettext cmake ninja-build \
    python3 python3-pip python3-virtualenv python3-devel

# Download ARM GCC 14.2.Rel1 toolchain (required for CircuitPython 10.x)
cd ~
wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
tar xf arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz

# Add to PATH (add to ~/.bashrc for persistence)
export PATH="$HOME/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin:$PATH"

# Verify installation
arm-none-eabi-gcc --version  # Should show 14.2.1
```

### Clone CircuitPython

```bash
cd ~
git clone https://github.com/adafruit/circuitpython.git
cd circuitpython
git submodule update --init --recursive
```

### Set up Python Environment

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install -r requirements-dev.txt
pip install -r requirements-doc.txt
```

### Build mpy-cross

```bash
make -C mpy-cross
```

### Install Board Definition

Copy the `wooof_v2` directory to the CircuitPython ports:

```bash
cp -r /path/to/this/repo/wooof_v2 ~/circuitpython/ports/nordic/boards/
```

### Build Firmware

```bash
cd ~/circuitpython/ports/nordic
source ../../.venv/bin/activate
make BOARD=wooof_v2
```

Output files will be in `build-wooof_v2/`:
- `firmware.hex`
- `firmware.uf2`
- `firmware.bin`

## Deployment

### Combine with SoftDevice

The nRF52840 requires the Nordic SoftDevice (BLE stack) to be flashed alongside the firmware.

Using Nordic's `mergehex` (from nRF Command Line Tools):

```bash
cd ~/circuitpython/ports/nordic
mergehex -m bluetooth/s140_nrf52_7.0.1/s140_nrf52_7.0.1_softdevice.hex \
    build-wooof_v2/firmware.hex \
    -o build-wooof_v2/combined.hex
```

Alternatively, using `srec_cat` (from srecord package):

```bash
sudo dnf install srecord
srec_cat bluetooth/s140_nrf52_7.0.1/s140_nrf52_7.0.1_softdevice.hex -intel \
    build-wooof_v2/firmware.hex -intel \
    -o build-wooof_v2/combined.hex -intel
```

### Flash with nrfjprog

```bash
nrfjprog --program build-wooof_v2/combined.hex --chiperase --verify --reset
```

Or flash components separately:

```bash
# Flash SoftDevice first
nrfjprog --program bluetooth/s140_nrf52_7.0.1/s140_nrf52_7.0.1_softdevice.hex --chiperase --verify

# Then flash firmware
nrfjprog --program build-wooof_v2/firmware.hex --verify --reset
```

### Verify Flash

```bash
nrfjprog --memrd 0x26000 --n 16  # Should show firmware start
nrfjprog --reset
```

## Memory Layout

| Region | Start | Size | Description |
|--------|-------|------|-------------|
| MBR | 0x00000 | 4 KB | Master Boot Record |
| SoftDevice | 0x01000 | 152 KB | S140 v7.0.1 BLE Stack |
| Firmware | 0x27000 | 524 KB | CircuitPython |
| BLE Config | - | 32 KB | BLE bonding data |
| NVM | - | 8 KB | Non-volatile storage |
| Filesystem | - | 256 KB | Internal flash filesystem |

## Serial Console

Since USB is disabled, use UART for the CircuitPython REPL:

- **TX**: P1.09
- **RX**: P1.08
- **Baud**: 115200

Connect a USB-to-serial adapter and use your preferred terminal:

```bash
screen /dev/ttyUSB0 115200
# or
minicom -D /dev/ttyUSB0 -b 115200
```

## Troubleshooting

### Build Errors

**"No rule to make target"**: Ensure submodules are initialized:
```bash
git submodule update --init --recursive
```

**Toolchain not found**: Verify ARM GCC is in PATH:
```bash
which arm-none-eabi-gcc
```

### Flash Errors

**"Overlapping segments detected"**: The SoftDevice version doesn't match. This board requires S140 v7.0.1. Ensure `SOFTDEV_VERSION = 7.0.1` is set in `mpconfigboard.mk`.

**"Could not connect to device"**: Check J-Link connection and that the device is powered.

### Runtime Issues

**No REPL output**: Check UART wiring (TX/RX may need swapping) and baud rate (115200).

**BLE not working**: Ensure the SoftDevice was flashed before/with the firmware.

## License

Board definition files are MIT licensed. See CircuitPython repository for full licensing details.

CircuitPython is Copyright (c) 2013-2024 Damien P. George, Paul Sokolovsky, and contributors.
