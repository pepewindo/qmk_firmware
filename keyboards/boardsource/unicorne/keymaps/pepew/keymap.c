#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "quantum.h"
#include "lib/oled.h"

// Layer names for each layer
enum layers {
    _BASE,
    _SYMB_FUNC,
    _BOOT_RGB,
    _NAV_NUM
};


static const char PROGMEM ergol_logo_img[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x38, 0x1c, 0x1c, 0x0c, 
    0x8c, 0xce, 0xee, 0xe6, 0x72, 0x78, 0x7c, 0xfc, 0xfe, 0xfe, 0x3f, 0x03, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x63, 0x30, 0x38, 0x3c, 0xbe, 0x1f, 0x1f, 
    0x1f, 0x1f, 0x7f, 0xff, 0xfe, 0xfc, 0xfe, 0x7f, 0x1f, 0x03, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3f, 0x3b, 0x18, 0x08, 
    0x0c, 0x00, 0x00, 0x7f, 0x3f, 0x0f, 0x03, 0x18, 0x1c, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x38, 0x1c, 0x1c, 0x0c, 0x8c, 0xce, 0xee, 
    0xe6, 0x72, 0x78, 0x7c, 0xfc, 0xfe, 0xfe, 0x3f, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x63, 0x30, 0x38, 0x3c, 0x9e, 0x1f, 0x1f, 0x1f, 0x1f, 0x7f, 
    0xff, 0xfe, 0xfc, 0xfe, 0x7f, 0x1f, 0x03, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7c, 0x3f, 0x3b, 0x18, 0x0c, 0x0c, 0x00, 0x00, 
    0x7f, 0x3f, 0x0f, 0x03, 0x18, 0x1c, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xc0, 0x70, 0x38, 0x1c, 0x0e, 0x8e, 0x86, 0xc6, 0xe7, 0xf7, 0xf3, 0x39, 0x3c, 
    0x3e, 0xfe, 0xff, 0xff, 0x1f, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x23, 0x11, 0x18, 0x1c, 0x9e, 0xcf, 0x0f, 0x0f, 0x0f, 0x0f, 0x3f, 0xff, 0xff, 0xfe, 
    0xff, 0x3f, 0x0f, 0x81, 0xc0, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x1d, 0x0c, 0x04, 0x06, 0x00, 0x00, 0x3f, 0x1f, 0x07, 
    0x01, 0x0c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


static const char PROGMEM ergol_logo_base_img[] = {
// 'ergo-l_logo_base', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x60, 0x70, 0x30, 0x30, 0x38, 0xb8, 
0x98, 0xc8, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x8e, 0xc3, 0xe1, 0xf0, 0xf8, 0x7c, 0x7c, 0x7e, 0x7f, 0xff, 
0xff, 0xf9, 0xf1, 0xf9, 0xff, 0x7f, 0x0f, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0xe0, 0xfc, 0xee, 0x60, 0x30, 0x30, 0x40, 0x01, 
0xff, 0xff, 0x3f, 0x0f, 0x61, 0x70, 0x38, 0x1e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0xff, 0x01, 0x21, 
0x23, 0x3e, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0x08, 0x08, 
0x08, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xdb, 0x89, 
0x89, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xb0, 
0x10, 0x31, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x09, 
0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xac, 0x22, 
0x22, 0xb6, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM ergol_logo_symbols_img[] = {
// 'ergo-l_logo_symbols', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x60, 0x70, 0x30, 0x30, 0x38, 0xb8, 
0x98, 0xc8, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x8e, 0xc3, 0xe1, 0xf0, 0xf8, 0x7c, 0x7c, 0x7e, 0x7f, 0xff, 
0xff, 0xf9, 0xf1, 0xf9, 0xff, 0x7f, 0x0f, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0xe0, 0xfc, 0xee, 0x60, 0x30, 0x30, 0x40, 0x01, 
0xff, 0xff, 0x3f, 0x0f, 0x61, 0x70, 0x38, 0x1e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x33, 0x3f, 0x1f, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x33, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, 0x80, 0xf0, 0xf0, 0x70, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x20, 0x30, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x1f, 0x1f, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xc0, 0x00, 0x80, 0xe0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x07, 0x1f, 0x1f, 0x07, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xb0, 0xb0, 0xf0, 0xf0, 0x60, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x19, 0x19, 0x1f, 0x1f, 0x0f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xd8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM ergol_logo_bootrgb_img[] = {
// 'ergo-l_logo_bootrgb', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x60, 0x70, 0x30, 0x30, 0x38, 0xb8, 
0x98, 0xc8, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x8e, 0xc3, 0xe1, 0xf0, 0xf8, 0x7c, 0x7c, 0x7e, 0x7f, 0xff, 
0xff, 0xf9, 0xf1, 0xf9, 0xff, 0x7f, 0x0f, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0xe0, 0xfc, 0xee, 0x60, 0x30, 0x30, 0x40, 0x01, 
0xff, 0xff, 0x3f, 0x0f, 0x61, 0x70, 0x38, 0x1e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xfe, 0x62, 0x22, 0x22, 0x22, 0xfe, 0xcc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xdc, 0xfe, 0x22, 0x22, 0x62, 0xe2, 0xfe, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x82, 0x82, 0x82, 0x82, 0x03, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x20, 0x20, 0x31, 0x1f, 0x0e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x7c, 0xfe, 0x83, 0x01, 0x11, 0x11, 0x93, 0xf6, 0x60, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x10, 0x10, 0x30, 0xe0, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0xc4, 0xc4, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xee, 0xff, 0x11, 0x11, 0x11, 0x11, 0xff, 0xe6, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0x7f, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM ergol_logo_navnum_img[] = {
// 'ergo-l_logo_navnum', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x60, 0x70, 0x30, 0x30, 0x38, 0xb8, 
0x98, 0xc8, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x8e, 0xc3, 0xe1, 0xf0, 0xf8, 0x7c, 0x7c, 0x7e, 0x7f, 0xff, 
0xff, 0xf9, 0xf1, 0xf9, 0xff, 0x7f, 0x0f, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0xe0, 0xfc, 0xee, 0x60, 0x30, 0x30, 0x40, 0x01, 
0xff, 0xff, 0x3f, 0x0f, 0x61, 0x70, 0x38, 0x1e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x78, 0xf0, 0xe0, 0xc0, 0xfc, 0xfc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x7c, 0xf0, 0xe0, 0xc0, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xfe, 0x9e, 0xbe, 0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x7e, 0xfe, 0x80, 0x80, 0xfe, 0x7e, 0x1e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfc, 0xe0, 0xe0, 0xf8, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_ESC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              MO(1),    KC_A,    KC_S,    CTL_T(KC_D),   KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LGUI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_END,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LALT, LT(3,KC_BSPC), KC_SPC,     KC_ENT, KC_RALT, KC_RSFT
                                            //`--------------------------'  `--------------------------'
        ),
      
    [_SYMB_FUNC] = LAYOUT_split_3x6_3(
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS, 
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_TRNS,   TG(2),   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, 
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LALT, LT(3,KC_NO), KC_TRNS,     KC_ENT, KC_RALT, KC_RSFT
                                            //`--------------------------'  `--------------------------'
        ),

    [_BOOT_RGB] = LAYOUT_split_3x6_3(
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  EE_CLR,                      RGB_VAI, RGB_HUI, RGB_SAI, RGB_MOD, RGB_TOG, KC_TRNS, 
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      RGB_VAD, RGB_HUD, RGB_SAD,RGB_RMOD, RGB_M_T,   TO(0), 
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
                                            //`--------------------------'  `--------------------------'
        ),

    [_NAV_NUM] = LAYOUT_split_3x6_3(
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_TAB, KC_LALT, KC_HOME,   KC_UP,  KC_END, KC_PGUP,                      KC_PMNS,   KC_P7,   KC_P8,   KC_P9, KC_PSLS,  KC_ESC, 
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_CAPS, KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                      KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PAST,  KC_DEL, 
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_PSCR, KC_MUTE, KC_VOLD, KC_VOLU, KC_WBAK, KC_WFWD,                       KC_DOT,   KC_P1,   KC_P2,   KC_P3,  KC_EQL, KC_CALC, 
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                 KC_INS,   KC_NO,   KC_NO,     KC_ENT,   KC_P0, KC_RSFT
                                            //`--------------------------'  `--------------------------'
        )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_raw_P(ergol_logo_base_img, sizeof(ergol_logo_base_img));
            break;
        case _SYMB_FUNC:
            oled_write_raw_P(ergol_logo_symbols_img, sizeof(ergol_logo_symbols_img));
            break;
        case _BOOT_RGB:
            oled_write_raw_P(ergol_logo_bootrgb_img, sizeof(ergol_logo_bootrgb_img));
            break;
        case _NAV_NUM:
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
                oled_write_P(PSTR("SYMB_FUNC\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("BOOT_RGB\n"), false);
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



#endif // OLED_ENABLE




