#pragma once

#include "IConstraint.h"

namespace Physics {

	class Spring : public IConstraint {
	public:
		Spring(IPhysicsObject *objA, IPhysicsObject *objB);
		Spring(IPhysicsObject *objA, IPhysicsObject *objB, float length, float friction, float stiffness);
		virtual ~Spring();

		virtual void Constrain();

		inline float GetLength() const { return m_length; }
		inline float GetFriction() const { return m_friction; }
		inline float GetStiffness() const { return m_stiffness; }

		inline void SetLength(float length) { m_length = length; }
		inline void SetFriction(float friction) { m_friction = friction; }
		inline void SetStiffness(float stiffness) { m_stiffness = stiffness; }
	protected:
		float m_length;
		float m_friction;
		float m_stiffness;
	private:
	};
}