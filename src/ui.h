#ifndef __UI_H__
#define __UI_H__

#include "constants.h"
#include "texture.h"

typedef struct {
  bool editMode;
  bool debugMode;
} UiFlags;

void draw_ui(UiFlags *flags);
int update_hotbar(void);
void draw_hotbar(Texture2D *texture, Rectangle source, int *slots,
                 int numSlots);

#endif
