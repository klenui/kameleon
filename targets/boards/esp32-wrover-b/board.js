global.board = {
  name: 'esp32-wrover-b',
  NUM_GPIO: 0,
  NUM_LED: 0,
  NUM_BUTTON: 0,
  NUM_PWM: 0,
  NUM_ADC: 0,
  NUM_I2C: 0,
  NUM_SPI: 0,
  NUM_UART: 0,
  led_pins: [],
  button_pins: [],
  pwm_pins: [],
  adc_pins: [],
  gpio: function (pin, mode) {
      return null;
  },
  led: function (pin) {
      return null;
  },
  button: function (pin, pull, debounce) {
      return null;
  },
  pwm: function (pin, frequency, duty) {
      return null;
  },
  adc: function (pin) {
      return null;
  },
  i2c: function (bus, mode, mode_option) {
      return null;
  },
  spi: function (bus, options) {
      return null;
  },
  uart: function (port, options) {
      return null;
  },
  get LED0() {
      return null;
  },
  get BTN0() {
      return null;
  }
}
