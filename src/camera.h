#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "constants.h"
#include "entity.h"
#include "raylib.h"

void update_camera(Camera2D *camera, Entity *player, float deltaTime);
void camera_zoom_at(Camera2D *camera, Vector2 screenPoint, float amount);

#endif
