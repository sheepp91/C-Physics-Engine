#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <map>

#include "Collider.h"

namespace Physics {
	class IPhysicsObject;
	class IConstraint;

	class PhysicsScene {
	public:
		struct CollisionInfo {
			IPhysicsObject *objA;
			IPhysicsObject *objB;
			Collider::IntersectData data;
		};

	public:
		PhysicsScene();
		virtual ~PhysicsScene();

		void Update(float deltaTime);

		// The scene assumes ownership of the object
		// and will take care of destroying memory
		unsigned int AttachObject(IPhysicsObject *object, int groupId = -1);

		// The scene returns ownership to the caller
		void DetachObject(IPhysicsObject* object, int groupId);

		// The scene will will delete the object
		// and nullify the provided pointer
		void RemoveObject(IPhysicsObject* &object, int groupId);

		//const std::vector<IPhysicsObject*> & GetObjects() const;
		const std::map<unsigned int, std::set<IPhysicsObject*> > & GetObjects() const;

		void ApplyGlobalForce(const glm::vec3 & force);

		bool IsIntersecting(IPhysicsObject *obj);

		void AttachConstraint(IConstraint *constraint);
		void DetachConstraint(IConstraint *constraint);
		void RemoveConstraint(IConstraint *constraint);

		const std::vector<IConstraint*> & GetConstraints() const { return m_constraints; }

		unsigned int GenerateGroupId();

	protected:
		void DetectCollisions();
		void ResolveCollisions();

	protected:
		// Object Groups
		std::map<unsigned int, std::set<IPhysicsObject*> > m_objectGroups;
		unsigned int m_nextGroupId = 0;

		//std::set<IPhysicsObject*> m_objects2;
		//std::vector<IPhysicsObject*> m_objects;
		std::vector<CollisionInfo> m_collisionPairs;
		std::map<IPhysicsObject *, bool> m_collisionIntersectLookup;

		glm::vec3 m_globalForce;

		std::vector<IConstraint*> m_constraints;
	private:
	};
}