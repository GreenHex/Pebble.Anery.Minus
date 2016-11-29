//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#include <pebble.h>
#include "battery.h"
#include "utils.h"

static BatteryChargeState charge_state;

static void batt_gauge_update_proc( BatteryChargeState state ) {
  charge_state = state;
}

static void battery_layer_update_proc( Layer *layer, GContext *ctx ) {
  GRect bounds = layer_get_bounds( layer );
  graphics_context_set_antialiased( ctx, true );

  graphics_context_set_fill_color( ctx, GColorBlack );
  graphics_fill_rect( ctx, bounds, 0, GCornerNone );
  
  GPath *gpath = gpath_create( &BATT_GAUGE_TICK ); 
  gpath_move_to( gpath, BATTERY_GAUGE_TICK_POS );
  graphics_context_set_stroke_width( ctx, 1 );
  gpath_rotate_to( gpath, DEG_TO_TRIGANGLE( 0 ) );
  graphics_context_set_stroke_color( ctx, GColorLightGray );
  gpath_draw_outline( ctx, gpath );
  gpath_rotate_to( gpath, DEG_TO_TRIGANGLE( BATTERY_GAUGE_MAX_ANGLE_DEG ) );
  graphics_context_set_stroke_color( ctx, GColorKellyGreen );
  gpath_draw_outline( ctx, gpath );
  gpath_rotate_to( gpath, DEG_TO_TRIGANGLE( -BATTERY_GAUGE_MAX_ANGLE_DEG ) );
  graphics_context_set_stroke_color( ctx, GColorOrange );
  gpath_draw_outline( ctx, gpath );
  gpath_destroy( gpath );
  
  uint32_t batt_angle = DEG_TO_TRIGANGLE( (uint32_t) ( ( charge_state.charge_percent * 40 ) / 100 ) + 250 );
  GPoint battery_hand = (GPoint) {
    .x = ( sin_lookup( batt_angle ) * BATT_HAND_LENGTH / TRIG_MAX_RATIO ) + BATTERY_GAUGE_PIVOT.x,
    .y = ( -cos_lookup( batt_angle ) * BATT_HAND_LENGTH / TRIG_MAX_RATIO ) + BATTERY_GAUGE_PIVOT.y
  };
  
  draw_clock_hand( & (HAND_DRAW_PARAMS) {
    .ctx = ctx,
    .center_pt = BATTERY_GAUGE_PIVOT,
    .from_pt = BATTERY_GAUGE_PIVOT,
    .to_pt = battery_hand,
    .hand_width = 1,
    .hand_colour = GColorDarkGray,
    .hand_outline_colour = GColorBlack,
    .dot_radius = BATT_GAUGE_DOT_RADIUS,
    .dot_colour = GColorDarkGray,
    .dot_outline_colour = GColorBlack
  } );
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