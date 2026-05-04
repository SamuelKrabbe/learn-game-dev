#include "camera.h"
#include "entity.h"
#include "raylib.h"

void camera_zoom_at(Camera2D *camera, Vector2 screenPoint, float amount) {
  Vector2 mouseWorldBefore = GetScreenToWorld2D(screenPoint, *camera);

  camera->zoom += amount * 0.2f;
  if (camera->zoom < 0.2f)
    camera->zoom = 0.2f;
  if (camera->zoom > 3.0f)
    camera->zoom = 3.0f;

  Vector2 mouseWorldAfter = GetScreenToWorld2D(screenPoint, *camera);

  camera->target.x += (mouseWorldBefore.x - mouseWorldAfter.x);
  camera->target.y += (mouseWorldBefore.y - mouseWorldAfter.y);
}

void update_camera(Camera2D *camera, Entity *entity, float deltaTime) {
  // Deadzone in screen space, centered
  float dzW = SCREEN_WIDTH * 0.5f;
  float dzH = SCREEN_HEIGHT * 0.5f;
  float dzX = (SCREEN_WIDTH - dzW) / 2.0f;
  float dzY = (SCREEN_HEIGHT - dzH) / 2.0f;

  // Convert entity world pos to screen pos
  Vector2 screenPos = GetWorldToScreen2D(entity->pos, *camera);

  if (entity->dir.x != 0) {
    int moveX = entity->dir.x * entity->vel.x * deltaTime;
    if (screenPos.x < dzX || screenPos.x > dzX + dzW)
      camera->target.x += moveX;
  }

  if (entity->dir.y != 0) {
    int moveY = entity->dir.y * entity->vel.y * deltaTime;
    if (screenPos.y < dzY || screenPos.y > dzY + dzH)
      camera->target.y += moveY;
  }
}
