#pragma once
#include "pebble.h"
#include "../pge.h"  // GLine

bool pge_collision_rectangle_rectangle(GRect *rect_a, GRect *rect_b);

bool pge_collision_line_rectangle(GLine *line, GRect *rect);

bool pge_collision_line_line(GLine *line_a, GLine *line_b);

bool pge_collision_point_rectangle(GPoint *point, GRect *rect);

