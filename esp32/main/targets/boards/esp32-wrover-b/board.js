global.board = {
  name: 'esp-wrover-kit',
  NUM_GPIO: 22,
  NUM_LED: 3,
  NUM_BUTTON: 0,
  NUM_PWM: 0,
  NUM_ADC: 0,
  NUM_I2C: 2,
  NUM_SPI: 2,
  NUM_UART: 0,
    led_pins: [0,2,4],
  button_pins: [],
  pwm_pins: [],
  adc_pins: [],
  gpio: function (pin, mode) {
    var GPIO = global.require('gpio').GPIO;
    return new GPIO(pin, mode);
  },
  led: function (pin) {
    var LED = global.require('led').LED;
    return new LED(pin);
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
    if (!this._led0) {
      var LED = global.require('led').LED;
      this._led0 = new LED(this.led_pins[0]);
    }
    return this._led0
  },
  get LED1() {
    if (!this._led1) {
      var LED = global.require('led').LED;
      this._led1 = new LED(this.led_pins[1]);
    }
    return this._led1
  },
    get LED2() {
    if (!this._led2) {
      var LED = global.require('led').LED;
      this._led2 = new LED(this.led_pins[2]);
    }
    return this._led2
  },
  get BTN0() {
      return null;
  }
}
