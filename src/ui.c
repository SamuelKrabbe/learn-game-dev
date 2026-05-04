#include "ui.h"
#include "constants.h"
#include "raygui.h"
#include "raylib.h"

static int selectedSlot = 0;

void draw_ui(UiFlags *flags) {
  DrawFPS(10, 10);
  GuiCheckBox((Rectangle){10, SCREEN_HEIGHT - 30, 20, 20}, "Edit Map",
              &flags->editMode);
  GuiCheckBox((Rectangle){10, SCREEN_HEIGHT - 60, 20, 20}, "Debug",
              &flags->debugMode);
}

int update_hotbar(void) {
  int wheel = (int)GetMouseWheelMove();
  if (wheel != 0) {
    selectedSlot -= wheel;
    if (selectedSlot > HOTBAR_NUM_SLOTS - 1)
      selectedSlot = HOTBAR_NUM_SLOTS - 1;
    else if (selectedSlot < 0)
      selectedSlot = 0;
  }

  return selectedSlot;
}

void draw_hotbar(Texture2D texture, Rectangle source, int *slots,
                 int numSlots) {
  int tilesPerRow = (texture.width - (int)source.x) / (int)source.width;
  int totalWidth =
      HOTBAR_NUM_SLOTS * (HOTBAR_TILE_SIZE + HOTBAR_PADDING) - HOTBAR_PADDING;
  int hotbarX = (SCREEN_WIDTH - totalWidth) / 2;
  int hotbarY = SCREEN_HEIGHT - HOTBAR_TILE_SIZE - 10;

  int id, x;
  Rectangle dest, curSource = source;
  for (int i = 0; i < numSlots; i++) {
    id = slots[i];
    curSource =
        (Rectangle){source.x + (float)(id % tilesPerRow) * source.width,
                    source.y + (float)(id / tilesPerRow) * source.height,
                    source.width, source.height};
    x = hotbarX + i * (HOTBAR_TILE_SIZE + HOTBAR_PADDING);
    dest = (Rectangle){x, hotbarY, HOTBAR_TILE_SIZE, HOTBAR_TILE_SIZE};

    DrawRectangleRec(dest, Fade(BLACK, 0.5f));
    DrawTexturePro(texture, curSource, dest, (Vector2){0, 0}, 0.0f, WHITE);

    if (i == selectedSlot)
      DrawRectangleLinesEx(dest, 2, GREEN);
    else
      DrawRectangleLinesEx(dest, 1, GRAY);
  }
}
