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
		//std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;
	}

	void GameManager::LateUpdate() {

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mTex->Render();
		mRedShip->Render();
		mGreenGalaga->Render();
		mPurpleGalaga->Render();

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		//Calling to our Graphics singleton
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized) {
			mQuit = true;
		}

		mTimer = Timer::Instance();
		mAssetManager = AssetManager::Instance();

		mTex = new Texture("SpriteSheet.png", 182, 54, 20, 20);
		mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
		mTex->Scale(Vector2(2.0f, 2.0f));

		mRedShip = new Texture("SpriteSheet.png", 182, 74, 20, 20);
		mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.49f));
		mRedShip->Scale(Vector2(2.0f, 2.0f));

		mGreenGalaga = new Texture("SpriteSheet.png", 182, 100, 20, 20);
		mGreenGalaga->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.49f));
		mGreenGalaga->Scale(Vector2(2.0f, 2.0f));

		mPurpleGalaga = new Texture("SpriteSheet.png", 182, 125, 20, 20);
		mPurpleGalaga->Position(Vector2(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.49f));
		mPurpleGalaga->Scale(Vector2(2.0f, 2.0f));
		

	}

	GameManager::~GameManager() {
		//Release Variables
		delete mTex;
		mTex = nullptr;
		delete mRedShip;
		mRedShip = nullptr;
		delete mGreenGalaga;
		mGreenGalaga = nullptr;
		delete mPurpleGalaga;
		mPurpleGalaga = nullptr;

		//Release Modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		//Quit SDL
		SDL_Quit();
	}


}