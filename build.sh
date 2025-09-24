#!/bin/bash
set -e
ELF_FILE="build/stm32-min.elf"

openocd \
  -d0 \
  -c "adapter speed 1800" \
  -f interface/stlink.cfg \
  -f target/stm32f4x.cfg \
  -c "transport select hla_swd" \
  -c "init" \
  -c "adapter speed 1800" \
  -c "adapter speed" \
  -c "reset halt" \
  -c "program $ELF_FILE verify" \
  -c "reset run" \
  -c "shutdown"
