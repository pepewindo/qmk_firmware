//USB detect
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_MAX_CONNECTION_ERRORS 30
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 1000
#define SPLIT_USB_TIMEOUT_POLL 20
#define SPLIT_WATCHDOG_TIMEOUT 5000

// Don't let my OLEDs burn in
#define SPLIT_OLED_ENABLE
#define OLED_FADE_OUT
#define OLED_TIMEOUT 10000