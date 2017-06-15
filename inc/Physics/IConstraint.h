#pragma once
namespace Physics {
	class IPhysicsObject;

	class IConstraint {
	public:

		IConstraint(IPhysicsObject *objA, IPhysicsObject *objB);
		virtual ~IConstraint();

		virtual void Constrain() = 0;

		IPhysicsObject *GetObjectA() { return m_objA; }
		IPhysicsObject *GetObjectB() { return m_objB; }
	protected:
		IPhysicsObject *m_objA;
		IPhysicsObject *m_objB;
	private:
	};
}