#ifndef _STYLE_SETTINGS_H_
#define _STYLE_SM_H_

#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "ui/Container.h"
#include "ui/ui_util.h"

///////////////////////////////////////////////////////////////
// Window (root container)
#define W_TOP_LEFT ui_util::Point { 5, 5 }
#define W_WIDTH 310
#define W_HEIGHT 230
#define W_ORIENTATION Container::Column
#define W_COLOUR COLOUR_BLACK
#define W_BORDER_COLOUR COLOUR_RED
// Header
#define HEADER_WIDTH 200
#define HEADER_HEIGHT 25
#define HEADER_COLOUR W_COLOUR
// Font
#define HEADER_FONT FREE_SANS_12PT7B
#define HEADER_FONT_COLOUR COLOUR_WHITE
#define HEADER_FONT_WIDTH 1
#define HEADER_FONT_HEIGHT 1

///////////////////////////////////////////////////////////////
// Menu Button Container
#define MC_WIDTH 290
#define MC_HEIGHT 180
#define MC_ORIENTATION Container::Column
#define MC_COLOUR COLOUR_GREY
#define MC_BORDER_COLOUR COLOUR_MAGENTA

///////////////////////////////////////////////////////////////
// Menu Buttons
// Dimensions
#define MB_HEIGHT 30
#define MB_WIDTH 200
#define MB_COLOUR COLOUR_LIGHTGREY
#define MB_BORDER_COLOUR COLOUR_BLACK
#define MB_FOCUS_COLOUR COLOUR_BLACK
// Font
#define MB_FONT FREE_SANS_BOLD_9PT7B
#define MB_FONT_FOCUS_COLOUR COLOUR_WHITE
#define MB_FONT_SELECT_COLOUR COLOUR_WHITE
#define MB_FONT_WIDTH 1
#define MB_FONT_HEIGHT 1
#define MB_FONT_COLOUR COLOUR_BLACK

///////////////////////////////////////////////////////////////
// Nav Button Container
#define NC_WIDTH 260
#define NC_HEIGHT 30
#define NC_ORIENTATION Container::Row
#define NC_COLOUR COLOUR_NAVY
#define NC_BORDER_COLOUR COLOUR_BLACK

///////////////////////////////////////////////////////////////
// Nav Buttons
// Dimensions
#define NB_HEIGHT 25
#define NB_WIDTH 80
#define NB_BORDER_COLOUR COLOUR_BLACK
// Font
#define NB_FONT FREE_SANS_BOLD_9PT7B
#define NB_FONT_FOCUS_COLOUR COLOUR_WHITE
#define NB_FONT_SELECT_COLOUR COLOUR_WHITE
#define NB_FONT_WIDTH 1
#define NB_FONT_HEIGHT 1
#define NB_FONT_COLOUR COLOUR_BLACK
// Select
#define SELECT_STRING "Select"
#define SELECT_COLOUR COLOUR_GREEN
#define SELECT_FOCUS_COLOUR COLOUR_DARKCYAN
// Back
#define BACK_STRING "Back"
#define BACK_COLOUR COLOUR_RED
#define BACK_FOCUS_COLOUR COLOUR_PURPLE

#endif