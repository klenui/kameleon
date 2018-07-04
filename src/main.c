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

#include "system.h"
// #include "gpio.h"
// #include "led.h"
#include "tty.h"
// #include "io.h"
// #include "repl.h"
// #include "runtime.h"

#include "duktape.h"

int main(void) {
  system_init();
  tty_init();
  // io_init();
  // runtime_init(false);
  // repl_init();
  // io_run();

  tty_printf("started...\r\n");

  duk_context *ctx = duk_create_heap_default();
  duk_eval_string(ctx, "1+2");
  int result = (int) duk_get_int(ctx, -1);
  duk_destroy_heap(ctx);

  while (1) {
    tty_printf("1+2=%d\r\n", result);
    delay(1000);
  }
}
