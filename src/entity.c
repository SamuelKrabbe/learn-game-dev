#include "entity.h"
#include "constants.h"
#include "raylib.h"
#include "raymath.h"

Entity create_entity(Texture2D texture, Vector2 startPos, Vector2 frameDim) {
  Entity entity = {0};

  entity.pos = startPos;
  entity.vel = (Vector2){200, 200};
  entity.dir = (Vector2){0, 0};
  entity.deadzone = (Rectangle){startPos.x, startPos.y, SCREEN_WIDTH * 0.5,
                                SCREEN_HEIGHT * 0.5};
  entity.frameDim = frameDim;
  entity.currentFrame = 0;
  entity.frameTimer = 0.0f;
  entity.frameDuration = 0.2f;
  entity.maxFrames = 6;
  entity.animationType = IDLE;
  entity.animationDirection = DOWN;
  entity.texture = texture;

  return entity;
}

void update_entity(Entity *entity, float deltaTime) {
  if (entity->animationType == ATTACK &&
      entity->currentFrame < entity->maxFrames - 1) {
    update_animation(entity, deltaTime);
    return; // don't process other input until attack is done
  }

  AnimationDirection dirInput = entity->animationDirection;
  entity->dir = (Vector2){0, 0};

  if (IsKeyDown(KEY_W)) {
    entity->dir.y -= 1;
    dirInput = UP;
  }
  if (IsKeyDown(KEY_S)) {
    entity->dir.y += 1;
    dirInput = DOWN;
  }
  if (IsKeyDown(KEY_A)) {
    entity->dir.x -= 1;
    dirInput = LEFT;
  }
  if (IsKeyDown(KEY_D)) {
    entity->dir.x += 1;
    dirInput = RIGHT;
  }

  entity->dir = Vector2Normalize(entity->dir);

  if (entity->dir.x == 0 && entity->dir.y == 0) {
    set_entity_animation(entity, IDLE, dirInput);
  } else {
    set_entity_animation(entity, MOVE, dirInput);
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    set_entity_animation(entity, ATTACK, dirInput);
  }

  int moveX = entity->dir.x * entity->vel.x * deltaTime;
  int moveY = entity->dir.y * entity->vel.y * deltaTime;

  entity->pos.x += moveX;
  entity->pos.y += moveY;
}

void draw_entity(Entity *entity) {
  int type = entity->animationType;
  float scale = 2.0f;

  int frameWidth = (int)entity->frameDim.x;
  int frameHeight = (int)entity->frameDim.y;

  int row = type + entity->animationDirection;
  int col = entity->currentFrame;

  bool flip = false;

  // If LEFT, reuse RIGHT row and flip
  if (entity->animationDirection == LEFT) {
    row = type + RIGHT;
    flip = true;
  }

  if (type == DEATH) {
    row = DEATH;
  }

  Rectangle source;

  if (!flip) {
    source = (Rectangle){col * frameWidth, row * frameHeight, frameWidth,
                         frameHeight};
  } else {
    source = (Rectangle){(col + 1) * frameWidth, row * frameHeight, -frameWidth,
                         frameHeight};
  }

  Rectangle dest = {entity->pos.x, entity->pos.y, frameWidth * scale,
                    frameHeight * scale};

  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(entity->texture, source, dest, origin, 0.0f, WHITE);
}

void update_animation(Entity *entity, float deltaTime) {
  entity->frameTimer += deltaTime;

  while (entity->frameTimer >= entity->frameDuration) {
    entity->frameTimer -= entity->frameDuration;
    entity->currentFrame++;
  }

  if (entity->currentFrame >= entity->maxFrames)
    entity->currentFrame %= entity->maxFrames;
}

void set_entity_animation(Entity *entity, AnimationType type,
                          AnimationDirection dir) {
  if (entity->animationType != type || entity->animationDirection != dir) {
    entity->animationType = type;
    entity->animationDirection = dir;
    entity->currentFrame = 0;
    entity->frameTimer = 0;

    if (type == IDLE || type == MOVE) {
      entity->maxFrames = 6;
      entity->frameDuration = 0.1f;
    } else if (type == ATTACK) {
      entity->maxFrames = 4;
      entity->frameDuration = 0.1f;
    } else if (type == DEATH) {
      entity->maxFrames = 3;
      entity->frameDuration = 0.3f;
    }
  }
}
