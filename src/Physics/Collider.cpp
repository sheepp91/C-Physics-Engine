#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"

#include "iostream"

using namespace Physics;

Collider::Collider(Type type) : m_type(type) {

}

Collider::~Collider() {

}

Collider::Type Collider::GetType() {
	return m_type;
}

bool Collider::Intersects(Collider * other, IntersectData *data) {
	if (GetType() == Type::SPHERE) {
		if (other->GetType() == Type::SPHERE)
			return SphereToSphere((SphereCollider*)this, (SphereCollider*)other, data);
		else if (other->GetType() == Type::AABB)
			return SphereToAabb((SphereCollider*)this, (AABBCollider*)other, data);
		//else if (other->GetType() == Type::OBB)
			//return SphereToObb(this, other);
	} else if (GetType() == Type::AABB) {
		//if (other->GetType() == Type::SPHERE) return AabbToSphere(this, other);
		//else 
		if (other->GetType() == Type::AABB) 
			return AabbToAabb((AABBCollider*)this, (AABBCollider*)other, data);
		//else if (other->GetType() == Type::OBB) return AabbToObb(this, other);
	} else if (GetType() == Type::OBB) {
		//if (other->GetType() == Type::SPHERE) return ObbToSphere(this, other);
		//else if (other->GetType() == Type::AABB) return ObbToAabb(this, other);
		//else if (other->GetType() == Type::OBB) return ObbToObb(this, other);
	}

	//Change this to VolumeToVolume or SAT collision detection strategies .... ? (Ask Aaron)
	return false;
}

bool Collider::SphereToSphere(SphereCollider *colA, SphereCollider *colB, IntersectData *data) {
	glm::vec3 vDistance = colB->GetPosition() - colA->GetPosition();
	float distance = glm::length(vDistance);
	float minDistance = colA->GetRadius() + colB->GetRadius();

	if (distance < minDistance) {
		if (data != nullptr) {
			// objA is intersecting with objB
			glm::vec3 collisionNormal = glm::normalize(vDistance);
			float overlap = minDistance - distance;
			data->collisionVec = collisionNormal * overlap;
		}
	}
	return distance < minDistance;
}


bool Collider::SphereToAabb(SphereCollider *colA, AABBCollider *colB, IntersectData *data) {
	glm::vec3 spherePos = colA->GetPosition();
	glm::vec3 minB = colB->GetPosition() - colB->GetDimensions();
	glm::vec3 maxB = colB->GetPosition() + colB->GetDimensions();

	auto check = [&](
		const double pn,
		const double bmin,
		const double bmax) -> double {
		double out = 0;

		if (pn < bmin) {
			double val = (bmin - pn);
			out += val * val;
		}

		if (pn > bmax) {
			double val = (pn - bmax);
			out += val * val;
		}

		return out;
	};

	// Squared distance
	double sq = 0.0;
	sq += check(spherePos.x, minB.x, maxB.x);
	sq += check(spherePos.y, minB.y, maxB.y);
	sq += check(spherePos.z, minB.z, maxB.z);

	bool isIntersecting = (sq <= (colA->GetRadius() * colA->GetRadius()));

	if (isIntersecting) {
		if (data != nullptr) {
			
		}
	}

	return isIntersecting;
}

bool Collider::AabbToAabb(AABBCollider *colA, AABBCollider *colB, IntersectData *data) {
	glm::vec3 minA = colA->GetPosition() - colA->GetDimensions();
	glm::vec3 maxA = colA->GetPosition() + colA->GetDimensions();
	glm::vec3 minB = colB->GetPosition() - colB->GetDimensions();
	glm::vec3 maxB = colB->GetPosition() + colB->GetDimensions();

	bool isIntersecting = (
		minA.x < maxB.x && maxA.x > minB.x &&
		minA.y < maxB.y && maxA.y > minB.y &&
		minA.z < maxB.z && maxA.z > minB.z);

	if (isIntersecting) {
		if (data != nullptr) {
			glm::vec3 min(glm::max(minA.x, minB.x), glm::max(minA.y, minB.y), glm::max(minA.z, minB.z));
			glm::vec3 max(glm::min(maxA.x, maxB.x), glm::min(maxA.y, maxB.y), glm::min(maxA.z, maxB.z));

			glm::vec3 overlap = max - min;

			data->collisionVec = glm::vec3(0, 0, 0);
			if (overlap.x < overlap.y && overlap.x < overlap.z) data->collisionVec.x = overlap.x;
			else if (overlap.y < overlap.x && overlap.y < overlap.z) data->collisionVec.y = overlap.y;
			else if (overlap.z < overlap.x && overlap.z < overlap.y) data->collisionVec.z = overlap.z;

			// correct the sign
			glm::vec3 normal = glm::normalize(data->collisionVec);
			glm::vec3 posA = colA->GetPosition() * normal;
			glm::vec3 posB = colB->GetPosition() * normal;
			glm::vec3 correction = glm::normalize(posB - posA);
			data->collisionVec *= correction;
		}
	}
	return isIntersecting;
}