
#include <SDL2/SDL.h>

#include "texturemanager.hpp"
#include "texturemanager.cpp"

#include "Map.hpp"
#include "Map.cpp"
#include <iostream>
#include "GameObject.hpp"
#include "GameObject.cpp"

Map  *map1 ;
SDL_Event Game ::event;

SDL_Renderer *Game ::renderer = nullptr;
GameObject *player1;
Game::Game()
{
}
Game ::~Game()
{
}
void Game ::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "subsystems initialised" << std ::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            std ::cout << "window created" << std ::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std ::cout << "renderer created" << std ::endl;
        }
        isRunning = true;

        map1 = new Map();

      


        player1 = new GameObject("player_anims.png", 0, 0);
    }

    else
    {
        isRunning = false;
    }
}
void Game ::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;

        break;

    default:
        break;
    }
}
void Game::update()
{
    cnt++;
  
    std::cout << player1->xpos << ", " << player1->ypos << "," << lvl1[(player1->xpos / 32 )*(player1->ypos / 32)] << std::endl;
    player1->update();
    
    map1->mapxpos =  -player1->xpos;
    map1->mapypos = -player1->ypos;

}
void Game::render()
{

    SDL_RenderClear(renderer);
    map1->DrawMap();
    player1->Render();

    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game ends !" << std::endl;
}
void Game::AddTile(int id, int x, int y)
{
    SDL_Rect src, dest;
    src.x = src.y = 0;
    src.w = src.h = 32;
    dest.h = dest.w = 32;
    dest.x = x ;
    dest.y = y ;

    switch (id)
            {
            case 0:
                Texturemanager::Draw(Texturemanager::LoadTexture("water.png"), src, dest);

                break;
            case 1:
                Texturemanager::Draw(Texturemanager::LoadTexture("grass.png"), src, dest);
                break;
            case 2:
                Texturemanager::Draw(Texturemanager::LoadTexture("dirt.png"), src, dest);

            default:
                break;
            }
};