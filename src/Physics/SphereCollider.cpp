#include "Physics\SphereCollider.h"
#include "Physics\IPhysicsObject.h"

using namespace Physics;

SphereCollider::SphereCollider() : Collider(Type::SPHERE), m_radius(1.f) {

}

SphereCollider::SphereCollider(float radius) : Collider(Type::SPHERE), m_radius(radius) {

}

SphereCollider::~SphereCollider() {

}

void SphereCollider::Transform(IPhysicsObject * object) {
	m_position = object->GetPosition();
}