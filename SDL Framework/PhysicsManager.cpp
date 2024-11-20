#include "PhysicsManager.h"

namespace SDLFramework {

	PhysicsManager* PhysicsManager::sInstance = nullptr;

	PhysicsManager* PhysicsManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new PhysicsManager();
		}

		return sInstance;
	}

	void PhysicsManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	PhysicsManager::PhysicsManager() {
		mLastID = 0;

		for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++) {
			mLayerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
		}
	}

	PhysicsManager::~PhysicsManager() {
		for (auto layer : mCollisionLayers) {
			layer.clear();
		}
	}

	void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flag) {
		mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flag));
	}

	unsigned long PhysicsManager::RegisterEntity(PhysicsEntity* entity, CollisionLayers layer) {
		mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
		mLastID++;

		return mLastID;
	}

	void PhysicsManager::UnregisterEntity(unsigned long id) {
		bool found = false;
		//This is going to Loop through all of our collision layers
		for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++) {
			//Loop through all of the objects in a specific Collision Layer
			for (int a = 0; a < mCollisionLayers[i].size() && !found; a++) {
				//i == the layer we are currently looking at
				//a == the PhysicsEntity* we are currently looking at
				if (mCollisionLayers[i][a]->getId() == id) {
					mCollisionLayers[i].erase(mCollisionLayers[i].begin() + a);
					found = true;
				}
			}
		}
	}

	void PhysicsManager::Update() {
		//Iteration 1 - looking through all of our layers
		for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++) {
			//Iteration 2 - Looking through all of our layers
			//ask about the difference between the two iterations after break
			for (int a = 0; a < static_cast<unsigned int>(CollisionLayers::MaxLayers); a++) {
				if (mLayerMasks[i].test(a) && i <= a) {
					//Iteration 1 - looking through all of our objects on iterations 1's layer
					for (int b = 0; b < mCollisionLayers[i].size(); b++) {
						//iteration 2 - looking through all of our objects on iterations 2's layer
						for (int c = 0; b < mCollisionLayers[i].size(); c++) {
							//This is where the actual collision check is happening!
							if (mCollisionLayers[i][b]->CheckCollision(mCollisionLayers[a][c])) {
								//a Collision has occured
								//Our first object has hit our second object
								mCollisionLayers[i][b]->Hit(mCollisionLayers[a][c]);
								//our second object has hit our first object
								mCollisionLayers[a][c]->Hit(mCollisionLayers[i][b]);
							}
						}
					}
				}
			}
		}
	}

}