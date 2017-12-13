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

#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

typedef enum {
  GPIO_PIN_MODE_INPUT,
  GPIO_PIN_MODE_OUPUT_PP,
  GPIO_PIN_MODE_OUPUT_OD,
  GPIO_PIN_MODE_AF_PP,
  GPIO_PIN_MODE_AF_OD
} gpio_mode_t;


typedef enum {
  POLARITY_LOW_PHASE_1EDGE,
  POLARITY_LOW_PHASE_2EDGE,
  POLARITY_HIGH_PHASE_1EDGE,
  POLARITY_HIGH_PHASE_2EDGE,
}SPI_CLK_MODE;

#define GPIO_LOW 0
#define GPIO_HIGH 1

void gpio_set_gpio_mode(uint8_t pin, gpio_mode_t mode);
void gpio_write(uint8_t pin, uint8_t value);
void gpio_toggle(uint8_t pin);
uint8_t gpio_read(uint8_t pin);

#define IS_GPIO_SPI_PIN(PIN) (((PIN) == 5) || \
                              ((PIN) == 6) || \
                              ((PIN) == 7) || \
                              ((PIN) == 8))

#define IS_GPIO_I2C_PIN(PIN) (((PIN) == 8) || \
                              ((PIN) == 9))

#define IS_GPIO_PWM_PIN(PIN) (((PIN) == 10) || \
                              ((PIN) == 11))
#endif /* __GPIO_H */