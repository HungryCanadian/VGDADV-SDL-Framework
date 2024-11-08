#include "Graphics.h"


namespace SDLFramework {
	//this is how we initialize static members in a class
	//specifically ones that we do not want to be constants!!
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	//this is where we make this class a singleton
	Graphics* Graphics::Instance() {
		//we are checking if sInstance already has an instance of Graphics stored in it.
		if (sInstance == nullptr) {
			//if not, create a new instance of graphics
			sInstance = new Graphics();
		}
		//returns our graphics instance after making sure there is one.
		return sInstance;
	}

	void Graphics::Release() {
		delete sInstance;
		sInstance = nullptr;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	Graphics::Graphics() : mRenderer(nullptr) {
		sInitialized = Init();
	}

	Graphics::~Graphics() {
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
	}
	
	bool Graphics::Init() {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
			return false;
		}

		mWindow = SDL_CreateWindow(
			"SDL Framework",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (mWindow == nullptr) {
			std::cerr << "Failed to create a window! SDL_Error: " << SDL_GetError() << "\n;";
			return false;
		}

		mRenderer = SDL_CreateRenderer(
			mWindow,
			-1,
			SDL_RENDERER_ACCELERATED
		);

		if (mRenderer == nullptr) {
			std::cerr << "Failed to create a renderer! SDL_Error: " << SDL_GetError() << "\n;";
			return false;
		}

		SDL_SetRenderDrawColor(mRenderer, 140, 15, 185, 255);
		return true;
	}

}