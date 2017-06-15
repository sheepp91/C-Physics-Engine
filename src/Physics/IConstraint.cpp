#include "Physics\IConstraint.h"

using namespace Physics;

IConstraint::IConstraint(IPhysicsObject *objA, IPhysicsObject *objB) : 
	m_objA(objA),
	m_objB(objB) {

}
IConstraint::~IConstraint() {
}