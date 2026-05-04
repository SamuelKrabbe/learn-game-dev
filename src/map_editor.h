#ifndef __MAP_EDITOR_H__
#define __MAP_EDITOR_H__

#include "constants.h"
#include "raylib.h"
#include "texture.h"

typedef enum {
  TILE_EMPTY = 0,
  TILE_EDGE,
  TILE_DOUBLE_NUCK,
  TILE_STRAIGHT,
  TILE_NUCK,
  TILE_FULL
} TileID;

typedef struct {
  bool logicalGrid[MAP_HEIGHT][MAP_WIDTH];
  unsigned int visualGrid[MAP_HEIGHT + 1][MAP_WIDTH + 1];
} Map;

void update_grid(Camera2D *camera, int seletedHotbarSlot);
void draw_grid(Camera2D *camera, Textures *textures);
void rebuild_visual_grid();
void save_map();

#endif
