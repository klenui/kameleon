#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

#include "system.h"
#include "gpio.h"
#include "tty.h"
#include "io.h"
#include "repl.h"
#include "runtime.h"

static const char* TAG = "kameleon";

void app_main()
{
  bool load = false;
  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  ESP_LOGI(TAG, "This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
	 chip_info.cores,
	 (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
	 (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  ESP_LOGI(TAG, "silicon revision %d, ", chip_info.revision);

  ESP_LOGI(TAG, "%dMB %s flash", spi_flash_get_chip_size() / (1024 * 1024),
	 (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");


  system_init();
  load = running_script_check();
  ESP_LOGI(TAG, "running_script_check returned %d", load);
  tty_init();
  io_init();
  repl_init();
  ESP_LOGI(TAG, "runtime_init(%d,true)", load);
  runtime_init(load, true);
  io_run();
}
