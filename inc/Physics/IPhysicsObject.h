#pragma once

#include <glm/glm.hpp>

namespace Physics {
	class Collider;

	class IPhysicsObject {
	public:
		IPhysicsObject();
		virtual ~IPhysicsObject();

		void Update(float deltaTime);

		void ApplyForce(const glm::vec3 force);

		//Getters and setters
		//----------------------------------------------------------------------------------------------
		inline const glm::vec3 & GetPosition() const { return m_position; }
		inline const glm::vec3 & GetVelocity() const { return m_velocity; }
		inline const glm::vec3 & GetAcceleration() const { return m_acceleration; }
		inline float GetMass() const { return m_mass; }
		inline float GetInvMass() const { return 1.0f / m_mass; }
		inline float GetFriction() const { return m_friction; }
		inline float GetBounciness() const { return m_bounciness; }
		inline int GetGroupIdentifier() const { return m_groupIdentifier; }
		inline bool GetStatic() const { return m_static; }

		void SetPosition(const glm::vec3 & pos);
		inline void SetVelocity(const glm::vec3 & vel) { m_velocity = vel; }
		inline void SetAcceleration(const glm::vec3 & accel) { m_acceleration = accel; }
		inline void SetMass(float mass) { m_mass = mass; }
		inline void SetFriction(float fric) { m_friction = fric; }
		inline void SetBounciness(float bounce) { m_bounciness = bounce; }
		inline void SetGroupIdentifier(int groupId) { m_groupIdentifier = groupId; }
		inline void SetStatic(bool staticVar) { m_static = staticVar; }

		void SetCollider(Collider *collider);
		Collider *GetCollider();

		//----------------------------------------------------------------------------------------------

	protected:
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;

		float m_mass;
		float m_friction;
		float m_bounciness;
		bool m_static;

		Collider *m_collider;

		int m_groupIdentifier;

	private:

	};
}