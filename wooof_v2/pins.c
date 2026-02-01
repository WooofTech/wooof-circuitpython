// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2025 Wooof
//
// SPDX-License-Identifier: MIT

#include "shared-bindings/board/__init__.h"

static const mp_rom_map_elem_t board_module_globals_table[] = {
    CIRCUITPYTHON_BOARD_DICT_STANDARD_ITEMS

    // Status LED - Red LED on P0.24
    { MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&pin_P0_24) },
    { MP_ROM_QSTR(MP_QSTR_LED_RED), MP_ROM_PTR(&pin_P0_24) },
    { MP_ROM_QSTR(MP_QSTR_LED_BLUE), MP_ROM_PTR(&pin_P0_05) },
    { MP_ROM_QSTR(MP_QSTR_LED_GREEN), MP_ROM_PTR(&pin_P0_04) },

    // UART pins for debug/programming
    { MP_ROM_QSTR(MP_QSTR_TX), MP_ROM_PTR(&pin_P1_09) },
    { MP_ROM_QSTR(MP_QSTR_RX), MP_ROM_PTR(&pin_P1_08) },

    // I2C pins for accelerometer
    { MP_ROM_QSTR(MP_QSTR_SDA), MP_ROM_PTR(&pin_P0_08) },
    { MP_ROM_QSTR(MP_QSTR_SCL), MP_ROM_PTR(&pin_P0_13) },
    { MP_ROM_QSTR(MP_QSTR_I2C_SDA), MP_ROM_PTR(&pin_P0_08) },
    { MP_ROM_QSTR(MP_QSTR_I2C_SCL), MP_ROM_PTR(&pin_P0_13) },

    // Battery pins
    {MP_ROM_QSTR(MP_QSTR_READ_BATT_ENABLE), MP_ROM_PTR(&pin_P0_14)},
    {MP_ROM_QSTR(MP_QSTR_VBATT), MP_ROM_PTR(&pin_P0_31)},
    {MP_ROM_QSTR(MP_QSTR_CHARGE_STATUS), MP_ROM_PTR(&pin_P0_17)},

    { MP_ROM_QSTR(MP_QSTR_PDM_CLK), MP_ROM_PTR(&pin_P0_22) },
    { MP_ROM_QSTR(MP_QSTR_PDM_DATA), MP_ROM_PTR(&pin_P0_21) },

    { MP_ROM_QSTR(MP_QSTR_BUTTON), MP_ROM_PTR(&pin_P1_00) },
    { MP_ROM_QSTR(MP_QSTR_RESET), MP_ROM_PTR(&pin_P1_00) },

    // Raw pin access (P0.xx format)
    { MP_ROM_QSTR(MP_QSTR_P0_04), MP_ROM_PTR(&pin_P0_04) }, 
    { MP_ROM_QSTR(MP_QSTR_P0_05), MP_ROM_PTR(&pin_P0_05) }, 
    { MP_ROM_QSTR(MP_QSTR_P0_08), MP_ROM_PTR(&pin_P0_08) }, 
    { MP_ROM_QSTR(MP_QSTR_P0_13), MP_ROM_PTR(&pin_P0_13) }, 
    { MP_ROM_QSTR(MP_QSTR_P0_14), MP_ROM_PTR(&pin_P0_14) }, 
    { MP_ROM_QSTR(MP_QSTR_P0_17), MP_ROM_PTR(&pin_P0_17) },
    { MP_ROM_QSTR(MP_QSTR_P0_19), MP_ROM_PTR(&pin_P0_19) },
    { MP_ROM_QSTR(MP_QSTR_P0_20), MP_ROM_PTR(&pin_P0_20) },
    { MP_ROM_QSTR(MP_QSTR_P0_21), MP_ROM_PTR(&pin_P0_21) },
    { MP_ROM_QSTR(MP_QSTR_P0_22), MP_ROM_PTR(&pin_P0_22) },
    { MP_ROM_QSTR(MP_QSTR_P0_23), MP_ROM_PTR(&pin_P0_23) },
    { MP_ROM_QSTR(MP_QSTR_P0_24), MP_ROM_PTR(&pin_P0_24) },
    { MP_ROM_QSTR(MP_QSTR_P0_31), MP_ROM_PTR(&pin_P0_31) },
    { MP_ROM_QSTR(MP_QSTR_P1_00), MP_ROM_PTR(&pin_P1_00) },
    { MP_ROM_QSTR(MP_QSTR_P1_08), MP_ROM_PTR(&pin_P1_08) },
    { MP_ROM_QSTR(MP_QSTR_P1_09), MP_ROM_PTR(&pin_P1_09) },

    { MP_ROM_QSTR(MP_QSTR_UART), MP_ROM_PTR(&board_uart_obj) },
    { MP_ROM_QSTR(MP_QSTR_I2C), MP_ROM_PTR(&board_i2c_obj) },
};

MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);
