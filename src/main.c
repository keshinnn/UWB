#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

//紅色波浪不管，nrf connect編譯能過就行//

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static void blink(int on_ms, int off_ms) {
    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    while (1) {
        gpio_pin_set_dt(&led0, 1); k_msleep(on_ms);
        gpio_pin_set_dt(&led0, 0); k_msleep(off_ms);
    }
}

void main(void) {
#if IS_ENABLED(CONFIG_APP_ROLE_INITIATOR)
    LOG_INF("Role = INITIATOR");
    /* TODO: uwb_start_initiator(); */
    blink(150, 150);     // 快閃 = 主
#elif IS_ENABLED(CONFIG_APP_ROLE_RESPONDER)
    LOG_INF("Role = RESPONDER");
    /* TODO: uwb_start_responder(); */
    blink(600, 600);     // 慢閃 = 從
#endif
}
