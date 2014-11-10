#pragma once
#include "pebble.h"
#include "pge.h"  // GLine

bool collision_rectangle_rectangle(GRect *rect_a, GRect *rect_b);

bool collision_line_rectangle(GLine *line, GRect *rect);

bool collision_line_line(GLine *line_a, GLine *line_b, GPoint *collision_point);

bool collision_point_rectangle(GPoint *point, GRect *rect);

