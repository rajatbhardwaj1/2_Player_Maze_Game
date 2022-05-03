
#include "game.hpp"
#include "game.cpp"

Game *game = nullptr;
int main(int argc, char *argv[])
{
    SDL_Texture *start_screen;
    start_screen = Texturemanager::LoadTexture("startscreen.png");

    bool startscreen = true;

    bool instructionscreen = false;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init(
        "birch engine ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, true

    );
    while (game->running())
    {
        if (!startscreen)
        {
            if (!instructionscreen)
            {


                game->handleEvents();
                game->update();
                game->render();

               
            }
            else
            {
                game->handleEvents();
                game->disp_instructions();
                if (Game::event.type == SDL_KEYDOWN)
                {
                    if (Game::event.key.keysym.sym == SDLK_b)
                    {
                        startscreen = true;
                        instructionscreen = false ;

                    }
                }
            }
        }
        else
        {
            game->handleEvents();
            SDL_Rect dest, src;

            game->disp_startscreen();
            if (Game::event.type == SDL_KEYDOWN)
            {

                if (Game::event.key.keysym.sym == SDLK_s)
                {
                    startscreen = false;
                }
                if (Game::event.key.keysym.sym == SDLK_i)
                {
                    startscreen = false;
                    instructionscreen = true;
                }
            }
        }
         frameStart = SDL_GetTicks();
                frameTime = SDL_GetTicks() - frameStart;
                if (frameDelay > frameTime)
                {
                    SDL_Delay(frameDelay - frameTime);
                }
    }
    game->clean();
}