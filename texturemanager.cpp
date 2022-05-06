#include "texturemanager.hpp"

SDL_Texture *Texturemanager::LoadTexture(const char *texture) {
    SDL_Surface *tempsurface  = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer , tempsurface  ) ; 
    
    SDL_FreeSurface(tempsurface);
    return tex ;
    
}

void Texturemanager::Draw(SDL_Texture *tex , SDL_Rect src , SDL_Rect dest){
    SDL_RenderCopy (Game::renderer , tex , &src , &dest) ; 
}
void Texturemanager::dispscreen(const char *texture ,  SDL_Rect src , SDL_Rect dest)
{
    SDL_Surface *tempsurface  = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer , tempsurface  ) ; 
    
    SDL_FreeSurface(tempsurface);
    SDL_RenderCopy (Game::renderer , tex , &src , &dest) ; 


}