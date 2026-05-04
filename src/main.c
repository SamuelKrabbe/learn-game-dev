#include "camera.h"
#include "constants.h"
#include "entity.h"
#include "map_editor.h"
#include "raygui.h"
#include "raylib.h"
#include "texture.h"
#include "ui.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunny Acres");

  UiFlags uiFlags = {0};
  uiFlags.editMode = true;
  uiFlags.debugMode = false;

  int mapHotbarSlots[HOTBAR_NUM_SLOTS] = {TILE_EMPTY,       TILE_EDGE,
                                          TILE_DOUBLE_NUCK, TILE_STRAIGHT,
                                          TILE_NUCK,        TILE_FULL};

  int itemHotbarSlots[HOTBAR_NUM_SLOTS] = {0};

  int selectedHotbarSlot = 0;

  Textures textures = create_textures();
  load_textures(&textures);

  Entity player = create_entity(
      textures.characterTextures[0],
      (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, (Vector2){48, 48});

  Camera2D camera = {0};
  camera.target = player.pos;
  camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();

    selectedHotbarSlot = update_hotbar();

    if (uiFlags.editMode)
      update_grid(&camera, selectedHotbarSlot);
    else
      update_entity(&player, delta);

    update_camera(&camera, &player, delta);

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      float wheel = GetMouseWheelMove();

      if (wheel != 0) {
        camera_zoom_at(&camera, GetMousePosition(), wheel);
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    // DrawTexturePro(scene, (Rectangle){0, 0, scene.width, scene.height},
    //                (Rectangle){0, 0, scene.width, scene.height},
    //                (Vector2){0, 0}, 0.0, WHITE);

    if (uiFlags.editMode) {
      draw_grid(&camera, &textures);
    } else {
      draw_entity(&player);
    }

    EndMode2D();

    draw_ui(&uiFlags);
    if (uiFlags.editMode) {
      draw_hotbar(&textures.tilesetTextures[0], (Rectangle){32, 0, 32, 32},
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
