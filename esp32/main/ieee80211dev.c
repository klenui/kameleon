#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "jerryscript.h"
#include "jerryscript-ext/handler.h"
#include "runtime.h"
#include "global.h"
#include "jerryxx.h"

JERRYXX_FUN(ieee80211dev_reset_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  return 0;
}

JERRYXX_FUN(ieee80211dev_scan_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  return 0;
}
JERRYXX_FUN(ieee80211dev_connect_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  return 0;
}
JERRYXX_FUN(ieee80211dev_disconnect_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  return 0;
}
JERRYXX_FUN(ieee80211dev_get_connection_fn) {
  JERRYXX_CHECK_ARG_FUNCTION(0, "callback");
  jerry_value_t callback = JERRYXX_GET_ARG(0);
  return 0;
}

void register_global_ieee80211dev() {
  jerry_value_t ieee = jerry_create_object();
  jerryxx_set_property_function(ieee, "reset", ieee80211dev_reset_fn);
  jerryxx_set_property_function(ieee, "scan", ieee80211dev_scan_fn);
  jerryxx_set_property_function(ieee, "connect", ieee80211dev_connect_fn);
  jerryxx_set_property_function(ieee, "disconnect", ieee80211dev_disconnect_fn);
  jerryxx_set_property_function(ieee, "getConnection", ieee80211dev_get_connection_fn);
  jerry_value_t global = jerry_get_global_object();
  jerryxx_set_property(global, "__ieee80211dev", ieee);
  jerry_release_value(ieee);
  jerry_release_value(global);
}

