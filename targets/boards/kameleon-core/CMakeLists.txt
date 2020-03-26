add_definitions(-DUSE_HAL_DRIVER
  -DSTM32F411xE 
  -DUSE_FULL_ASSERT)

set(SOURCE
  ${SOURCE}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/adc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ringbuffer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pwm.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tty.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_device.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_conf.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f4xx_it.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_desc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_cdc_if.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system_stm32f4xx.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f4xx_hal_msp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/flash.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/storage.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/uart.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/i2c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/spi.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
  ${CMAKE_CURRENT_SOURCE_DIR}(SHARED_DIR)/middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc)
  
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SHARED_DIR}/drivers/STM32F4xx_HAL_Driver/Inc
  ${SHARED_DIR}/drivers/STM32F4xx_HAL_Driver/Inc/Legacy
  ${SHARED_DIR}/middlewares/ST/STM32_USB_Device_Library/Core/Inc
  ${SHARED_DIR}/middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
  ${SHARED_DIR}/drivers/CMSIS/Device/ST/STM32F4xx/Include
  ${SHARED_DIR}/drivers/CMSIS/Include)

set(TARGET_HEAPSIZE 96)

ifeq ($(BOOTLOADER),1)
  TARGET_LDSCRIPT = $(TARGET_DIR)/src/STM32F411CETx_FLASH_BOOT.ld
else
  TARGET_LDSCRIPT = $(TARGET_DIR)/src/STM32F411CETx_FLASH.ld
endif

KAMELEON_MODULES='events gpio led button pwm adc i2c spi uart graphics at storage stream net http url wifi startup'

KAMELEON_MODULE_PWM = 1
KAMELEON_MODULE_I2C = 1
KAMELEON_MODULE_SPI = 1
KAMELEON_MODULE_STORAGE = 1
KAMELEON_MODULE_UART = 1
KAMELEON_MODULE_GRAPHICS = 1

