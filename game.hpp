#pragma once
#ifndef test_hpp
#define test_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
class Game {

    public :
        Game();
        ~Game() ; 
        void init(const char * title  , int xpos , int ypos ,   int width , int height , bool fullscreen  ) ; 
        void update( );
        void render() ;
        void clean (); 
        static void AddTile(int id , int x , int y ) ;
        
        void handleEvents() ; 
        bool running() {return isRunning;}

        
    static SDL_Renderer *renderer ;
    static SDL_Event event ; 
    
    

    private : 
    bool isRunning ; 
    int cnt ; 
    SDL_Window *window ;
    
  
};
#endif  