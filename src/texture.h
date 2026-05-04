#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "raylib.h"

#define TEXTURES_MAX_LENGTH 20
#define FILE_FILTER "DIRS*;.png"

typedef enum { PLAYER, ANIMALS, OBJECTS, TILESET } AssetType;

typedef struct {
  Texture2D animalTextures[TEXTURES_MAX_LENGTH];
  Texture2D characterTextures[TEXTURES_MAX_LENGTH];
  Texture2D objectTextures[TEXTURES_MAX_LENGTH];
  Texture2D particleTextures[TEXTURES_MAX_LENGTH];
  Texture2D tilesetTextures[TEXTURES_MAX_LENGTH];

  int animalTexturesCount;
  int characterTexturesCount;
  int objectTexturesCount;
  int particleTexturesCount;
  int tilesetTexturesCount;
} Textures;

Textures create_textures();

void load_textures(Textures *textures);

void load_animal_textures(Textures *textures);
void load_character_textures(Textures *textures);
void load_object_textures(Textures *textures);
void load_particle_textures(Textures *textures);
void load_tileset_textures(Textures *textures);

void unload_textures(Textures *textures);

void unload_animal_textures(Textures *textures);
void unload_character_textures(Textures *textures);
void unload_object_textures(Textures *textures);
void unload_particle_textures(Textures *textures);
void unload_tileset_textures(Textures *textures);

#endif
