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
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#include "tty.h"
#include "system.h"

static fd_set readfds;
static struct timeval timeout;

void tty_init()
{
}


uint32_t tty_available()
{
  int state;
  
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);

  timeout.tv_sec = timeout.tv_usec = 0;
  state = select(1, &readfds, NULL, NULL, &timeout);
  if ( state > 0 ) return 1;

  return 0;
}

uint32_t tty_read(uint8_t *buf, size_t len)
{
  return read(0, (void*)buf, len);
}

uint32_t tty_read_sync(uint8_t *buf, size_t len, uint32_t _timeout)
{
  int state;
  
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);

  timeout.tv_sec = _timeout;
  timeout.tv_usec = 0;
  
  state = select(1, &readfds, NULL, NULL, &timeout);
  if ( state <= 0 ) return 0;

  return tty_read(buf, len);
}


uint8_t tty_getc()
{
  return getc(stdin);
}

void tty_putc(char ch)
{
  putc(ch, stdout);
}


void tty_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
