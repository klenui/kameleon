set(TARGET_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(SOURCES
  ${SOURCES}
  ${TARGET_SRC_DIR}/adc.c
  ${TARGET_SRC_DIR}/flash.c
  ${TARGET_SRC_DIR}/gpio.c
  ${TARGET_SRC_DIR}/i2c.c
  ${TARGET_SRC_DIR}/pwm.c
  ${TARGET_SRC_DIR}/spi.c
  ${TARGET_SRC_DIR}/storage.c
  ${TARGET_SRC_DIR}/tty.c
  ${TARGET_SRC_DIR}/uart.c)
  
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(TARGET_HEAPSIZE 96)

#set(KAMELEON_MODULES events gpio led button pwm adc i2c spi uart graphics at storage stream net http url wifi startup)

#set(KAMELEON_MODULE_PWM 1)
#set(KAMELEON_MODULE_I2C 1)
#set(KAMELEON_MODULE_SPI 1)
#set(KAMELEON_MODULE_STORAGE 1)
#set(KAMELEON_MODULE_UART 1)
#set(KAMELEON_MODULE_GRAPHICS 1)

