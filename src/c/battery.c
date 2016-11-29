//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#include <pebble.h>
#include "battery.h"

static BatteryChargeState charge_state;

static void batt_gauge_update_proc( BatteryChargeState state ) {
  charge_state = state;
}

static void battery_layer_update_proc( Layer *layer, GContext *ctx ) {
  GRect bounds = layer_get_bounds( layer );
  graphics_context_set_fill_color( ctx, GColorBlue );
  graphics_fill_rect( ctx, bounds, 0, GCornerNone );
}

void battery_init( Layer* parent_layer ) {
  battery_layer = layer_create( BATTERY_GAUGE_FRAME );
  layer_set_update_proc( battery_layer, battery_layer_update_proc );
  layer_add_child( parent_layer, battery_layer );
  
  batt_gauge_update_proc( battery_state_service_peek() );
  battery_state_service_subscribe( batt_gauge_update_proc );
}

void battery_deinit( void ) {
  if ( battery_layer ) layer_destroy( battery_layer );
}