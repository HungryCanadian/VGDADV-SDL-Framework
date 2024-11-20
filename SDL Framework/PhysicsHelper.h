#pragma once
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"


namespace SDLFramework {
	//circle vs circle
	inline bool CircleVsCircleCollision(CircleCollider* circle1, CircleCollider* circle2) {
		return (circle1->getPosition() - circle2->getPosition()).Magnitude() < (circle1->getRadius() + circle2->getRadius());
	}
	//circle vs box
	inline bool BoxVsCircleCollision(BoxCollider* box, CircleCollider* circle) {
		Vector2 circlePos = circle->getPosition();
		float radius = circle->getRadius();

		if (PointToLineDistance(box->getVertexPos(0), box->getVertexPos(1), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(0), box->getVertexPos(2), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(2), box->getVertexPos(3), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(3), box->getVertexPos(1), circlePos) < radius) {
			return true;
		}
		return false;
	}
	//box vs box
	inline bool BoxVsBoxCollision(BoxCollider* box1, BoxCollider* box2) {
		Vector2 projAxes[4];

		projAxes[0] = (box1->getVertexPos(0) - box1->getVertexPos(1)).Normalized();
		projAxes[1] = (box1->getVertexPos(0) - box1->getVertexPos(2)).Normalized();
		projAxes[2] = (box2->getVertexPos(0) - box2->getVertexPos(1)).Normalized();
		projAxes[3] = (box2->getVertexPos(0) - box2->getVertexPos(2)).Normalized();

		float box1Min = 0.0f, box1Max = 0.0f;
		float box2Min = 0.0f, box2Max = 0.0f;
		float proj1 = 0.0f, proj2 = 0.0f;

		for (int a = 0; a < 4; a++) {
			for (int v = 0; v < 4; v++) {
				proj1 = Dot(box1->getVertexPos(v), projAxes[a]);
				proj2 = Dot(box2->getVertexPos(v), projAxes[a]);

				if (v == 0) {
					box1Min = box1Max = proj1;
					box2Min = box2Max = proj2;
				}
				else {
					if (proj1 < box1Min)
						box1Min = proj1;
					if (proj1 > box1Max)
						box1Max = proj1;

					if (proj2 < box2Min)
						box2Min = proj2;
					if (proj2 > box2Max)
						box2Max = proj2;
				}
				float halfDist1 = (box1Max - box1Min) * 0.5f;
				float midPoint1 = box1Min + halfDist1;

				float halfDist2 = (box2Max - box2Min) * 0.5f;
				float midPoint2 = box2Min + halfDist2;

				if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2)) {
					return false;
				}
			}
			return true;
		}
	}
	inline bool ColliderVsColliderCheck(Collider* c1, Collider* c2) {
		if (c1->getType() == Collider::ColliderType::Circle && c2->getType() == Collider::ColliderType::Circle)
			return CircleVsCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Circle)
			return BoxVsCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c2->getType() == Collider::ColliderType::Box && c1->getType() == Collider::ColliderType::Circle)
			return BoxVsCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Box)
			return BoxVsBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
		else
			return false;
	}

}