//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#include <pebble.h>
#include "global.h"
#include "clock.h"
#include "utils.h"

static Layer *window_layer = 0;
static Layer *dial_layer = 0;
static tm tm_time;
static tm tm_gmt;

void draw_clock( void ) {
  time_t now = time( NULL );
  tm_time = *localtime( &now ); // copy to global
  tm_gmt = *gmtime( &now ); // copy to global
}

static void handle_clock_tick( struct tm *tick_time, TimeUnits units_changed ) {
  tm_time = *tick_time; // copy to global
  time_t now = time( NULL );
  tm_gmt = *gmtime( &now ); // copy to global
  
  #ifdef DEBUG
  APP_LOG( APP_LOG_LEVEL_INFO, "clock.c: handle_clock_tick(): %d:%d:%d", tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec );
  #endif
}

static void dial_layer_update_proc( Layer *layer, GContext *ctx ) {
  GRect bounds = layer_get_bounds( layer );
  graphics_context_set_antialiased( ctx, true );
  graphics_context_set_fill_color( ctx, GColorBlack );
  graphics_fill_rect( ctx, bounds, 0, GCornerNone );
  draw_seconds_ticks( & (DRAW_TICKS_PARAMS) { layer, ctx, &PATH_TICK, 5, 1, 12, White, Black } );
  draw_seconds_ticks( & (DRAW_TICKS_PARAMS) { layer, ctx, &PATH_TICK, 15, 3, 15, White, Black } );
  graphics_context_set_stroke_color( ctx, GColorBlack );
  graphics_context_set_stroke_width( ctx, 3 * 2 );
  graphics_draw_round_rect( ctx, bounds, 3 );
}
#define DEBUG
static void prv_unobstructed_change( AnimationProgress progress, void *context ) {
  GRect uo_bounds = layer_get_unobstructed_bounds( (Layer *) context );
  // GRect bounds = layer_get_bounds( dial_layer );
  layer_set_bounds( dial_layer, uo_bounds );
  layer_mark_dirty( dial_layer );
}

void clock_init( Window* window ){
  window_layer = window_get_root_layer( window );
  dial_layer = layer_create( CLOCK_DIAL_RECT );
  layer_set_update_proc( dial_layer, dial_layer_update_proc );
  layer_add_child( window_layer, dial_layer );

  unobstructed_area_service_subscribe( (UnobstructedAreaHandlers) { .change = prv_unobstructed_change }, window_layer );
}

void clock_deinit( void ){
  if ( dial_layer ) layer_destroy( dial_layer );
}
