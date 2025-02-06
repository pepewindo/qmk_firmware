#define MASTER_LEFT

//USB detect
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000
//#define SPLIT_MAX_CONNECTION_ERRORS 10
//#define SPLIT_CONNECTION_CHECK_TIMEOUT 500

// Don't let my OLEDs burn in
#define SPLIT_OLED_ENABLE
#define OLED_FADE_OUT
#define OLED_TIMEOUT 10000

// Tapping Term for cool people
#define TAPPING_TERM 300
//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */