// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include "action_layer.h"
#include "host.h"
#include "led.h"
#include "oled_driver.h"
#include "progmem.h"
#include "quantum.h"
#include "lib/oled.h"

#ifdef OLED_ENABLE


// Layer names for each layer
enum layer_names {
    _DEFAULT,
    _NUM_SYM,
    _FLASH_RGB,
    _NAV_NUM
};


oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
    oled_write_raw_P(bs_logo_img, sizeof(bs_logo_img));
    }
    return false;
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_raw_P(ergol_logo_base_img, sizeof(ergol_logo_base_img));
            break;
        case 1:
            oled_write_raw_P(ergol_logo_symbols_img, sizeof(ergol_logo_symbols_img));
            break;
        case 2:
            oled_write_raw_P(ergol_logo_bootrgb_img, sizeof(ergol_logo_bootrgb_img));
            break;
        case 3:
            oled_write_raw_P(ergol_logo_navnum_img, sizeof(ergol_logo_navnum_img));
            break;

        /*
        oled_set_cursor(0,6);
        oled_write_P(PSTR("PEPE\nBOARD\n"), false);
        oled_write_P(PSTR("-----\n"), false);
        // Host Keyboard Layer Status
        oled_write_P(PSTR("MODE\n"), false);
        oled_write_P(PSTR("\n"), false);

        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("BASE\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("NUM_SYM\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("FLASH_RGB\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("NAV_NUM\n"), false);
                break;
        }
        */
        }        
    }

    return false;
}

/*
bool oled_task_user(void) {
    
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        // Set oled cursor position
        oled_set_cursor(0, 1);

        // Switch on current active layer
        switch (get_highest_layer(layer_state)) {
            case _DEFAULT :
                oled_write_raw_P("ERGOL", sizeof("ERGOL"));
                break;
            case _NUM_SYM :
                oled_write_raw_P("NUM_SYM", sizeof("NUM_SYM"));
                break;
            case _FLASH_RGB :
                oled_write_raw_P("FLASH_RGB", sizeof("FLASH_RGB"));
                break;
            case _NAV_NUM :
                oled_write_raw_P("NAV_NUM", sizeof("NAV_NUM"));
                break;
        }

        // Capslock status
        //led_t led_state = host_keyboard_led_state();
        //oled_write_P(led_state.caps_lock ? PSTR("Capslock On") : PSTR("Capslock Off"), false);
        //oled_write_raw_P(bs_logo_img, sizeof(bs_logo_img));
    }
    
    return false;
}
*/
#endif
