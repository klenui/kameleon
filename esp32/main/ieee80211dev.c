#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "jerryscript.h"
#include "jerryscript-ext/handler.h"
#include "runtime.h"
#include "global.h"
#include "jerryxx.h"
#include <esp_wifi.h>
#include <esp_log.h>
#include <esp_event.h>
#include <nvs_flash.h>

#define DEFAULT_SSID "hyde"
#define DEFAULT_PWD ""
#define DEFAULT_SCAN_METHOD WIFI_FAST_SCAN
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#define DEFAULT_RSSI -127
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#define TAG ("ieee80211dev")

JERRYXX_FUN(ieee80211dev_reset_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  printf("ieee80211dev_reset_fn\n");
  return 0;
}

static void event_handler(void* arg, esp_event_base_t event_base, 
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip: %s", ip4addr_ntoa(&event->ip_info.ip));
    }
}

/* Initialize Wi-Fi as sta and set scan method */
static void wifi_scan(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
  
  tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = DEFAULT_SSID,
            .password = DEFAULT_PWD,
            .scan_method = DEFAULT_SCAN_METHOD,
            .sort_method = DEFAULT_SORT_METHOD,
            .threshold.rssi = DEFAULT_RSSI,
            .threshold.authmode = DEFAULT_AUTHMODE,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

JERRYXX_FUN(ieee80211dev_scan_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  printf("ieee80211dev_scan_fn\n");
  wifi_scan();
  return 0;
}
JERRYXX_FUN(ieee80211dev_connect_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  printf("ieee80211dev_connect_fn\n");
  return 0;
}
JERRYXX_FUN(ieee80211dev_disconnect_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  printf("ieee80211dev_disconnect_fn\n");
  return 0;
}
JERRYXX_FUN(ieee80211dev_get_connection_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  printf("ieee80211dev_get_connection_fn\n");
  return 0;
}

void register_global_ieee80211dev() {
  jerry_value_t ieee = jerry_create_object();
  jerryxx_set_property_function(ieee, "reset", ieee80211dev_reset_fn);
  jerryxx_set_property_function(ieee, "scan", ieee80211dev_scan_fn);
  jerryxx_set_property_function(ieee, "connect", ieee80211dev_connect_fn);
  jerryxx_set_property_function(ieee, "disconnect", ieee80211dev_disconnect_fn);
  jerryxx_set_property_function(ieee, "getConnection", ieee80211dev_get_connection_fn);
  jerry_value_t global = jerry_get_global_object();
  jerryxx_set_property(global, "__ieee80211dev", ieee);
  jerry_release_value(ieee);
  jerry_release_value(global);
}

