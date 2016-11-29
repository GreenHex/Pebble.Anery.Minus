//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#pragma once
#include <pebble.h>
#include "global.h"

#if PBL_DISPLAY_WIDTH == 200

#define BATT_GAUGE_SIZE_W 45
#define BATT_GAUGE_SIZE_H 45
#define BATT_HAND_LENGTH 35
#define BATT_GAUGE_DOT_RADIUS 3

#else

#define BATT_GAUGE_SIZE_W 35
#define BATT_GAUGE_SIZE_H 30
#define BATT_HAND_LENGTH 26
#define BATT_GAUGE_DOT_RADIUS 3

#endif

#define BATT_GAUGE_RIGHT_GAP 3
#define BATTERY_GAUGE_POS_X ( BATT_GAUGE_RIGHT_GAP )
#define BATTERY_GAUGE_POS_Y ( PBL_DISPLAY_HEIGHT/2 - BATT_GAUGE_SIZE_H/2 )
#define BATTERY_GAUGE_FRAME ( GRect ( BATTERY_GAUGE_POS_X, BATTERY_GAUGE_POS_Y, BATT_GAUGE_SIZE_W, BATT_GAUGE_SIZE_H ) )

#define BATTERY_GAUGE_PIVOT ( GPoint( BATT_GAUGE_SIZE_W - BATT_GAUGE_RIGHT_GAP, BATT_GAUGE_SIZE_H/2 ) )
#define BATTERY_GAUGE_MAX_ANGLE_DEG 20
#define BATTERY_GAUGE_TICK_POS_X ( -BATT_GAUGE_SIZE_W )
#define BATTERY_GAUGE_TICK_POS_Y ( BATT_GAUGE_SIZE_H / 2 )
#define BATTERY_GAUGE_TICK_POS ( GPoint( -BATTERY_GAUGE_TICK_POS_X, BATTERY_GAUGE_TICK_POS_Y ) )

#define COLOUR_BATT_15          GColorRed
#define COLOUR_BATT_95          GColorDarkGreen
#define COLOUR_BATT_100         GColorMayGreen

#if PBL_DISPLAY_WIDTH == 200

static GPathInfo BATT_GAUGE_TICK = {
  2, (GPoint[]) {
    { BATTERY_GAUGE_TICK_POS_X + 5, 0 },
    { BATTERY_GAUGE_TICK_POS_X, 0 }
  }
};

#else

static GPathInfo BATT_GAUGE_TICK = {
  2, (GPoint[]) {
    { BATTERY_GAUGE_TICK_POS_X + 3, 0 },
    { BATTERY_GAUGE_TICK_POS_X, 0 }
  }
};

#endif

typedef struct {
  GContext *ctx;
  uint32_t batt_angle;
  GPoint center_pt;
  GPath *s_hand;
  GColor hand_colour;
  GColor hand_outline_colour;
  uint16_t dot_radius;
  BatteryChargeState charge_state;
} BATTERY_HAND_DRAW_PARAMS;

Layer *battery_layer;

void battery_init( Layer *parent_layer );
void battery_deinit( void );
