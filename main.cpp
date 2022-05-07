
#include "game.hpp"
#include "game.cpp"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 1210
char cs = 's';

Game *game = nullptr;
int main(int argc, char *argv[])
{
    int starttime;
    SDL_Texture *start_screen;
    start_screen = Texturemanager::LoadTexture("startscreen.png");
    game = new Game();
    game->init(
        "IIT-D RUSH ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900  , 700, false

    );
    bool startscreen = true;

    bool instructionscreen = false;

    while (1)
    {
        if(startscreen)
        {
        game->disp_startscreen();
        game->handleEvents(); 
        if(!game->running())
        {
            break;
        }
        
        //resolve this 


        if (Game::event.type == SDL_KEYDOWN)
        {

            if (Game::event.key.keysym.sym == SDLK_s)
            {
                startscreen = false;
                game->start_time_of_game = SDL_GetTicks();
                break;
            }
            if (Game::event.key.keysym.sym == SDLK_c)
            {
                startscreen = false;
                game->start_time_of_game = SDL_GetTicks();

                cs = 'c';
                break;
            }
            if (Game::event.key.keysym.sym == SDLK_i)
            {
                startscreen = false;
                instructionscreen = true;
                
            }
        }
        }
        else if(instructionscreen)
        {
             game->handleEvents();
                    game->disp_instructions();

                    if (Game::event.type == SDL_KEYDOWN)
                    {
                        if (Game::event.key.keysym.sym == SDLK_b)
                        {
                            startscreen = true;
                            instructionscreen = false;
                        }
                    }
        }
    }

    int s1 = 0;
    int s2 = 0;
    if(game->running()){
    if (cs == 's')
    {
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[20] = {0};

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET,
                       SO_REUSEADDR | SO_REUSEPORT, &opt,
                       sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        bool youwin = false;
        bool youlose = false;

        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart;
        int frameTime;

        while (game->running())
        {
            if (!startscreen)
            {

                if (!instructionscreen && !youwin && !youlose && !game->gameover && !game->player1_wins)
                {

                    game->handleEvents();
                    game->update();
                    game->render();
                    const char *hello;

                    uint32_t snt = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    uint32_t recvd;

                    send(new_socket, &snt, sizeof(snt), 0);

                    recv(new_socket, &recvd, sizeof(recvd), 0);

                    std::cout << "lol snt,rcv = " << snt << "," << recvd << "," << game->gameover << std::endl;

                    int x, y, z;
                    x = game->expos;
                    y = game->eypos;
                    z = recvd % 1000;
                    game->expos = recvd % 1000;
                    recvd /= 1000;
                    if (recvd % 1000 != y || x != z)
                    {
                        game->anime = true;
                    }
                    else
                    {
                        game->anime = false;
                    }
                    if (x > z)
                    {
                        game->flipped = true;
                    }
                    else
                    {
                        game->flipped = false;
                    }
                    game->eypos = recvd % 1000;
                    recvd /= 1000;
                    if (recvd % 10 == 1|| game->gameover)
                    {
                        youlose = true;
                    }
                    recvd /= 10;
                    if (recvd % 10 == 1 || game->player1_wins)
                    {
                        youwin = true;
                    }

                    s1 = SDL_GetTicks();
                }
                else if (youlose || game->player1_wins|| game->gameover)
                {
                    uint32_t snt = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    uint32_t recvd;

                    send(new_socket, &snt, sizeof(snt), 0);

                    recv(new_socket, &recvd, sizeof(recvd), 0);
                    game->handleEvents();
                    SDL_Rect a, b;
                    a.x = a.y = 0;
                    a.w = 4800;
                    a.h = 3200;
                    b.h = 100 * 6;
                    b.x = b.y = 0;

                    b.w = 150 * 6;
                    game->disp_youlose();
                    std::cout << "server lose ! \n";
                }

                else if (youwin || game->gameover)
                {
                    uint32_t snt = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    uint32_t recvd;

                    send(new_socket, &snt, sizeof(snt), 0);

                    recv(new_socket, &recvd, sizeof(recvd), 0);
                    game->handleEvents();
                    SDL_Rect a, b;
                    a.x = a.y = 0;
                    a.w = 4800;
                    a.h = 3200;
                    b.h = 100 * 6;
                    b.x = b.y = 0;

                    b.w = 150 * 6;
                    std::cout << "server wins !\n";
                    game->disp_youwin();
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
                            instructionscreen = false;
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
    }
    else
    {
        bool youwin = false, youlose = false;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char buffer[20] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary
        // form
        if (inet_pton(AF_INET, "10.194.62.38", &serv_addr.sin_addr) <= 0)
        {
            printf(
                "\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr,
                    sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        SDL_Texture *start_screen;
        start_screen = Texturemanager::LoadTexture("startscreen.png");

        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart;
        int frameTime;

        while (game->running())
        {
            if (!startscreen)
            {
                if (!instructionscreen && !youwin && !youlose && !game->gameover && !game->player1_wins)

                {

                    game->handleEvents();
                    game->update();
                    game->render();

                    // game->send_data(sock, hello, strlen(hello), 0);
                    // game->read_data(sock, buffer, 20);

                    u_int32_t snd, recvd;
                    snd = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    send(sock, &snd, sizeof(snd), 0);

                    recv(sock, &recvd, sizeof(recvd), 0);
                    std::cout << "snt , rcv = " << snd << "," << recvd << "," << game->gameover << std::endl;

                    int x, y, z;
                    x = game->expos;
                    y = game->eypos;
                    game->expos = recvd % 1000;
                    z = recvd % 1000;
                    recvd /= 1000;
                    game->eypos = recvd % 1000;
                    if (y != recvd % 1000 || x != z)
                    {
                        game->anime = true;
                    }
                    else
                    {
                        game->anime = false;
                    }
                    if (x > z)
                    {
                        game->flipped = true;
                    }
                    else
                    {
                        game->flipped = false;
                    }
                    recvd /= 1000;
                    if (recvd % 10 == 1 || game->gameover)
                    {
                        youlose = true;
                    }
                    recvd /= 10;
                    if (recvd % 10 == 1 || game->player1_wins)
                    {
                        youwin = true;
                    }

                    s2 = SDL_GetTicks();
                }
                else if (youwin || game->gameover)
                {
                    u_int32_t snd, recvd;
                    snd = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    send(sock, &snd, sizeof(snd), 0);

                    recv(sock, &recvd, sizeof(recvd), 0);

                    game->handleEvents();

                    SDL_Rect a, b;
                    a.x = a.y = 0;
                    a.w = 4800;
                    a.h = 3200;
                    b.h = 100 * 6;
                    b.x = b.y = 0;

                    b.w = 150 * 6;
                    game->disp_youwin();
                    std::cout << "client wins! ";
                }
                else if (youlose || game->player1_wins)
                {
                    u_int32_t snd, recvd;
                    snd = game->xpos + 1000 * game->ypos + 1000000 * game->player1_wins + 10000000 * game->gameover;
                    send(sock, &snd, sizeof(snd), 0);

                    recv(sock, &recvd, sizeof(recvd), 0);
                    game->handleEvents();

                    SDL_Rect a, b;
                    a.x = a.y = 0;
                    a.w = 4800;
                    a.h = 3200;
                    b.h = 100 * 6;
                    b.x = b.y = 0;

                    b.w = 150 * 6;
                    game->disp_youlose();
                    std::cout << "client lose !\n";
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
                            instructionscreen = false;
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
    }
    }
    game->clean();
}