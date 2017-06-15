#pragma once
#include <glm/glm.hpp>

namespace Physics {

	class IPhysicsObject;
	class SphereCollider;
	class AABBCollider;

	class Collider {
	public:
		enum class Type {
			NONE,
			SPHERE,
			AABB,
			OBB
		};

		struct IntersectData {
			glm::vec3 collisionVec;
		};

		Collider(Type type);
		virtual ~Collider();

		Type GetType();

		virtual void Transform(IPhysicsObject * object) { /*intentially left blank*/}

		bool Collider::Intersects(Collider * other, IntersectData *data = nullptr);

		static bool SphereToSphere(SphereCollider * colA, SphereCollider *colB, IntersectData *data = nullptr);
		static bool SphereToAabb(SphereCollider * colA, AABBCollider *colB, IntersectData *data = nullptr);

		static bool AabbToAabb(AABBCollider * colA, AABBCollider *colB, IntersectData *data = nullptr);

	protected:
	private:
		Type m_type;
	};
}