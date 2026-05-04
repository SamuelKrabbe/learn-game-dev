#ifndef __ENTITY_H__
#define __ENTITY_H__

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

typedef struct {
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
} Entity;

Entity create_entity(Texture2D texture, Vector2 startPos, Vector2 frameDim);
void update_entity(Entity *entity, float deltaTime);
void draw_entity(Entity *entity);
void update_animation(Entity *entity, float deltaTime);
void set_entity_animation(Entity *entity, AnimationType type,
                          AnimationDirection dir);

#endif
