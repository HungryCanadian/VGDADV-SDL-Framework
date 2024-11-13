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
		mInputManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mTex->Translate(Vector2(0.0f, -40.0f) * mTimer->DeltaTime(), GameEntity::Local);			
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
			mTex->Translate(Vector2(0.0f, 40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mTex->Translate(Vector2(-40.0f, 0.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mTex->Translate(Vector2(40.0f, 0.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			mTex->Rotation(mTex->getRotation(GameEntity::Local) + -180.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			mTex->Rotation(mTex->getRotation(GameEntity::Local) + 180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
			mTex->Scale(mTex->getScale() + Vector2(0.1f, 0.1f));
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			mTex->Scale(mTex->getScale() - Vector2(0.1f, 0.1f));
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_I)) {
			mRedShip->Translate(Vector2(0.0f, -40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_K)) {
			mRedShip->Translate(Vector2(0.0f, 40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_J)) {
			mRedShip->Rotation(mRedShip->getRotation(GameEntity::Local) + -180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_L)) {
			mRedShip->Rotation(mRedShip->getRotation(GameEntity::Local) + 180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyPressed(SDL_SCANCODE_W)) {
			std::cout << "W Key Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_W)) {
			std::cout << "W Key Released" << std::endl;
		}
		if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
			std::cout << "S Key Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_S)) {
			std::cout << "S Key Released" << std::endl;
		}
		if (mInputManager->KeyPressed(SDL_SCANCODE_A)) {
			std::cout << "A Key Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_A)) {
			std::cout << "A Key Released" << std::endl;
		}
		if (mInputManager->KeyPressed(SDL_SCANCODE_D)) {
			std::cout << "D Key Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_D)) {
			std::cout << "D Key Released" << std::endl;
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_ESCAPE)) {
			mQuit = true;
		}
		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Key Pressed" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Key Released" << std::endl;
		}
		if (mInputManager->MouseButtonPressed(InputManager::LEFT)) {
			std::cout << "Left Mouse Button Pressed" << std::endl;
		}
		if (mInputManager->MouseButtonReleased(InputManager::LEFT)) {
			std::cout << "Left Mouse Button Released" << std::endl;
		}
	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();
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
		mInputManager = InputManager::Instance();

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

		InputManager::Release();
		mInputManager = nullptr;

		//Quit SDL
		SDL_Quit();
	}


}