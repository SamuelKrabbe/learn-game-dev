#ifndef __MAP_EDITOR_H__
#define __MAP_EDITOR_H__

#include "constants.h"
#include "raylib.h"
#include "texture.h"

#define ROWS 500
#define COLS 500

typedef enum {
  TILE_EMPTY = 0,
  TILE_EDGE,
  TILE_DOUBLE_NUCK,
  TILE_STRAIGHT,
  TILE_NUCK,
  TILE_FULL
} TileID;

typedef struct {
  bool logicalGrid[ROWS][COLS];
  unsigned int visualGrid[ROWS + 1][COLS + 1];
} map;

void update_grid(Camera2D *camera, int seletedHotbarSlot);
void draw_grid(Camera2D *camera, Textures *textures);
void save_map();

#endif
