#define MASTER_LEFT

// USB detect
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 1000
#define SPLIT_USB_TIMEOUT_POLL 20
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 5000
#define SPLIT_MAX_CONNECTION_ERRORS 30
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500

// Don't let my OLEDs burn in
#define SPLIT_OLED_ENABLE
#define OLED_FADE_OUT
#define OLED_TIMEOUT 10000

// Tapping Term for cool people
#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY
// #define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define ONESHOT_TIMEOUT 2000 /* Time (in ms) before the one shot key is released */

// Mouse emulation
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_0 2
#define MK_C_OFFSET_1 8

// Cold reboot mitigation
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 174 // 8192 / 47 = max 174

// hold for Shift/Backspace key
#define PERMISSIVE_HOLD_PER_KEY
