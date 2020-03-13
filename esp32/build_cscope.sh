#!/bin/bash

find main -name "*.c" > cscope.files
find ../src -name "*.c" >> cscope.files
find ../deps -name "*.c" >> cscope.files
find ../targets/boards/esp32-wrover-b -name "*.c" >> cscope.files
find ../targets/boards/kameleon-core -name "*.c" >> cscope.files

find main -name "*.h" >> cscope.files
find ../src -name "*.h" >> cscope.files
find ../deps -name "*.h" >> cscope.files
find ../targets/boards/esp32-wrover-b -name "*.h" >> cscope.files
find ../targets/boards/kameleon-core -name "*.h" >> cscope.files

cscope -b
