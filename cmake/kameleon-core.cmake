project(kameleon C)

set(CMAKE_SYSTEM_PROCESSOR arm)

set(PREFIX arm-none-eabi-)
set(CMAKE_C_COMPILER ${PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${PREFIX}g++)
set(CMAKE_LINKER ${PREFIX}ld)
set(CMAKE_OBJCOPY ${PREFIX}objcopy)

set(JERRY_ROOT ../deps/jerryscript)
set(JERRY_INC
  ${JERRY_ROOT}/jerry-core
  ${JERRY_ROOT}/jerry-core/api
  ${JERRY_ROOT}/jerry-core/debugger
  ${JERRY_ROOT}/jerry-core/ecma/base
  ${JERRY_ROOT}/jerry-core/ecma/builtin-objects
  ${JERRY_ROOT}/jerry-core/ecma/builtin-objects/typedarray
  ${JERRY_ROOT}/jerry-core/ecma/operations
  ${JERRY_ROOT}/jerry-core/include
  ${JERRY_ROOT}/jerry-core/jcontext
  ${JERRY_ROOT}/jerry-core/jmem
  ${JERRY_ROOT}/jerry-core/jrt
  ${JERRY_ROOT}/jerry-core/lit
  ${JERRY_ROOT}/jerry-core/parser/js
  ${JERRY_ROOT}/jerry-core/parser/regexp
  ${JERRY_ROOT}/jerry-core/vm
  ${JERRY_ROOT}/jerry-ext/arg
  ${JERRY_ROOT}/jerry-ext/include
  ${JERRY_ROOT}/jerry-libm)

set(KAMELEON_INC ../include ../include/port ../src/gen ../src/modules)
include_directories(${KAMELEON_INC} ${JERRY_INC})

set(JERRY_ARGS
  --toolchain=cmake/toolchain_mcu_stm32f4.cmake
  --lto=OFF
  --error-messages=ON
  --js-parser=ON
  --mem-heap=${TARGET_HEAPSIZE}
  --mem-stats=ON
  --snapshot-exec=ON
  --line-info=ON
  --vm-exec-stop=ON
  --profile=es2015-subset
  --jerry-cmdline=OFF
  --cpointer-32bit=ON)

set(JERRY_LIBS
  ${JERRY_ROOT}/build/lib/libjerry-core.a
  ${JERRY_ROOT}/build/lib/libjerry-ext.a)

  
add_custom_target(jerry
  WORKING_DIRECTORY ${JERRY_ROOT}
  COMMAND python tools/build.py --clean ${JERRY_ARGS}
  BYPRODUCTS ${JERRY_LIBS})

add_executable(kameleon ../src/main.c ${JERRY_LIBS})
target_link_libraries(kameleon c nosys m)
