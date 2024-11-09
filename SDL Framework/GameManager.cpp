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
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		//Calling to our Graphics singleton
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized) {
			mQuit = true;
		}
		mTimer = Timer::Instance();

		mParent = new GameEntity(100.0f, 400.0f);
		mChild = new GameEntity(100.0f, 500.0f);


		//this happens before we are attaching the child to the parent
		printf("Child local pos: (%f, %f)\n",
			mChild->getPosition(GameEntity::Local).x,
			mChild->getPosition(GameEntity::Local).y);

		mChild->Parent(mParent);

		//This is happening after we are attaching the child to the parent
		printf("Child local pos: (%f, %f)\n",
			mChild->getPosition(GameEntity::Local).x,
			mChild->getPosition(GameEntity::Local).y);
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