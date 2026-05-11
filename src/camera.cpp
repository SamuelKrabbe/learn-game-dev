#include "camera.h"
#include "player.h"
#include "raylib.h"

void Camera2d::zoom_at(Vector2 screenPoint, float amount) {
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

void Camera2d::update(Player *player, float deltaTime) {
  // Deadzone in screen space, centered
  float dzW = SCREEN_WIDTH * 0.5f;
  float dzH = SCREEN_HEIGHT * 0.5f;
  float dzX = (SCREEN_WIDTH - dzW) / 2.0f;
  float dzY = (SCREEN_HEIGHT - dzH) / 2.0f;

  // Convert entity world pos to screen pos
  Vector2 screenPos = GetWorldToScreen2D(player->get_pos(), *camera);

  Vector2 dir{player->get_dir()};
  Vector2 vel{player->get_vel()};
  if (dir.x != 0) {
    int moveX = dir.x * dir.x * deltaTime;
    if (screenPos.x < dzX || screenPos.x > dzX + dzW)
      camera->target.x += moveX;
  }

  if (dir.y != 0) {
    int moveY = dir.y * vel.y * deltaTime;
    if (screenPos.y < dzY || screenPos.y > dzY + dzH)
      camera->target.y += moveY;
  }
}
