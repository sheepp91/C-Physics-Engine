#include "Physics\Spring.h"
#include "Physics\IPhysicsObject.h"
#include <glm\glm.hpp>

using namespace Physics;

Spring::Spring(IPhysicsObject *objA, IPhysicsObject *objB) :
	IConstraint(objA, objB),
	m_length(1.f),
	m_friction(1.f),
	m_stiffness(100.f) {

}

Spring::Spring(IPhysicsObject *objA, IPhysicsObject *objB, float length, float friction, float stiffness) :
	IConstraint(objA, objB),
	m_length(length),
	m_friction(friction),
	m_stiffness(stiffness) {

}

Spring::~Spring() {

}

void Spring::Constrain() {
	glm::vec3 springVec = m_objB->GetPosition() - m_objA->GetPosition();
	float distance = glm::length(springVec);

	glm::vec3 force;
	if (distance > 0) {
		// F = -kV (Hooke's Law)
		// F  =      k              *                V
		force += m_stiffness * (springVec / distance) * (distance - m_length);
	}
	glm::vec3 relativeVel = m_objB->GetVelocity() - m_objA->GetVelocity();
	force += m_friction * relativeVel;

	force *= 5 + 5;

	m_objA->ApplyForce(force);
	m_objB->ApplyForce(-force);
}