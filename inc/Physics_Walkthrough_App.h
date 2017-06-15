#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include <vector>

class Camera;

namespace Physics {
	class IPhysicsObject;
	class PhysicsScene;
	class PhysicsGizmosRenderer;
}

class Physics_Walkthrough_App : public aie::Application {
public:

	Physics_Walkthrough_App();
	virtual ~Physics_Walkthrough_App();

	virtual bool startup();
	virtual void shutdown();

	void InitialiseObjects();

	virtual void update(float deltaTime);
	virtual void draw();

	void shootSphere();
	void shootAABB();

	void RenderGizmosGrid();

	void SetupScene1();
	void SetupScene2();
	void SetupScene3();
	void SetupScene4();
	void SetupScene5();

protected:
	Physics::PhysicsScene *m_scene;
	Physics::PhysicsGizmosRenderer *m_sceneRenderer;

	std::vector<Physics::IPhysicsObject*> m_topRow;

	// Scene 2
	Physics::IPhysicsObject *obj1;
	Physics::IPhysicsObject *obj2;
	//

	// Sphere vals
	float m_mass = 1.f;
	float m_sphereFriction = 2.f;
	float m_bounciness = 1.f;

	// Spring Vals
	float m_length = 0.75f;
	float m_springFriction = 0.1f;
	float m_stiffness = 100.f;

	// Cloth collider nums
	int m_xSize = 10;
	int m_ySize = 1;
	int m_zSize = 10;

	// camera transforms
	Camera *m_camera = nullptr;

	int m_sceneNum;
};