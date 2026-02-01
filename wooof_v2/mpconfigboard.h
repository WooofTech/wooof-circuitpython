// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2025 Wooof
//
// SPDX-License-Identifier: MIT

#pragma once

#include "nrfx/hal/nrf_gpio.h"

#define MICROPY_HW_BOARD_NAME       "WooofV2"
#define MICROPY_HW_MCU_NAME         "nRF52840"

// Crystal configuration - 32MHz only, no 32kHz crystal
#define BOARD_HAS_32KHZ_XTAL        (0)
#define BOARD_HAS_XTAL              (1)

// Status LED - Red LED on P0.24
#define MICROPY_HW_LED_STATUS       (&pin_P0_24)

// UART pins for debug/programming
#define MICROPY_HW_UART_TX          (&pin_P1_09)
#define MICROPY_HW_UART_RX          (&pin_P1_08)

// Default I2C bus for accelerometer
#define DEFAULT_I2C_BUS_SCL         (&pin_P0_13)
#define DEFAULT_I2C_BUS_SDA         (&pin_P0_08)

// Default UART bus (same as debug UART)
#define DEFAULT_UART_BUS_RX         (&pin_P1_08)
#define DEFAULT_UART_BUS_TX         (&pin_P1_09)

// Console UART for debug output - THIS IS THE KEY FIX!
#define CIRCUITPY_CONSOLE_UART_TX   (&pin_P1_09)
#define CIRCUITPY_CONSOLE_UART_RX   (&pin_P1_08)

// Power management - enable DCDC for better efficiency
#define MICROPY_HW_ENABLE_DCDC      (1)

// Flash configuration handled by mpconfigboard.mk
