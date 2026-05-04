#include "texture.h"
#include "raylib.h"

Textures create_textures() {
  Textures textures = {0};
  return textures;
}

void load_textures(Textures *textures) {
  load_animal_textures(textures);
  load_character_textures(textures);
  load_object_textures(textures);
  load_particle_textures(textures);
  load_tileset_textures(textures);
}

void load_animal_textures(Textures *textures) {
  FilePathList texturesPath =
      LoadDirectoryFilesEx("assets/animals", FILE_FILTER, true);

  for (unsigned int i = 0; i < texturesPath.count; i++) {
    textures->animalTextures[i] = LoadTexture(texturesPath.paths[i]);
    SetTextureFilter(textures->animalTextures[i], TEXTURE_FILTER_POINT);
  }

  textures->animalTexturesCount = texturesPath.count;
  UnloadDirectoryFiles(texturesPath);
}

void load_character_textures(Textures *textures) {
  FilePathList texturesPath =
      LoadDirectoryFilesEx("assets/characters", FILE_FILTER, true);

  // TraceLog(LOG_INFO, "Tileset file count: %d", texturesPath.count);
  //
  // if (texturesPath.count > TEXTURES_MAX_LENGTH) {
  //   TraceLog(LOG_ERROR, "Too many textures! Increase TEXTURES_MAX_LENGTH");
  //   UnloadDirectoryFiles(texturesPath);
  //   return;
  // }

  for (unsigned int i = 0; i < texturesPath.count; i++) {
    textures->characterTextures[i] = LoadTexture(texturesPath.paths[i]);
    SetTextureFilter(textures->characterTextures[i], TEXTURE_FILTER_POINT);
    TraceLog(LOG_INFO, "Loading: %s", texturesPath.paths[i]);
  }

  textures->characterTexturesCount = texturesPath.count;
  UnloadDirectoryFiles(texturesPath);
}

void load_object_textures(Textures *textures) {
  FilePathList texturesPath =
      LoadDirectoryFilesEx("assets/objects", FILE_FILTER, true);

  for (unsigned int i = 0; i < texturesPath.count; i++) {
    textures->objectTextures[i] = LoadTexture(texturesPath.paths[i]);
    SetTextureFilter(textures->objectTextures[i], TEXTURE_FILTER_POINT);
  }

  textures->objectTexturesCount = texturesPath.count;
  UnloadDirectoryFiles(texturesPath);
}

void load_particle_textures(Textures *textures) {
  FilePathList texturesPath =
      LoadDirectoryFilesEx("assets/particles", FILE_FILTER, true);

  for (unsigned int i = 0; i < texturesPath.count; i++) {
    textures->particleTextures[i] = LoadTexture(texturesPath.paths[i]);
    SetTextureFilter(textures->particleTextures[i], TEXTURE_FILTER_POINT);
  }

  textures->particleTexturesCount = texturesPath.count;
  UnloadDirectoryFiles(texturesPath);
}

void load_tileset_textures(Textures *textures) {
  FilePathList texturesPath =
      LoadDirectoryFilesEx("assets/tilesets", FILE_FILTER, true);

  for (unsigned int i = 0; i < texturesPath.count; i++) {
    textures->tilesetTextures[i] = LoadTexture(texturesPath.paths[i]);
    SetTextureFilter(textures->tilesetTextures[i], TEXTURE_FILTER_POINT);
  }

  textures->tilesetTexturesCount = texturesPath.count;
  UnloadDirectoryFiles(texturesPath);
}

void unload_textures(Textures *textures) {
  // TraceLog(LOG_INFO, "Counts: player=%d animalTextures=%d object=%d
  // tileset=%d",
  //          textures->characterTexturesTexturesCount,
  //          textures->animalTexturesTexturesCount,
  //          textures->objectTexturesCount, textures->tilesetTexturesCount);
  unload_animal_textures(textures);
  unload_character_textures(textures);
  unload_object_textures(textures);
  unload_particle_textures(textures);
  unload_tileset_textures(textures);
}

void unload_animal_textures(Textures *textures) {
  for (int i = 0; i < textures->animalTexturesCount; i++) {
    UnloadTexture(textures->animalTextures[i]);
  }
}

void unload_character_textures(Textures *textures) {
  for (int i = 0; i < textures->characterTexturesCount; i++) {
    UnloadTexture(textures->characterTextures[i]);
  }
}

void unload_object_textures(Textures *textures) {
  for (int i = 0; i < textures->objectTexturesCount; i++) {
    UnloadTexture(textures->objectTextures[i]);
  }
}

void unload_particle_textures(Textures *textures) {
  for (int i = 0; i < textures->particleTexturesCount; i++) {
    UnloadTexture(textures->particleTextures[i]);
  }
}

void unload_tileset_textures(Textures *textures) {
  for (int i = 0; i < textures->tilesetTexturesCount; i++) {
    UnloadTexture(textures->tilesetTextures[i]);
  }
}
