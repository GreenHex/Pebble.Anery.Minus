//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#pragma once

typedef struct {
  Layer *layer;
  GContext *ctx;
  GPathInfo *p_gpath_info;
  int increment;
  int tick_thk;
  int tick_length;
  uint32_t tick_colour;
  uint32_t bg_colour;
} DRAW_TICKS_PARAMS;

bool is_X_in_range( int a, int b, int x );
void print_pt( char *str, GPoint pt );
void print_rect( char *str, GRect rect );
void draw_seconds_ticks( DRAW_TICKS_PARAMS *pDTP );
