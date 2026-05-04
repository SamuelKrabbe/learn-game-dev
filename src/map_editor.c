#include "map_editor.h"
#include "constants.h"
#include "raylib.h"
#include "texture.h"

static int map[MAP_HEIGHT][MAP_WIDTH] = {0};
static int selectedTile = 0;

void update_grid(Camera2D *camera, int selectedHotbarSlot) {
  selectedTile = selectedHotbarSlot;
}

void draw_grid(Camera2D *camera, Textures *textures) {
  // --- Grid lines ---
  for (int x = 0; x <= MAP_WIDTH; x++)
    DrawLine(x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE,
             LIGHTGRAY);
  for (int y = 0; y <= MAP_HEIGHT; y++)
    DrawLine(0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, LIGHTGRAY);

  // --- Tile placement ---
  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera);
  int tileX = (int)(mouseWorld.x / TILE_SIZE);
  int tileY = (int)(mouseWorld.y / TILE_SIZE);

  if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
    DrawRectangleLines(tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE,
                       TILE_SIZE, GREEN);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      map[tileY][tileX] = selectedTile + 1; // 0 = empty
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
      map[tileY][tileX] = 0;
  }

  int textureWidth = textures->tilesetTextures[0].width;
  int textureHeight = textures->tilesetTextures[0].height;

  Rectangle source = {128, 0, 16, 16};
  Rectangle curSource = source;
  int tileW = (int)source.width;
  int tileH = (int)source.height;
  int tilesPerRow = (textureWidth - (int)source.x) / tileW;

  // --- Draw placed tiles ---
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      int tile = map[y][x];
      if (tile > 0) {
        int index = tile - 1; // 0-based index into tileset
        Rectangle curSource = {source.x + (index % tilesPerRow) * tileW,
                               source.y + (index / tilesPerRow) * tileH,
                               source.width, source.height};
        DrawTexturePro(
            textures->tilesetTextures[0], curSource,
            (Rectangle){x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE},
            (Vector2){0, 0}, 0.0f, WHITE);
      }
    }
  }

  save_map();
}

void save_map() {}
