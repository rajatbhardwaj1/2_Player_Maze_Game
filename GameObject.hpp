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
    bool completed_lect_1 ;
    bool completed_lect_2 ;
    bool library ;
    bool has_played ; 
    int time_spend_in_lhc ; 
    int time_spend_in_lib; 
    int time_spend_in_pg ;
    int time_spend_eating ; 
    int  time_spend_resting; 
    int energy ;
    int health ; 
    int nhealth;
    int nenergy ; 
    bool inlhc;
    bool inlhc1 ; 
    bool inlib ;
    bool ingirnar;
    bool inhimardri ;
    bool ind16;
    bool insac;
    bool inplayground;
    int start_time ; 
    int start_time1; 
    int start_time2 ; 
    bool completed_first_lec ;
    bool completed_second_lec ; 
    bool completed_library ;

    bool completed_play ;
    bool completed_objectives; 
    bool mission_failed; 

    GameObject(const char *texturesheet, int x, int y);

    ~GameObject();
    void update();
    void update1(int x , int y) ; 
    void Render();
};
