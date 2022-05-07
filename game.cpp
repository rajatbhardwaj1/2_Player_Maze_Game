#pragma once
#include <SDL2/SDL.h>

#include "texturemanager.hpp"
#include "texturemanager.cpp"

#include "Map.hpp"
#include "Map.cpp"
#include <iostream>
#include "GameObject.hpp"
#include "GameObject.cpp"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
Map *map1;
SDL_Event Game ::event;

SDL_Renderer *Game ::renderer = nullptr;
SDL_Renderer *gRenderer;
GameObject *player1, *enemy;

std::string status = "GO to LHC! ";
Game::Game()
{
	gameover = 0;
	player1_wins = 0;
	anime = false;
	start_time_of_game = 0 ;
	flipped  = false ;

}
Game ::~Game()
{
}

class LTexture
{
public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture *mTexture;

private:
	// The actual hardware texture

	// Image dimensions
	int mWidth;
	int mHeight;
};

// Starts up SDL and creates window
bool init();

// Loads media

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer

// Globally used font
TTF_Font *gFont = NULL;

// Rendered texture
LTexture gTextTexture;
LTexture player1_health, player1_energy, player1_status;

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
	// Return success
}
void LTexture::free()
{
	// Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(Game::renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(Game::renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	// Free loaded images
	gTextTexture.free();
	player1_energy.free();
	player1_health.free();
	player1_status.free();

	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	// Destroy window
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game ::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initialised" << std ::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std ::cout << "window created" << std ::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std ::cout << "renderer created" << std ::endl;
		}
		isRunning = true;

		map1 = new Map();

		player1 = new GameObject("p1p2.png", 866, 84);
		enemy = new GameObject("p2combined.png", 718, 84);

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			isRunning = false;
		}

		// Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			isRunning = false;
		}
		gFont = TTF_OpenFont("fonts/Roboto-Black.ttf", 28);
		if (gFont == NULL)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			isRunning = false;
		}
		else
		{
			// Render text
			SDL_Color textColor = {0xff, 0, 0};
		}
		// Main loop flag

		// Event handler

		// Clear screen
		SDL_RenderClear(renderer);

		// Render current frame

		// Update screen
		SDL_RenderPresent(renderer);
	}
}
void Game ::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;

		break;

	default:
		break;
	}
}

void Game::read_data(int new_socket, char *buffer, int l)
{
	read(new_socket, buffer, 1024);
}
void Game::send_data(int new_socket, const char *hello, int len, int z)
{
	send(new_socket, hello, strlen(hello), 0);
}
void Game::update()
{
	player1->start_time_of_game = start_time_of_game ; 
	cnt++;
	SDL_Color textColor = {0xff, 0, 0};
	if (player1->completed_lect_1)
	{
		status = "Go to library";
	}
	if (player1->completed_library)
	{
		status = "Go to LHC";
	}
	if (player1->completed_lect_2)
	{
		status = "Go to Play";
	}
	if (player1->completed_play)
	{
		status = "Done!";
	}
	gTextTexture.loadFromRenderedText("Player Scores 44", textColor);
	player1_energy.loadFromRenderedText("ENERGY " + std::to_string(player1->energy - player1->nenergy), textColor);
	player1_health.loadFromRenderedText("HEALTH " + std::to_string(player1->health - player1->nhealth), textColor);
	player1_status.loadFromRenderedText("STATUS: " + status, textColor);
	player1->update();

	enemy->update1(expos, eypos, anime , flipped);
	map1->mapxpos = -player1->xpos;
	map1->mapypos = -player1->ypos;
	xpos = player1->xpos;
	ypos = player1->ypos;

	if (player1->mission_failed)
	{
		gameover = 1;
	}
	if (player1->completed_objectives)
	{
		player1_wins = 1;
	}
}
void Game::render()
{

	SDL_RenderClear(renderer);
	map1->DrawMap();

	// Render current frame

	player1->Render();
	enemy->Render();
	gTextTexture.render(0, 0);
	player1_energy.render(250, 0);
	player1_health.render(440, 0);
	player1_status.render(610, 0);
	SDL_RenderPresent(Game::renderer);
}
void Game::disp_startscreen()
{
	map1->StartScreen();
	SDL_RenderPresent(Game::renderer);
}

void Game::disp_instructions()
{
	map1->DisplayInstructions();
	SDL_RenderPresent(Game::renderer);
}
void Game ::disp_youwin()
{
	map1->Disp_youwin();
	SDL_RenderPresent(Game::renderer);
}
void Game::disp_youlose()
{
	map1->Disp_youlose();
	SDL_RenderPresent(Game::renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	close();
	SDL_Quit();
	std::cout << "Game ends !" << std::endl;
}
void Game::AddTile(int id, int x, int y)
{
	SDL_Rect src, dest;
	src.x = src.y = 0;
	src.w = src.h = 32;
	dest.h = dest.w = 32;
	dest.x = x;
	dest.y = y;

	switch (id)
	{
	case 0:
		Texturemanager::Draw(Texturemanager::LoadTexture("water.png"), src, dest);

		break;
	case 1:
		Texturemanager::Draw(Texturemanager::LoadTexture("grass.png"), src, dest);
		break;
	case 2:
		Texturemanager::Draw(Texturemanager::LoadTexture("dirt.png"), src, dest);

	default:
		break;
	}
};