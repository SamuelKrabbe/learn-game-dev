#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "constants.h"
#include "player.h"
#include "raylib.h"

class Camera2d {
public:
  Camera2d(Vector2 pos, Vector2 offset, float rotation, float zoom)
      : camera{new Camera2D()} {
    camera->target = pos;
    camera->offset = offset;
    camera->rotation = rotation;
    camera->zoom = zoom;
  }

  void update(Player *player, float deltaTime);
  void zoom_at(Vector2 screenPoint, float amount);
  Camera2D *get_cam() { return camera; }

private:
  Camera2D *camera{};
};

#endif
