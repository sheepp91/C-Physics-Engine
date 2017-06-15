#include "Physics\AABBCollider.h"
#include "Physics\IPhysicsObject.h"

using namespace Physics;

AABBCollider::AABBCollider() : Collider(Type::AABB), m_dimensions(0.5f, 0.5f, 0.5f) {

}

AABBCollider::AABBCollider(glm::vec3 dimensions) : Collider(Type::AABB), m_dimensions(dimensions) {

}

AABBCollider::~AABBCollider() {

}

void AABBCollider::Transform(IPhysicsObject * object) {
	m_position = object->GetPosition();
}