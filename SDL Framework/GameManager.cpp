#include "GameManager.h"

namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		while (!mQuit) {
			mTimer->Update();
			while (SDL_PollEvent(&mEvents) != 0) {
				if (mEvents.type == SDL_QUIT) {
					mQuit = true;
				}
			}

			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();
			}
		}
	}

	void GameManager::Update() {
		std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;
	}

	void GameManager::LateUpdate() {

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false), mGraphics(nullptr) {
		//Calling to our Graphics singleton
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized) {
			mQuit = true;
		}
		mTimer = Timer::Instance();
	}

	GameManager::~GameManager() {
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		//Quit SDL
		SDL_Quit();
	}


}