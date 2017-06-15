#include "Physics\IPhysicsObject.h"
#include "Physics\Collider.h"
using namespace Physics;

IPhysicsObject::IPhysicsObject() : m_mass(1.0f), m_friction(2.0f), m_bounciness(1.0f), m_collider(nullptr), m_static(false) {

}

IPhysicsObject::~IPhysicsObject() {
	delete m_collider;
}

void IPhysicsObject::Update(float deltaTime) {
	if (!m_static) {
		ApplyForce(-m_velocity * m_friction);

		m_velocity += m_acceleration * deltaTime;
		m_position += m_velocity * deltaTime;
		m_acceleration = glm::vec3();

		GetCollider()->Transform(this);
	}
}

void IPhysicsObject::ApplyForce(const glm::vec3 force) {
	m_acceleration += force / m_mass;
}

void IPhysicsObject::SetCollider(Collider *collider) {
	delete m_collider;
	m_collider = collider;
}

Collider *IPhysicsObject::GetCollider() {
	if (m_collider == nullptr) {
		static Collider nullCollider(Collider::Type::NONE);
		return &nullCollider;
	}
	return m_collider;
}

void IPhysicsObject::SetPosition(const glm::vec3 & pos) {
	m_position = pos;
	GetCollider()->Transform(this);
}