// SDL Framework.cpp : 

#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
	//initialize SDL subsystems
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		// we have failed to initialize SDL
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}


	//Terminate SDL subsystems

	SDL_Quit();
	std::cout << "Hello World!\n";
	return 0;
    
}

