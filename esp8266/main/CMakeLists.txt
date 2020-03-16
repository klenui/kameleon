idf_component_register(SRCS
  "esp8266_main.c"
  "../../src/base64.c"
  "../../src/gen/kameleon_magic_strings.c"
  "../../src/gen/kameleon_modules.c"
  "../../src/global.c"
  "../../src/io.c"
  "../../src/jerry_port.c"
  "../../src/jerryxx.c"
  "../../src/main.c"
  "../../src/modules/graphics/font_default.c"
  "../../src/modules/graphics/gc.c"
  "../../src/modules/graphics/gc_16bit_prims.c"
  "../../src/modules/graphics/gc_1bit_prims.c"
  "../../src/modules/graphics/gc_cb_prims.c"
  "../../src/modules/graphics/module_graphics.c"
  "../../src/modules/i2c/module_i2c.c"
  "../../src/modules/pwm/module_pwm.c"
  "../../src/modules/spi/module_spi.c"
  "../../src/modules/storage/module_storage.c"
  "../../src/modules/uart/module_uart.c"
  #"../../src/modules/url/__module_url.c"
  "../../src/repl.c"
  "../../src/runtime.c"
  "../../src/utils.c"
  "../../src/ymodem.c"
  "../../targets/boards/esp32-wrover-b/src/adc.c"
  "../../targets/boards/esp32-wrover-b/src/flash.c"
  "../../targets/boards/esp32-wrover-b/src/gpio.c"
  "../../targets/boards/esp32-wrover-b/src/i2c.c"
  "../../targets/boards/esp32-wrover-b/src/pwm.c"
  "../../targets/boards/esp32-wrover-b/src/spi.c"
  "../../targets/boards/esp32-wrover-b/src/storage.c"
  "../../targets/boards/esp32-wrover-b/src/system.c"
  "../../targets/boards/esp32-wrover-b/src/tty.c"
  "../../targets/boards/esp32-wrover-b/src/uart.c"
  INCLUDE_DIRS
  "../../include"
  "../../include/port"
  "../../src/gen"
  "../../src/modules/graphics"
  "../../src/modules/http"
  "../../src/modules/i2c"
  "../../src/modules/led"
  "../../src/modules/net"
  "../../src/modules/pwm"
  "../../src/modules/spi"
  "../../src/modules/spi"
  "../../src/modules/startup"
  "../../src/modules/storage"
  "../../src/modules/stream"
  "../../src/modules/uart"
  "../../src/modules/url"
  "../../src/modules/wifi"
  "../../targets/boards/esp32-wrover-b/include"
  "../../deps/jerryscript/jerry-core/include"
  "../../deps/jerryscript/jerry-core/include"
  "../../deps/jerryscript/jerry-ext/include"
  "../../deps/jerryscript/jerry-libm/include"
  "../../deps/jerryscript/jerry-port/default/include"
  "../../deps/jerryscript/targets/curie_bsp/include"
  "../../deps/jerryscript/targets/curie_bsp/jerry_app/include"
  "../../deps/jerryscript/targets/esp8266/include")

function(add_prebuilt_library target_name lib_path)
    cmake_parse_arguments(_ "" "" "REQUIRES;PRIV_REQUIRES" ${ARGN})

    get_filename_component(lib_path "${lib_path}"
                ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")

    add_library(${target_name} STATIC IMPORTED)
    set_property(TARGET ${target_name} PROPERTY IMPORTED_LOCATION ${lib_path})

    foreach(req ${__REQUIRES})
        idf_component_get_property(req_lib "${req}" COMPONENT_LIB)
        set_property(TARGET ${target_name} APPEND PROPERTY LINK_LIBRARIES "${req_lib}")
        set_property(TARGET ${target_name} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "${req_lib}")
    endforeach()

    foreach(req ${__PRIV_REQUIRES})
        idf_component_get_property(req_lib "${req}" COMPONENT_LIB)
        set_property(TARGET ${target_name} APPEND PROPERTY LINK_LIBRARIES "${req_lib}")
        set_property(TARGET ${target_name} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "$<LINK_ONLY:${req_lib}>")
    endforeach()
endfunction()

add_prebuilt_library(libjerry-core "${COMPONENT_DIR}/../components/jerryscript/libjerry-core.a")
add_prebuilt_library(libjerry-ext "${COMPONENT_DIR}/../components/jerryscript/libjerry-ext.a")
add_prebuilt_library(libjerry-port "${COMPONENT_DIR}/../components/jerryscript/libjerry-port-default.a")

target_link_libraries(${COMPONENT_LIB} PRIVATE libjerry-core libjerry-ext libjerry-port "-lm" "-lc")

