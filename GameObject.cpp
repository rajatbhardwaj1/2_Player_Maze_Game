#include "GameObject.hpp"
#include "texturemanager.hpp"
#include "Map.hpp"
GameObject::GameObject(const char *texturesheet, int x, int y)
{
    objTexture = Texturemanager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    speedx = 0;
    speedy = 0;
    speed = 100;
    frames = 8;
    isAnime = false;
    SDL_RendererFlip spriteflip = SDL_FLIP_NONE ;
}

void GameObject::update()
{
    if (Game::event.type == SDL_KEYDOWN)
    {

        if (Game::event.key.keysym.sym == SDLK_w)
        {
            speedy = -5;
            isAnime = true;
        }
        if (Game::event.key.keysym.sym == SDLK_s)
        {
            speedy = 5;
            isAnime = true;
        }
        if (Game::event.key.keysym.sym == SDLK_a)
        {
            speedx = -5;
            isAnime = true;
            spriteflip = SDL_FLIP_HORIZONTAL ;
        }
        if (Game::event.key.keysym.sym == SDLK_d)
        {
            speedx = 5;
            isAnime = true;
        }
    }

    // if ((lvl1[((ypos +  32) /  32) * ((xpos + 29) /  32)] !=  21|| lvl1[((ypos +  32) /  32) * ((xpos + 3) /  32)] !=  21) && speedy == 5)
    // {
    //     speedy = 0;
    //     isAnime = false;
    // }
    // if ((lvl1[((ypos) /  32) * ((xpos + 29) /  32)] !=  21 || lvl1[((ypos) /  32) * ((xpos + 3) /  32)] !=  21) && speedy == -5)
    // {
    //     speedy = 0;
    //     isAnime = false;
    // }
    // if ((lvl1[((ypos + 29) /  32) * ((xpos +  32) /  32)] !=  21 || lvl1[((ypos + 3) /  32) * ((xpos +  32) /  32)] !=  21) && speedx == 5)
    // {
    //     speedx = 0;
    //     isAnime = false;
    // }
    // if ((lvl1[((ypos + 29) /  32) * ((xpos) /  32)] !=  21 || lvl1[((ypos + 3) /  32) * ((xpos) /  32)] !=  21) && speedx == -5)
    // {
    //     speedx = 0;
    //     spriteflip = SDL_FLIP_NONE ; 
    //     isAnime = false;
    // }

    if (Game::event.type == SDL_KEYUP)
    {
        if (Game::event.key.keysym.sym == SDLK_w)
        {
            speedy = 0;
            isAnime = false;
        }
        if (Game::event.key.keysym.sym == SDLK_s)
        {
            speedy = 0;
            isAnime = false;
        }
        if (Game::event.key.keysym.sym == SDLK_a)
        {
            speedx = 0;
            spriteflip = SDL_FLIP_NONE ; 
            isAnime = false;
        }
        if (Game::event.key.keysym.sym == SDLK_d)
        {
            speedx = 0;
            isAnime = false;
        }
    }
    xpos += speedx;
    ypos += speedy;

    srcRect.h = 32;
    srcRect.w = 32;
    if (isAnime)
    {
        srcRect.y = 32;
        srcRect.x = srcRect.w * ((SDL_GetTicks() / speed) % frames);
    }
    else
    {
        srcRect.y = 0;
        srcRect.x = 0 ;
    }
    DestRect.x = xpos;
    DestRect.y = ypos;
    DestRect.w = srcRect.w*2;
    DestRect.h = srcRect.h*2;
}
void GameObject::Render()
{
    SDL_RenderCopyEx (Game::renderer, objTexture, &srcRect, &DestRect , NULL , NULL , spriteflip );
}
