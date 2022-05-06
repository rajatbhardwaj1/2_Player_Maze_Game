
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
#define PORT 9898
char cs = 'c';
Game *game = nullptr;
int main(int argc, char *argv[])
{

    if (cs == 's')
    {
        
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};

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
            "IIT-D RUSH ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false 

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
                    valread = read(new_socket, buffer, 1024);
                    printf("%s\n", buffer);
                    const char *hello;
                    std::string s = std::to_string(game->xpos) + "," + std::to_string(game->ypos) + "\n";
                    hello = s.c_str();
                    
                    game->send_data(new_socket, hello, strlen(hello), 0);
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

        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client";
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary
        // form
        if (inet_pton(AF_INET, "10.194.63.63", &serv_addr.sin_addr) <= 0)
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

        bool startscreen = true;

        bool instructionscreen = false;
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart;
        int frameTime;

        game = new Game();
        game->init(
            "IIT-D RUSH ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false 

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

                    std::string s = std::to_string(game->xpos) + "," + std::to_string(game->ypos);
                    const char *hello = s.c_str();
                    game->send_data(sock, hello, strlen(hello), 0);
                    game->read_data(sock, buffer, 1024);
                    printf("%s\n", buffer);
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
    game->clean();
}