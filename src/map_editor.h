#ifndef __MAP_EDITOR_H__
#define __MAP_EDITOR_H__

#include "constants.h"
#include "raylib.h"
#include "texture.h"

typedef enum {
  TILE_CORNER,
  TILE_DOUBLE_NUCK,
  TILE_EDGE,
  TILE_NUCK,
  TILE_FULL,
  TILE_EMPTY = -1,
} TileID;

typedef struct {
  int tile;
  float rotation;
} TileInfo;

typedef struct {
  bool logicalGrid[MAP_HEIGHT][MAP_WIDTH];
  unsigned int visualGrid[MAP_HEIGHT + 1][MAP_WIDTH + 1];
} Map;

void update_grid(Camera2D *camera, int seletedHotbarSlot);
void draw_grid(Camera2D *camera, Textures *textures);
void rebuild_visual_grid();
TileInfo get_tile_info(int bitmask);
void save_map();

#endif
