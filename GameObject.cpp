#pragma once

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
    energy = 10;
    health = 10;
    nhealth = 0;
    nenergy = 0;
    frames = 2;
    isAnime = false;
    completed_lect_1 = false;
    completed_lect_2 = false;
    library = false;
    has_played = false;
    time_spend_in_lhc = 0;
    time_spend_in_lib = 0;
    time_spend_eating = 0;
    time_spend_resting = 0;
    time_spend_in_pg = 0;
    inlhc = false;
    inlhc1 = false;
    inlib = false;
    mission_failed = false;

    ingirnar = false;
    inhimardri = false;
    ind16 = false;
    insac = false;
    inplayground = false;
    start_time = 0;
    start_time1 = 0;
    completed_first_lec = false;
    completed_second_lec = false;
    completed_library = false;
    completed_play = false;
    completed_objectives = false;

    SDL_RendererFlip spriteflip = SDL_FLIP_NONE;
}

void GameObject::update1(int x , int y , bool animate)
{
    if(!animate)
    {
    srcRect.x = 0 ;
  
    }
    else 
    {
        srcRect.x = srcRect.w * ((SDL_GetTicks() / speed) % 2);
        
    }
      srcRect.y = 0 ;
    srcRect.w = 1024;
    srcRect.h = 1024 ; 
    DestRect.x = x;
    DestRect.y = y;
    DestRect.w = 32;
    DestRect.h = 32;

}
void GameObject::update()
{

    if (Game::event.type == SDL_KEYDOWN)
    {

        if (Game::event.key.keysym.sym == SDLK_w)
        {
            speedy = -2;
            isAnime = true;
        }
        if (Game::event.key.keysym.sym == SDLK_s)
        {
            speedy = 2;
            isAnime = true;
        }
        if (Game::event.key.keysym.sym == SDLK_a)
        {
            speedx = -2;
            isAnime = true;
            spriteflip = SDL_FLIP_HORIZONTAL;
        }
        if (Game::event.key.keysym.sym == SDLK_d)
        {
            speedx = 2;
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

    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6865 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6865) && speedx > 0)
    {
        speedx = 0;
        isAnime = false;
    }

    if ((lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6865 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6865) && speedx < 0)
    {
        speedx = 0;
        isAnime = false;
    }
    if ((lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6865 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6865) && speedy > 0)
    {
        speedy = 0;
        isAnime = false;
    }
    if ((lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6865 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6865) && speedy < 0)
    {
        speedy = 0;
        isAnime = false;
    }




    if (((xpos + 32) / 6) >= 150 && speedx > 0  )
    {
        speedx = 0;
        isAnime = false;
    }
    if((xpos - 1 )/6 < 0 && speedx < 0 )
    {
        speedx = 0 ; 
    }

    if(((ypos+64) / 7 ) >= 100 && speedy > 0)
    {
        speedy = 0 ;
    }
    if((ypos - 1 ) / 7  < 0 && speedy < 0 )
    {
        speedy  = 0 ; 
    }


    // going to LHC
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6850 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6850) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6850 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6850) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6850 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6850) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6850 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6850))
    {
        if (!inlhc)
            start_time = SDL_GetTicks();

        inlhc = true;
        std::cout << "in lhc"
                  << " " << time_spend_in_lhc << std::endl;

        time_spend_in_lhc = (SDL_GetTicks() - start_time) / 1000;
    }
    else
    {
        inlhc = false;
        time_spend_in_lhc = 0;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6890 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6890) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6890 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6890) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6890 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6890) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6890 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6890))
    {
        std::cout << "in sac\n";
        if (!insac)
            start_time = SDL_GetTicks();

        insac = true;
        time_spend_in_pg = (SDL_GetTicks() - start_time) / 1300;
    }
    else
    {
        insac = false;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6860 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6860) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6860 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6860) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6860 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6860) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6860 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6860))
    {
        std::cout << "in girnar\n";
        if (!ingirnar)
        {
            start_time = SDL_GetTicks() - 1000 * energy;
            start_time1 = SDL_GetTicks() - 1300 * health;
        }

        ingirnar = true;

        energy = (SDL_GetTicks() - start_time) / 1000;
        health = (SDL_GetTicks() - start_time1) / 1300;
    }
    else
    {
        ingirnar = false;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6938 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6938) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6938 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6938) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6938 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6938) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6938 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6938))
    {

        std::cout << "in lib\n";
        if (!inlib)
            start_time = SDL_GetTicks();
        inlib = true;
        time_spend_in_lib = (SDL_GetTicks() - start_time) / 1000;
        std::cout << time_spend_in_lib << std::endl;
    }
    else
    {
        inlib = false;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6900 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6900) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6900 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6900) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6900 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6900) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6900 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6900))
    {
        std::cout << "in playground ";
        if (!inplayground)
            start_time = SDL_GetTicks();

        inplayground = true;
        time_spend_in_pg = (SDL_GetTicks() - start_time) / 1000;
        std::cout << time_spend_in_pg << std::endl;
    }
    else
    {
        inplayground = false;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6902 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6902) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6902 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6902) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6902 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6902) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6902 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6902))
    {
        std::cout << "in d16\n";
        if (!ind16)
        {

            start_time1 = SDL_GetTicks() - 1300 * health;
        }
        ind16 = true;
        health = (SDL_GetTicks() - start_time1) / 1300;
    }
    else
    {
        ind16 = false;
    }
    if ((lvl1[((xpos + 32) / 6) + (150 * ((ypos + 29) / 7))] == 6913 || lvl1[((xpos + 32) / 6) + (150 * ((ypos + 3) / 7))] == 6913) ||
        (lvl1[((xpos) / 6) + (150 * ((ypos + 29) / 7))] == 6913 || lvl1[((xpos) / 6) + (150 * ((ypos + 3) / 7))] == 6913) ||
        (lvl1[((xpos + 29) / 6) + (150 * ((ypos + 32) / 7))] == 6913 || lvl1[((xpos + 3) / 6) + (150 * ((ypos + 32) / 7))] == 6913) ||
        (lvl1[((xpos + 3) / 6) + (150 * ((ypos) / 7))] == 6913 || lvl1[((xpos + 29) / 6) + (150 * ((ypos) / 7))] == 6913))
    {
        std::cout << "in himadri\n";

        if (!inhimardri)
        {
            start_time = SDL_GetTicks() - 1000 * energy;
            start_time1 = SDL_GetTicks() - 1300 * health;
        }
        inhimardri = true;

        energy = (SDL_GetTicks() - start_time) / 1000;
        health = (SDL_GetTicks() - start_time1) / 1300;
    }
    else
    {
        inhimardri = false;
    }

    nhealth = SDL_GetTicks() / 3000;
    nenergy = SDL_GetTicks() / 3000;

    if (time_spend_in_lhc >= 10 && !completed_lect_1)
    {
        completed_lect_1 = true;
        time_spend_in_lhc = 0;
    }
    if (time_spend_in_lhc >= 10 && completed_lect_1 && completed_library)
    {
        completed_lect_2 = true;
    }
    if (time_spend_in_lib >= 10 && completed_lect_1)
    {
        completed_library = true;
    }
    if (time_spend_in_pg >= 10 && completed_lect_2)
    {
        completed_play = true;
    }

    if (completed_play)
    {
        completed_objectives = true;
    }
    if (completed_objectives)
        std::cout << "completed_objectives" << std::endl;

    if (health + nhealth <= 0 || energy + nenergy <= 0)
    {
        mission_failed = true;
    }

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
            spriteflip = SDL_FLIP_NONE;
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

    srcRect.h = 249;
    srcRect.w = 248.5;
    if (isAnime)
    {
        srcRect.x = srcRect.w * ((SDL_GetTicks() / speed) % frames);
    }
    else
    {
        srcRect.y = 0;
        srcRect.x = 0;
    }
    DestRect.x = xpos;
    DestRect.y = ypos;
    DestRect.w = 32;
    DestRect.h = 32;
}
void GameObject::Render()
{
    SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &DestRect, NULL, NULL, spriteflip);
}
