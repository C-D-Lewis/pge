#include "pge_sprite.h"
#include "pge_collision.h"

PGESprite* pge_sprite_create(GPoint position, int initial_resource_id) {
  PGESprite *this = malloc(sizeof(PGESprite));

  // Allocate
  this->bitmap = gbitmap_create_with_resource(initial_resource_id);
  this->position = position;

  // Finally
  return this;
}

void pge_sprite_destroy(PGESprite *this) {
  gbitmap_destroy(this->bitmap);

  free(this);
}

void pge_sprite_set_anim_frame(PGESprite *this, int resource_id) {
  gbitmap_destroy(this->bitmap);
  this->bitmap = gbitmap_create_with_resource(resource_id);
}

void pge_sprite_draw(PGESprite *this, GContext *ctx) {
#ifdef PBL_PLATFORM_APLITE
  GRect bounds = this->bitmap->bounds;
#elif PBL_PLATFORM_BASALT
  GRect bounds = gbitmap_get_bounds(this->bitmap);
#endif
  graphics_draw_bitmap_in_rect(ctx, this->bitmap, GRect(this->position.x, this->position.y, bounds.size.w, bounds.size.h));
}

void pge_sprite_set_position(PGESprite *this, GPoint new_position) {
  this->position = new_position;
}

GPoint pge_sprite_get_position(PGESprite *this) {
  return this->position;
}

void pge_sprite_move(PGESprite *this, int dx, int dy) {
  GPoint pos = pge_sprite_get_position(this);
  pos.x += dx;
  pos.y += dy;
  pge_sprite_set_position(this, pos);
}

bool pge_check_collision(PGESprite* sprite1, PGESprite *sprite2) {
#ifdef PBL_PLATFORM_APLITE
  GRect bounds1 = sprite1->bitmap->bounds;
  GRect bounds2 = sprite2->bitmap->bounds;
#elif PBL_PLATFORM_BASALT
  GRect bounds1 = gbitmap_get_bounds(sprite1->bitmap);
  GRect bounds2 = gbitmap_get_bounds(sprite2->bitmap);
#endif

  GRect rect_a = (GRect){
    {sprite1->position.x, sprite1->position.y}, 
    {bounds1.size.w, bounds1.size.h}};

  GRect rect_b = (GRect){
    {sprite2->position.x, sprite2->position.y}, 
    {bounds2.size.w, bounds2.size.h}};

  // Test each corner of the other rect
  return pge_collision_rectangle_rectangle(&rect_a, &rect_b);
}

GRect pge_sprite_get_bounds(PGESprite *this) {
#ifdef PBL_PLATFORM_APLITE
  GRect bounds = this->bitmap->bounds;
#elif PBL_PLATFORM_BASALT
  GRect bounds = gbitmap_get_bounds(this->bitmap);
#endif
  return GRect(this->position.x, this->position.y, bounds.size.w, bounds.size.h);
}