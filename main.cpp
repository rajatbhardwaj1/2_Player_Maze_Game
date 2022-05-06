
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
char cs = 's';

Game *game = nullptr;
int main(int argc, char *argv[])
{

int s1 = 0 ; 
int s2 = 0 ;
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
                    const char *hello;
                    std::string s = std::to_string(game->xpos) + "," + std::to_string(game->ypos)+"." ;
                    hello = s.c_str();
                    
                   
                    uint32_t snt =  game->xpos + 10000*game->ypos ;
                    uint32_t recvd ;

                    send(new_socket , &snt , sizeof(snt) , 0  ) ; 

                    recv(new_socket , &recvd , sizeof(recvd) , 0 ) ;



                    // int excord , eycord;
                    // std::string s1 = "" , s2 = "";
                    // bool second  = false ;
                    // for(char pp: buffer)
                    // {
                    //     if(pp == ',')
                    //     {
                    //         second = true ;
                    //     }
                    //     else 
                    //     {
                    //         if(pp == '.')break;
                    //         else 
                    //         {
                    //             if(second)s2+= pp ;
                    //             else s1 += pp ;
                    //         }
                    //     }
                    // }
                    // game->expos = stoi(s1);
                    // game->eypos = stoi(s2) ; 
                    game->expos = recvd % 10000 ;
                    recvd /= 10000;
                    game->eypos = recvd %10000 ; 



                    s1 = SDL_GetTicks() ; 
                    

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

                    std::string s = std::to_string(game->xpos) + "," + std::to_string(game->ypos) + ".";
                    const char *hello = s.c_str();
                    
                    // game->send_data(sock, hello, strlen(hello), 0);
                    // game->read_data(sock, buffer, 20);
                    
                    u_int32_t snd , recvd ; 
                    snd =  game->xpos + 10000*game->ypos ;
                    send(sock , &snd , sizeof(snd) , 0) ;
                    
                    recv(sock , &recvd , sizeof(recvd) , 0 ) ;

                    game->expos = recvd % 10000 ;
                    recvd /= 10000;
                    game->eypos = recvd %10000 ; 
                    s2 = SDL_GetTicks () ; 
                    
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