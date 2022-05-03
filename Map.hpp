#pragma once

#include "game.hpp"

class Map
{
public:
    Map();
    ~Map();
    void LoadMap(int arr[15000]);
    void StartScreen() ;
    void DisplayInstructions() ; 
    static void LoadMap1(std::string path, int x, int y);
    int mapxvel = 0;
    int mapyvel = 0;
    int mapxpos = 0 ;
    int mapypos = 0 ;

    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;
    SDL_Texture *new_map;
    SDL_Texture *iitd_map ;
    SDL_Texture *start_screen ;
    SDL_Texture *instruction_screen ; 
    
    int map[15000];
};