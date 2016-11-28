//
// Copyright (C) 2016, Vinodh Kumar M. <GreenHex@gmail.com>
//

#pragma once
#include <pebble.h>
#include "global.h"

#if PBL_DISPLAY_WIDTH == 200

#define CLOCK_POS_X 0
#define CLOCK_POS_Y 0

#else

#define CLOCK_POS_X 0
#define CLOCK_POS_Y 0

#endif=

void draw_clock( void );
void clock_init( Window* window );
void clock_deinit( void );