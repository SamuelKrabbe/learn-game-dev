#include "map_editor.h"
#include "constants.h"
#include "raylib.h"
#include "texture.h"

static int selectedTile = 0;

void Map::update_grid(Camera2D *camera, int selectedHotbarSlot) {
  selectedTile = selectedHotbarSlot;
}

void Map::draw_grid(Camera2D *camera, Textures *textures) {
  // --- Logical Grid lines ---
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      this->logicalGrid[tileY][tileX] = 1; // 1 for occupied 0 otherwise
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      this->logicalGrid[tileY][tileX] = 0;
    }
  }

  rebuild_visual_grid();

  int textureWidth = textures->tilesetTextures[0].width;
  int textureHeight = textures->tilesetTextures[0].height;

  Rectangle source = {0, 0, 32, 32};
  Rectangle curSource = source;
  int tileW = (int)source.width;
  int tileH = (int)source.height;
  int tilesPerRow = (textureWidth - (int)source.x) / tileW;

  // --- Draw placed tiles ---
  for (int y = 0; y < MAP_HEIGHT + 1; y++) {
    for (int x = 0; x < MAP_WIDTH + 1; x++) {
      int tile = this->visualGrid[y][x];
      if (tile > 0) {
        TileInfo info = get_tile_info(tile);
        int index = info.tile;

        Rectangle curSource = {source.x + (index % tilesPerRow) * tileW,
                               source.y + ((float)index / tilesPerRow) * tileH,
                               source.width, source.height};

        float cx = (x * TILE_SIZE) - 16 + TILE_SIZE / 2.0f;
        float cy = (y * TILE_SIZE) - 16 + TILE_SIZE / 2.0f;

        DrawTexturePro(
            textures->tilesetTextures[0], curSource,
            (Rectangle){cx, cy, TILE_SIZE, TILE_SIZE},
            (Vector2){TILE_SIZE / 2.0f, TILE_SIZE / 2.0f}, // origin = center
            info.rotation, WHITE);
      }
    }
  }

  save_map();
}

void Map::rebuild_visual_grid() {
  for (int y = 0; y < MAP_HEIGHT + 1; y++)
    for (int x = 0; x < MAP_WIDTH + 1; x++)
      this->visualGrid[y][x] = 0;

  for (int vy = 0; vy < MAP_HEIGHT + 1; vy++) {
    for (int vx = 0; vx < MAP_WIDTH + 1; vx++) {
      // The 4 logical cells surrounding this visual cell
      // Clamp to grid bounds, out-of-bounds = 0
      int topLeft = (vy > 0 && vx > 0) ? this->logicalGrid[vy - 1][vx - 1] : 0;
      int topRight =
          (vy > 0 && vx < MAP_WIDTH) ? this->logicalGrid[vy - 1][vx] : 0;
      int botLeft =
          (vy < MAP_HEIGHT && vx > 0) ? this->logicalGrid[vy][vx - 1] : 0;
      int botRight =
          (vy < MAP_HEIGHT && vx < MAP_WIDTH) ? this->logicalGrid[vy][vx] : 0;

      this->visualGrid[vy][vx] =
          (topLeft << 3) | (topRight << 2) | (botLeft << 1) | botRight;
    }
  }
}

TileInfo Map::get_tile_info(int bitmask) {
  switch (bitmask) {
  case 0b0000:
    return (TileInfo){TILE_EMPTY, 0};
  case 0b1111:
    return (TileInfo){TILE_FULL, 0};

  case 0b0100:
    return (TileInfo){TILE_CORNER, 0};
  case 0b0001:
    return (TileInfo){TILE_CORNER, 90};
  case 0b0010:
    return (TileInfo){TILE_CORNER, 180};
  case 0b1000:
    return (TileInfo){TILE_CORNER, 270};

  case 0b0011:
    return (TileInfo){TILE_EDGE, 0};
  case 0b1010:
    return (TileInfo){TILE_EDGE, 90};
  case 0b1100:
    return (TileInfo){TILE_EDGE, 180};
  case 0b0101:
    return (TileInfo){TILE_EDGE, 270};

  case 0b0111:
    return (TileInfo){TILE_NUCK, 0};
  case 0b1011:
    return (TileInfo){TILE_NUCK, 90};
  case 0b1110:
    return (TileInfo){TILE_NUCK, 180};
  case 0b1101:
    return (TileInfo){TILE_NUCK, 270};

  case 0b1001:
    return (TileInfo){TILE_DOUBLE_NUCK, 0};
  case 0b0110:
    return (TileInfo){TILE_DOUBLE_NUCK, 90};

  default:
    return (TileInfo){TILE_EMPTY, 0};
  }
}

void save_map() {}
