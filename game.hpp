#pragma once
#ifndef test_hpp
#define test_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
class Game
{

public:
    Game();
    ~Game();
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();
    void disp_startscreen();
    void disp_instructions() ; 
    static void AddTile(int id, int x, int y);
    void read_data(int new_socket , char * buffer , int l);
    void send_data(int new_socket , const char * hello , int len , int z) ; 
    void handleEvents();
    bool running() { return isRunning; }

    static SDL_Renderer *renderer, *renderer1;
    static SDL_Event event;
    int xpos , ypos ,expos , eypos ;
    int gameover ;
    int player1_wins ;

private:
    bool isRunning;
    int cnt;
    SDL_Window *window;
};
#endif