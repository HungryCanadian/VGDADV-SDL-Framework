// SDL Framework.cpp : 

#include <iostream>
#include <SDL.h>
#include "graphics.h"



bool quit = false;

int main(int argc, char* args[])
{


	SDL_SetRenderDrawColor(mRenderer, 132, 0, 150, 255);
	SDL_Event events = {};

	//main game loop
	while (!quit) {
		//event polling loop
		while (SDL_PollEvent(&events) != 0) {
			switch (events.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
		//Draw code goes down here
		SDL_RenderFillRect(mRenderer, nullptr);
		SDL_RenderPresent(mRenderer);
	}

	//Destroy the renderer
	SDL_DestroyRenderer(mRenderer);
	//Destroy the window
	SDL_DestroyWindow(mWindow);

	SDL_Quit();
	return 0;
    
}

