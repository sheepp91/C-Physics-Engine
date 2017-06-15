#pragma once
#include "Physics\Collider.h"
#include <glm\glm.hpp>

namespace Physics {
	class SphereCollider : public Collider {
	public:
		SphereCollider();
		SphereCollider(float radius);
		virtual ~SphereCollider();

		virtual void Transform(IPhysicsObject * object);

		inline const glm::vec3 GetPosition() const { return m_position; }
		inline float GetRadius() const { return m_radius; }

		inline void SetPosition(const glm::vec3 & pos) { m_position = pos; }
		inline void SetRadius(const float rad) { m_radius = rad; }
	protected:
		glm::vec3 m_position;
		float m_radius;

	private:
	};
}