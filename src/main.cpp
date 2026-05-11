#include "camera.h"
#include "constants.h"
#include "map_editor.h"
#include "player.h"
#include "raygui.h"
#include "raylib.h"
#include "texture.h"
#include "ui.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunny Acres");

  UiFlags uiFlags{0};
  uiFlags.editMode = true;
  uiFlags.debugMode = false;

  Map map{};

  int mapHotbarSlots[HOTBAR_NUM_SLOTS] = {TILE_CORNER, TILE_DOUBLE_NUCK,
                                          TILE_EDGE, TILE_NUCK, TILE_FULL};

  int itemHotbarSlots[HOTBAR_NUM_SLOTS] = {0};

  int selectedHotbarSlot = 0;

  Textures textures = create_textures();
  load_textures(&textures);

  Player player{textures.characterTextures[0],
                (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                (Vector2){48, 48}};

  Vector2 offset{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  Camera2d camera{player.get_pos(), offset, 0.0f, 1.0f};

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();

    selectedHotbarSlot = update_hotbar();

    if (uiFlags.editMode)
      map.update_grid(camera.get_cam(), selectedHotbarSlot);
    else
      player.update(delta);

    camera.update(&player, delta);

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      float wheel = GetMouseWheelMove();

      if (wheel != 0) {
        camera.zoom_at(GetMousePosition(), wheel);
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(*camera.get_cam());

    if (uiFlags.editMode) {
      map.draw_grid(camera.get_cam(), &textures);
    } else {
      player.draw();
    }

    EndMode2D();

    draw_ui(&uiFlags);
    if (uiFlags.editMode) {
      draw_hotbar(&textures.tilesetTextures[0], (Rectangle){0, 0, 32, 32},
                  mapHotbarSlots, HOTBAR_NUM_SLOTS);
    } else {
      draw_hotbar(&textures.objectTextures[0], (Rectangle){0, 0, 16, 16},
                  itemHotbarSlots, HOTBAR_NUM_SLOTS);
    }

    if (uiFlags.debugMode)
      DrawRectangleLines((SCREEN_WIDTH - SCREEN_WIDTH * 0.5f) / 2,
                         (SCREEN_HEIGHT - SCREEN_HEIGHT * 0.5f) / 2,
                         SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, RED);

    EndDrawing();
  }

  unload_textures(&textures);
  CloseWindow();

  return 0;
}
