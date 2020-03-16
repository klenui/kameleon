#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "system.h"
#include "gpio.h"
#include "tty.h"
#include "io.h"
#include "repl.h"
#include "runtime.h"

void app_main()
{
  bool load = false;
  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
	 chip_info.cores,
	 (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
	 (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  printf("silicon revision %d, ", chip_info.revision);

  printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
	 (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");


  system_init();
  load = running_script_check();
  printf("running_script_check returned %d\n", load);
  io_init();
  repl_init();
  printf("runtime_init(%d,true)\n", load);
  runtime_init(load, true);
  io_run();
}
