#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "constants.h"
#include "raylib.h"

typedef enum {
  IDLE = 0,
  MOVE = 3,
  ATTACK = 6,
  DEATH = 9,
  MAX_TYPES
} AnimationType;
typedef enum { DOWN, RIGHT, UP, LEFT } AnimationDirection;

class Player {
public:
  Player(Texture2D texture, Vector2 startPos, Vector2 frameDim) {
    pos = startPos;
    vel = (Vector2){200, 200};
    dir = (Vector2){0, 0};
    deadzone = (Rectangle){startPos.x, startPos.y, SCREEN_WIDTH * 0.5,
                           SCREEN_HEIGHT * 0.5};
    this->frameDim = frameDim;
    currentFrame = 0;
    frameTimer = 0.0f;
    frameDuration = 0.2f;
    maxFrames = 6;
    animationType = IDLE;
    animationDirection = DOWN;
    this->texture = texture;
  }

  void update(float deltaTime);
  void draw();
  void update_animation(float deltaTime);
  void set_animation(AnimationType type, AnimationDirection dir);
  Vector2 get_pos() { return pos; }
  Vector2 get_vel() { return vel; }
  Vector2 get_dir() { return dir; }

private:
  Vector2 pos;
  Vector2 vel;
  Vector2 dir;
  Rectangle deadzone;
  Texture2D texture;

  Vector2 frameDim;
  int currentFrame;
  float frameTimer;    // accumulated time
  float frameDuration; // time per frame (seconds)
  int maxFrames;
  AnimationType animationType;
  AnimationDirection animationDirection;
};

#endif
