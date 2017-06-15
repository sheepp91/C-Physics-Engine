#include "Physics\PhysicsGizmosRenderer.h"
#include "Physics\IPhysicsObject.h"
#include "Physics\PhysicsScene.h"
#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\IConstraint.h"
#include <iostream>

#include <Gizmos.h>

using namespace Physics;

PhysicsGizmosRenderer::PhysicsGizmosRenderer() : m_sceneNum(1) {

}

PhysicsGizmosRenderer::PhysicsGizmosRenderer(int sceneNum) : m_sceneNum(sceneNum) {

}

PhysicsGizmosRenderer::~PhysicsGizmosRenderer() {

}

void PhysicsGizmosRenderer::Draw(PhysicsScene *scene) {
	auto & objects = scene->GetObjects();

	for (auto gIter = objects.begin(); gIter != objects.end(); gIter++) {
		auto & group = gIter->second;

		for (auto oIter = group.begin(); oIter != group.end(); oIter++) {
			IPhysicsObject *obj = (*oIter);
			Collider *collider = obj->GetCollider();

			bool isIntersecting = scene->IsIntersecting(obj);

			//glm::vec4 &color = isIntersecting ? glm::vec4(1, 0, 0, 1) : GetRenderInfo(*oIter)->color;
			glm::vec4 &color = GetRenderInfo(*oIter)->color;

			if (collider->GetType() == Collider::Type::SPHERE) {
				SphereCollider *c = (SphereCollider *)collider;
				if (m_sceneNum != 4 && m_sceneNum != 3) {
					aie::Gizmos::addSphere(c->GetPosition(), c->GetRadius(), 8, 8, color);
				}
			} else if (collider->GetType() == Collider::Type::AABB) {
				AABBCollider *c = (AABBCollider *)collider;
				aie::Gizmos::addAABBFilled(c->GetPosition(), c->GetDimensions(), color);
			} else if (collider->GetType() == Collider::Type::OBB) {
				//ToDO: render OBB
			} else if (collider->GetType() == Collider::Type::NONE) {
				//ToDO: render Physics object or nothing
				//aie::Gizmos::addTransform()
				aie::Gizmos::addSphere(obj->GetPosition(), 0.1f, 8, 8, color);
			}
		}
	}

	std::vector<IConstraint*> constraints = scene->GetConstraints();
	for (auto iter = constraints.begin(); iter != constraints.end(); iter++) {
		IPhysicsObject *objA = (*iter)->GetObjectA();
		IPhysicsObject *objB = (*iter)->GetObjectB();

		aie::Gizmos::addLine(objA->GetPosition(), objB->GetPosition(), glm::vec4(1, 0, 0, 1));
	}
}

PhysicsGizmosRenderer::RenderInfo *PhysicsGizmosRenderer::GetRenderInfo(IPhysicsObject *object) {
	return &m_renderInfo[object];
}