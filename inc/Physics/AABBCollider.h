#pragma once
#include "Physics\Collider.h"
#include <glm\glm.hpp>

namespace Physics {
	class IPhysicsObject;

	class AABBCollider : public Collider {
	public:
		AABBCollider();
		AABBCollider(glm::vec3 dimensions);
		virtual ~AABBCollider();
	
		virtual void Transform(IPhysicsObject * object);

		inline const glm::vec3 GetPosition() const { return m_position; }
		inline const glm::vec3 GetDimensions() const { return m_dimensions; }

		inline void SetPosition(const glm::vec3 & pos) { m_position = pos; }
		inline void SetDimensions(const glm::vec3 dim) { m_dimensions = dim; }
	protected:
		glm::vec3 m_position;
		glm::vec3 m_dimensions;
	private:
	};
}