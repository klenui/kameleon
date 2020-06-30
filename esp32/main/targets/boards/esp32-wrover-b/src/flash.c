/* Copyright (c) 2017 Kameleon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string.h>
#include "kameleon_core.h"
#include "flash.h"
#include "tty.h"

void flash_clear()
{
}

uint32_t flash_size()
{
  return 0;
}

const char* const timer_test_script = "print(\"in script ok\\n\");\nsetInterval(function(){ print(\"in timer ok\"); }, 1000);\nprint(\"the timer was set.\");\n\n";

const char* const gpio_test_script =
  "print(\"in script ok\\n\");"
  "var pinR = board.gpio(0, OUTPUT);"
  "var pinG = board.gpio(2, OUTPUT);"
  "var pinB = board.gpio(4, OUTPUT);"
  "setInterval(function(){ "
  "pinR.toggle();"
  "pinG.toggle();"
  "pinB.toggle();"
  "print(\"in timer ok\\n\"); "
  "}, 1000);"
  "print(\"the timer was set.\\n\");";

const char* const spi_test_script =
  "print(\"in script ok\\n\");"
  "var GPIO = require('gpio').GPIO;"
  "var SPI =require('spi').SPI;"
  "var spi0cs = new GPIO(14, OUTPUT);"
  "var spiOptions = { mode: SPI.MODE_0, baudrate: 800000, bitorder: SPI.MSB};"
  "var spi = board.spi(0, spiOptions);"
  "var array = new Uint8Array([104,101,108,108,111,0,0,0]);"
  "spi0cs.write(LOW);"
  "setInterval(function(){ "
  "spi.send(array);"
  "print(\"in timer ok\\n\"); "
  "}, 1000);"
  "print(\"the timer was set.\");";

const char* const i2c_test_script =
  "var I2C = require('i2c').I2C;"
  "print(\"in script ok\\n\");"
  "var array = new Uint8Array([79,75]);"
  "var i2c0 = new I2C(0);"
  "setInterval(function(){ "
  "i2c0.write(array, 0x28);"
  "print(\"in timer ok\\n\"); "
  "}, 1000);"
  "print(\"the timer was set.\\n\");";

const char* const adc_test_script =
  "var ADC = require('adc').ADC;"
  "print(\"in script ok\\n\");"
  "var adc = new ADC(34);"
  "setInterval(function(){ "
  "print(\"adc : \", adc.read(), \"\\n\");"
  "}, 1000);"
  "print(\"the timer was set.\\n\");";

const char* const pwm_test_script =
  "var PWM = require('pwm').PWM;"
  "print(\"in script ok\\n\");"
  "var pin = 18;"
  "var freq = 5000;"
  "var duty = 0.37;"
  "var pwm = new PWM(pin, freq, duty);"
  "pwm.start();"
  "print(\"PWM start\\n\");";

const char* const wifi_test_script =
  "print(\"in script ok\\n\");"
  "var wifi = require('wifi');"
  "wifi.scan(function(err, scanResult){"
  "if(err != null){"
  "print(\"err: \", err);"
  "} else {"
  "print(\"scanResult: \", scanResult);"
  "}});";

const char* const http_test_script = 
"print(\"in script ok\\n\");"
"const http = require('http');"
"http.get({"
"  host : '192.168.17.103',"
"  port : 8000,"
"  path : '/index.js'"
"}, (res) => {"
"  res.resume();"
"  res.on('data', (chunk) => {"
"    console.log(`Chunk : ${chunk}`);"
"  });"
"  res.on('end', () => {"
"    console.log('Done.');"
"  });"
"});"
;

const char* const storage_test_script =
"print(\"in script ok\\n\");"
"const Storage=require('storage');"
"const storage = new Storage();"
"storage.setItem('value1', 'abcd');"
"storage.setItem('value2', '1234');"
"const val1 = storage.getItem('value1');"
"const val2 = storage.getItem('value2');"
"console.log(`val1 : ${val1}`);"
"console.log(`val2 : ${val2}`);"
;

const char* const flash_test_script =
  "print(\"in script ok\\n\");"
  "var flash = require('flash');"
;


const char* const test_script = http_test_script;

uint8_t *flash_get_data()
{
  return (uint8_t*)test_script;
}

uint32_t flash_get_data_size()
{
  return (uint32_t)strlen(test_script);
}

void flash_program_begin()
{
  return;
}

flash_status_t flash_program(uint8_t * buf, uint32_t size)
{
  return FLASH_FAIL;
}

flash_status_t flash_program_byte(uint8_t val)
{
  return FLASH_FAIL;
}

void flash_program_end()
{
}

uint32_t flash_get_checksum()
{
  return 0;
}

