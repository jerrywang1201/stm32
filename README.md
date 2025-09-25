# STM32-MIN

A minimal STM32F446RE project using **CMake + Ninja + arm-none-eabi-gcc**, demonstrating UART debugging output and ENS160 air quality sensor communication via I2C.

---

## Features
- **UART2 Debug Output**
  - `retarget.c` redirects `printf()` to UART2
  - Baud rate: 115200, 8-N-1
- **ENS160 Sensor Driver**
  - Communicates over I2C1
  - Reads AQI, TVOC, and eCO₂ values
- **System Initialization**
  - Configures HSI16MHz system clock
  - Initializes UART2 and I2C1
- **Build System**
  - Based on CMake + Ninja
  - Produces `.hex` and `.bin` images via `objcopy`
  - Custom linker script `STM32F446RETx_FLASH.ld`
  - Startup file `startup_stm32f446xx.s`

---

## Project Structure
```bash
STM32-MIN/
├── .vscode/ # VSCode configs (launch/tasks/settings)
├── cmake/ # Toolchain files
├── linker/ # Linker scripts
│ └── STM32F446RETx_FLASH.ld
├── modules/
│ ├── ens160/ # ENS160 driver
│ ├── i2c_lowlevel/ # Low-level I2C1 driver
│ ├── uart2/ # UART2 driver
│ ├── main.c # Main program
│ ├── retarget.c # printf redirection to UART
│ ├── system_init.c # System clock initialization
│ └── system_stub.c # Newlib syscall stubs
├── startup/
│ └── startup_stm32f446xx.s
├── build.sh # OpenOCD flashing script
├── CMakeLists.txt # Root CMake build file
└── README.md


## Build and Flash

### 1. Configure the build directory
```bash
cmake -S . -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake

cmake --build build

Build outputs:
stm32-min.elf
stm32-min.hex
stm32-min.bin

./build.sh



Dependencies
GNU Arm Embedded Toolchain
CMake
Ninja
OpenOCD


TODO
 Replace busy-wait delay loop with proper delay function
 Add ENS160 status register parsing
 Optional: FreeRTOS integration example