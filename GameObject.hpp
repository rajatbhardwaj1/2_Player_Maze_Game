#pragma once
#include "game.hpp"
class GameObject
{
private:
    int speed;
    int frames;
    bool isAnime;

    SDL_Texture *objTexture;
    SDL_Rect srcRect, DestRect;
    SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

public:
    int xpos;
    int ypos;
    int speedx ; 
    int speedy ;
    GameObject(const char *texturesheet, int x, int y);

    ~GameObject();
    void update();
    void Render();
};
