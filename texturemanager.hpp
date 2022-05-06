#pragma once
#include "game.hpp"
class Texturemanager{
public :
static SDL_Texture* LoadTexture(const char* texture  ) ;
static void Draw(SDL_Texture *tex , SDL_Rect  src , SDL_Rect dest);


static void dispscreen(const char *texture ,  SDL_Rect src , SDL_Rect dest);
};