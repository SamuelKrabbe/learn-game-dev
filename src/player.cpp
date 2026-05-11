#include "player.h"
#include "raylib.h"
#include "raymath.h"

inline void Player::update(float deltaTime) {
  if (this->animationType == ATTACK &&
      this->currentFrame < this->maxFrames - 1) {
    this->update_animation(deltaTime);
    return; // don't process other input until attack is done
  }

  AnimationDirection dirInput = this->animationDirection;
  this->dir = (Vector2){0, 0};

  if (IsKeyDown(KEY_W)) {
    this->dir.y -= 1;
    dirInput = UP;
  }
  if (IsKeyDown(KEY_S)) {
    this->dir.y += 1;
    dirInput = DOWN;
  }
  if (IsKeyDown(KEY_A)) {
    this->dir.x -= 1;
    dirInput = LEFT;
  }
  if (IsKeyDown(KEY_D)) {
    this->dir.x += 1;
    dirInput = RIGHT;
  }

  this->dir = Vector2Normalize(this->dir);

  if (this->dir.x == 0 && this->dir.y == 0) {
    this->set_animation(IDLE, dirInput);
  } else {
    this->set_animation(MOVE, dirInput);
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    this->set_animation(ATTACK, dirInput);
  }

  int moveX = this->dir.x * this->vel.x * deltaTime;
  int moveY = this->dir.y * this->vel.y * deltaTime;

  this->pos.x += moveX;
  this->pos.y += moveY;
}

inline void Player::draw() {
  int type = this->animationType;
  float scale = 2.0f;

  float frameWidth = this->frameDim.x;
  float frameHeight = this->frameDim.y;

  float row = type + this->animationDirection;
  float col = this->currentFrame;

  bool flip = false;

  // If LEFT, reuse RIGHT row and flip
  if (this->animationDirection == LEFT) {
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

  Rectangle dest = {this->pos.x, this->pos.y, frameWidth * scale,
                    frameHeight * scale};

  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

inline void Player::update_animation(float deltaTime) {
  this->frameTimer += deltaTime;

  while (this->frameTimer >= this->frameDuration) {
    this->frameTimer -= this->frameDuration;
    this->currentFrame++;
  }

  if (this->currentFrame >= this->maxFrames)
    this->currentFrame %= this->maxFrames;
}

inline void Player::set_animation(AnimationType type, AnimationDirection dir) {
  if (this->animationType != type || this->animationDirection != dir) {
    this->animationType = type;
    this->animationDirection = dir;
    this->currentFrame = 0;
    this->frameTimer = 0;

    if (type == IDLE || type == MOVE) {
      this->maxFrames = 6;
      this->frameDuration = 0.1f;
    } else if (type == ATTACK) {
      this->maxFrames = 4;
      this->frameDuration = 0.1f;
    } else if (type == DEATH) {
      this->maxFrames = 3;
      this->frameDuration = 0.3f;
    }
  }
}
