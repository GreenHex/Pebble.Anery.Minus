//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#pragma once
#include <pebble.h>
#include "global.h"

#define CLOCK_DIAL_SIZE_W PBL_DISPLAY_WIDTH 
#define CLOCK_DIAL_SIZE_H PBL_DISPLAY_HEIGHT
#define CLOCK_DIAL_POS_X 0
#define CLOCK_DIAL_POS_Y 0

#define CLOCK_DIAL_RECT ( GRect( CLOCK_DIAL_POS_X, CLOCK_DIAL_POS_Y, CLOCK_DIAL_SIZE_W, CLOCK_DIAL_SIZE_H ) )
#define CLOCK_TICK_EDGE_OFFSET 3 /* make it an odd number */

static GPathInfo PATH_TICK = {
  2, (GPoint []) {
    { 0, - ( CLOCK_DIAL_SIZE_W > CLOCK_DIAL_SIZE_H ? CLOCK_DIAL_SIZE_W : CLOCK_DIAL_SIZE_H ) },
    { 0, ( CLOCK_DIAL_SIZE_W >  CLOCK_DIAL_SIZE_H ? CLOCK_DIAL_SIZE_W : CLOCK_DIAL_SIZE_H ) }
  }
};

#if PBL_DISPLAY_WIDTH == 200

static GPathInfo HOUR_HAND_SBGE001_POINTS = {
  6, (GPoint []) {
    { -3, 20 },
    { -11, 0 },
    { -3, -48 },
    { 3, -48 },
    { 11, 0 },
    { 3, 20 }
  }
};

static GPathInfo HOUR_HAND_SBGE001_POINTS_HIGHLIGHT = {
  5, (GPoint []) {
    { 0, 20 },
    { 3, 20 },
    { 11, 0 },
    { 3, -48 },
    { 0, -48 },
  }
};

static GPathInfo MINUTE_HAND_SBGE001_POINTS = {
  6, (GPoint []) {
    { -3, 20 },
    { -8, 0 },
    { -3, -74 },
    { 3, -74 },
    { 8, 0 },
    { 3, 20 }
  }
};

static GPathInfo MINUTE_HAND_SBGE001_POINTS_HIGHLIGHT = {
  5, (GPoint []) {
    { 0, 20 },
    { -3, 20 },
    { -8, 0 },
    { -3, -74 },
    { 0, -74 },
  }
};

#else

static GPathInfo HOUR_HAND_SBGE001_POINTS = {
  6, (GPoint []) {
    { -3, 14 },
    { -9, 0 },
    { -2, -42 },
    { 2, -42 },
    { 9, 0 },
    { 3, 14 }
  }
};

static GPathInfo HOUR_HAND_SBGE001_POINTS_HIGHLIGHT = {
  5, (GPoint []) {
    { 0, 14 },
    { 3, 14 },
    { 9, 0 },
    { 2, -42 },
    { 0, -42 },
  }
};

static GPathInfo MINUTE_HAND_SBGE001_POINTS = {
  6, (GPoint []) {
    { -3, 14 },
    { -7, 0 },
    { -2, -61 },
    { 2, -61 },
    { 7, 0 },
    { 3, 14 }
  }
};

static GPathInfo MINUTE_HAND_SBGE001_POINTS_HIGHLIGHT = {
  5, (GPoint []) {
    { 0, 14 },
    { -3, 14 },
    { -7, 0 },
    { -2, -61 },
    { 0, -61 },
  }
};

#endif

#if PBL_DISPLAY_WIDTH == 200

#define SEC_HAND_LENGTH 74
#define SEC_HAND_TAIL_LENGTH 28
#define SEC_HAND_TIP_LENGTH 16
#define SEC_HAND_WIDTH 1
#define SEC_CENTER_DOT_RADIUS 5

#else

#define SEC_HAND_LENGTH 61 /* 55  53 */
#define SEC_HAND_TAIL_LENGTH 23
#define SEC_HAND_TIP_LENGTH 12
#define SEC_HAND_WIDTH 1
#define SEC_CENTER_DOT_RADIUS 4

#endif

void clock_init( Window* window );
void clock_deinit( void );
