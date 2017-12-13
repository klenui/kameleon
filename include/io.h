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

#ifndef __IO_H
#define __IO_H

#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

#include "jerryscript.h"

typedef struct io_loop_s io_loop_t;
typedef struct io_handle_s io_handle_t;
typedef struct io_handle_list_s io_handle_list_t;
typedef struct io_timer_handle_s io_timer_handle_t;
typedef struct io_tty_handle_s io_tty_handle_t;

/* callback function types */
typedef void (* io_close_cb)(io_handle_t *);
typedef void (* io_tty_read_cb)(char);
typedef void (* io_timer_cb)(io_timer_handle_t *);

/* handle types */
typedef enum io_type {
  IO_TIMER,
  IO_TTY
} io_type_t;

/* handle flags */
#define IO_FLAG_ACTIVE 0x01
#define IO_FLAG_CLOSING 0x02

#define IO_SET_FLAG_ON(field, flag) ((field) |= (flag))
#define IO_SET_FLAG_OFF(field, flag) ((field) &= ~(flag))
#define IO_HAS_FLAG(field, flag) ((field) & (flag))

struct io_handle_s {
  list_node_t base;
  io_type_t type;
  uint8_t flags;
  io_close_cb close_cb;
};

struct io_timer_handle_s {
  io_handle_t base;
  uint32_t timer_id;
  io_timer_cb timer_cb;
  jerry_value_t timer_js_cb;
  uint64_t clamped_timeout;
  uint64_t interval;
  bool repeat;
};

struct io_tty_handle_s {
  io_handle_t base;
  io_tty_read_cb read_cb;
};

/* loop type */
struct io_loop_s {
  bool stop_flag;
  uint64_t time;
  list_t timer_handles;
  list_t tty_handles;
  list_t closing_handles;
};

/* loop functions */
void io_init();
void io_run();

/* general handle functions */
void io_handle_init(io_handle_t *handle, io_type_t type);
void io_handle_close(io_handle_t *handle, io_close_cb close_cb);

/* timer functions */
void io_timer_init(io_timer_handle_t *timer);
void io_timer_start(io_timer_handle_t *timer, io_timer_cb timer_cb, uint64_t interval, bool repeat);
void io_timer_stop(io_timer_handle_t *timer);
io_timer_handle_t *io_timer_get_by_id(int timer_id);

/* TTY functions */
void io_tty_init(io_tty_handle_t *tty);
void io_tty_read_start(io_tty_handle_t *tty, io_tty_read_cb read_cb);
void io_tty_read_stop(io_tty_handle_t *tty);

#endif /* __IO_H */