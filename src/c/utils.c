//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#include <pebble.h>
#include "utils.h"

// function is "adjusted"" for whole hours or minutes; "after" 9:00 AM or "upto" 9:00 AM.
// "after" includes the hour, "upto" excludes the hour.
bool is_X_in_range( int a, int b, int x ) { return ( ( b > a ) ? ( ( x >= a ) && ( x < b ) ) : ( ( x >= a ) || ( x < b ) ) ); };

void print_pt( char *str, GPoint pt ) {
  #ifdef DEBUG
  APP_LOG( APP_LOG_LEVEL_INFO, "%s: ( %d, %d )", str, pt.x, pt.y );
  #endif
}

void print_rect( char *str, GRect rect ) {
  #ifdef DEBUG
  APP_LOG( APP_LOG_LEVEL_INFO, "%s: ( %d, %d, %d, %d )", str, rect.origin.x, rect.origin.y, rect.size.w, rect.size.h );
  #endif
}

void draw_seconds_ticks( DRAW_TICKS_PARAMS *pDTP ) {
  GRect bounds = layer_get_bounds( pDTP->layer );
  GPoint center_pt = grect_center_point( &bounds );
  GPath *gpath = gpath_create( pDTP->p_gpath_info );
  graphics_context_set_antialiased( pDTP->ctx, true );
  
  for ( int i = 0, angle = 0; i < 30; i += pDTP->increment ) { // drawing half the ticks is *probably* more efficient
    angle = TRIG_MAX_ANGLE * i / 60;
    gpath_rotate_to( gpath, angle );
    gpath_move_to( gpath, center_pt );
    graphics_context_set_stroke_color( pDTP->ctx, GColorFromHEX( pDTP->tick_colour ) );
    graphics_context_set_stroke_width( pDTP->ctx, pDTP->tick_thk );
    gpath_draw_outline( pDTP->ctx, gpath );
  }
  graphics_context_set_fill_color( pDTP->ctx, GColorFromHEX( pDTP->bg_colour ) );
  graphics_fill_rect( pDTP->ctx, grect_inset( bounds, GEdgeInsets( pDTP->tick_length ) ), 0, GCornerNone );
  gpath_destroy( gpath );
}
