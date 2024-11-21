#pragma once
#include "Collider.h"
#include <vector>

namespace SDLFramework {
	//base class for any object we want to have colliders
	class PhysicsEntity : public GameEntity {
	public:
		PhysicsEntity();
		virtual ~PhysicsEntity();

		unsigned long getId();

		bool CheckCollision(PhysicsEntity* other);

		virtual void Hit(PhysicsEntity* other) { std::cout << "A Collision has Happened!\n"; }

		virtual void Render() override;

		//TODO: Temporarily here. need access for testing.
		void AddCollider(Collider* collider, Vector2 localPos = Vec2_Zero);
		unsigned long mId;

	protected:
		

		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;
		
		virtual bool IgnoreCollisions();

		//TODO: Uncomment once permission stuff is sorted.
		//void AddCollider(Collider* collider, Vector2 localPos = Vec2_Zero);
		//unsigned long mId;
	};

}