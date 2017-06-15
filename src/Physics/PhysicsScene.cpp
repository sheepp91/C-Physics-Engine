#include "Physics\PhysicsScene.h"
#include "Physics\IPhysicsObject.h"
#include "Physics\Collider.h"
#include "Physics\IConstraint.h"
#include <iterator>
#include <iostream>

using namespace Physics;

PhysicsScene::PhysicsScene() {

}

 PhysicsScene::~PhysicsScene() {
	 for (auto iter = m_objectGroups.begin(); iter != m_objectGroups.end(); iter++) {
		 auto & collection = iter->second;
		 for (auto iter2 = collection.begin(); iter2 != collection.end(); iter2++) {
			 delete (*iter2);
		 }
		 collection.clear();
	 }
	 m_objectGroups.clear();

	 for (auto iter = m_constraints.begin(); iter != m_constraints.end(); iter++) {
		 delete (*iter);
	 }
	 m_constraints.clear();
}

void PhysicsScene::Update(float deltaTime) {
	// Loop through all the constraints and constrain them.
	// They will be reponsible for applaying the appropriate forces to the objects
	// they're attached to.
	for (auto iter = m_constraints.begin(); iter != m_constraints.end(); iter++) {
		IConstraint *constraint = (*iter);
		constraint->Constrain();
	}

	//for (auto iter = m_objects2.begin(); iter != m_objects2.end(); iter++) {
	for (auto iter = m_objectGroups.begin(); iter != m_objectGroups.end(); iter++) {
		auto & collection = iter->second;
		for (auto iter2 = collection.begin(); iter2 != collection.end(); iter2++) {

			IPhysicsObject *obj = (*iter2);
			obj->ApplyForce(m_globalForce);
			obj->Update(deltaTime);

			//temporary collision with ground
			//-----------------------------------------

			const glm::vec3 &pos = obj->GetPosition();
			if (pos.y < 0) {
				const glm::vec3 & vel = obj->GetVelocity();
				obj->SetPosition(glm::vec3(pos.x, 0, pos.z));
				obj->SetVelocity(glm::vec3(vel.x, -vel.y, vel.z));
			}
		}
		//-----------------------------------------
	}
	m_globalForce = glm::vec3();

	DetectCollisions();
	ResolveCollisions();
}

unsigned int PhysicsScene::AttachObject(IPhysicsObject *object, int groupId) {
	if (groupId == -1) {
		groupId = GenerateGroupId();
	}
	
	std::set<IPhysicsObject *> *groupA = &m_objectGroups[groupId];
	if (groupA->find(object) == groupA->end()) {
		groupA->insert(object);
	}
	object->SetGroupIdentifier(groupId);

	return groupId;
}

void PhysicsScene::DetachObject(IPhysicsObject* object, int groupId) {
	std::set<IPhysicsObject *> *groupA = &m_objectGroups[groupId];
	if (groupA->find(object) != groupA->end()) {
		groupA->erase(object);
	}
}

void PhysicsScene::RemoveObject(IPhysicsObject* &object, int groupId) {
	std::set<IPhysicsObject *> *groupA = &m_objectGroups[groupId];
	if (groupA->find(object) != groupA->end()) {
		groupA->erase(object);
		delete object;
	}
}

const std::map<unsigned int, std::set<IPhysicsObject*> > & PhysicsScene::GetObjects() const {
	return m_objectGroups;
}

void PhysicsScene::ApplyGlobalForce(const glm::vec3 & force) {
	m_globalForce += force;
}

void PhysicsScene::DetectCollisions() {
	m_collisionPairs.clear();
	m_collisionIntersectLookup.clear();

	for (auto gIterA = m_objectGroups.begin(); gIterA != m_objectGroups.end(); gIterA++) {
		for (auto gIterB = std::next(gIterA); gIterB != m_objectGroups.end(); gIterB++) {
			std::set<IPhysicsObject *> groupA = gIterA->second;
			std::set<IPhysicsObject *> groupB = gIterB->second;

			for (auto oIterA = groupA.begin(); oIterA != groupA.end(); oIterA++) {
				IPhysicsObject *objA = (*oIterA);
				Collider *colA = objA->GetCollider();
				if (colA->GetType() == Collider::Type::NONE)
					continue;

				for (auto oIterB = groupB.begin(); oIterB != groupB.end(); oIterB++) {
					IPhysicsObject *objB = (*oIterB);
					Collider *colB = objB->GetCollider();

					if (colB->GetType() == Collider::Type::NONE)
						continue;

					CollisionInfo info;

					//TODO: check for intersections
					if (colA->Intersects(colB, &info.data)) {
						info.objA = objA;
						info.objB = objB;
						m_collisionPairs.push_back(info);
						m_collisionIntersectLookup[objA] = true;
						m_collisionIntersectLookup[objB] = true;
					}
				}
			}
		}
	}

	//for (auto iterA = m_objects2.begin(); iterA != m_objects2.end(); iterA++) {
	//	IPhysicsObject *objA = (*iterA);
	//	Collider *colA = objA->GetCollider();
	//	if (colA->GetType() == Collider::Type::NONE)
	//		continue;
	//
	//	for (auto iterB = std::next(iterA); iterB != m_objects2.end(); iterB++) {
	//		IPhysicsObject *objB = (*iterB);
	//		Collider *colB = objB->GetCollider();
	//
	//		if (colB->GetType() == Collider::Type::NONE)
	//			continue;
	//
	//		CollisionInfo info;
	//
	//		//TODO: check for intersections
	//		if (colA->Intersects(colB, &info.data)) {
	//			info.objA = objA;
	//			info.objB = objB;
	//			m_collisionPairs.push_back(info);
	//			m_collisionIntersectLookup[objA] = true;
	//			m_collisionIntersectLookup[objB] = true;
	//		}
	//	}
	//}
}

void PhysicsScene::ResolveCollisions() {
	for (auto iter = m_collisionPairs.begin(); iter != m_collisionPairs.end(); iter++) {
		IPhysicsObject *objA = (*iter).objA;
		IPhysicsObject *objB = (*iter).objB;
		Collider::IntersectData &data = (*iter).data;

		glm::vec3 collisionNormal = glm::normalize(data.collisionVec);
		glm::vec3 resolutionVec = objB->GetVelocity() - objA->GetVelocity();

		float velAlongNormal = glm::dot(resolutionVec, collisionNormal);

		float bounciness = glm::min(objA->GetBounciness(), objB->GetBounciness());

		float impulseLength = -(1.f + bounciness) * velAlongNormal;
		impulseLength /= (objA->GetInvMass()) + (objB->GetInvMass());

		glm::vec3 impulse = impulseLength * collisionNormal;

		objA->SetVelocity(objA->GetVelocity() - (objA->GetInvMass()) * impulse);
		objB->SetVelocity(objB->GetVelocity() + (objB->GetInvMass()) * impulse);

		float collisionPercentA, collisionPercentB;
		if (objA->GetMass() < objB->GetMass()) {
			collisionPercentB = objA->GetMass() / objB->GetMass();
			collisionPercentA = 1 - collisionPercentB;
		} else if (objB->GetMass() > objA->GetMass()) {
			collisionPercentA = objB->GetMass() / objA->GetMass();
			collisionPercentB = 1 - collisionPercentA;
		} else {
			collisionPercentA = 0.5f;
			collisionPercentB = 0.5f;
		}

		//glm::vec3 separationVector = data.collisionVec * 0.5f;
		objA->SetPosition(objA->GetPosition() - data.collisionVec * collisionPercentA);
		objB->SetPosition(objB->GetPosition() + data.collisionVec * collisionPercentB);
	}
}

bool PhysicsScene::IsIntersecting(IPhysicsObject *obj) {
	return m_collisionIntersectLookup[obj];
}

void PhysicsScene::AttachConstraint(IConstraint *constraint) {
	m_constraints.push_back(constraint);
}
void PhysicsScene::DetachConstraint(IConstraint *constraint) {
	auto iter = std::find(m_constraints.begin(), m_constraints.end(), constraint);
	if (iter != m_constraints.end()) {
		m_constraints.erase(iter);
	}
}

void PhysicsScene::RemoveConstraint(IConstraint *constraint) {
	auto iter = std::find(m_constraints.begin(), m_constraints.end(), constraint);
	if (iter != m_constraints.end()) {
		m_constraints.erase(iter);
	}
	delete(constraint);
}

unsigned int PhysicsScene::GenerateGroupId() {
	int id = m_nextGroupId;
	m_nextGroupId += 1;
	return id;
}