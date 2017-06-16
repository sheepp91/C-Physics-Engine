#include "Physics_Walkthrough_App.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include "Camera.h"
#include "Physics\IPhysicsObject.h"
#include "Physics\PhysicsScene.h"
#include "Physics\PhysicsGizmosRenderer.h"
#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\Spring.h"
#include <imgui.h>

Physics_Walkthrough_App::Physics_Walkthrough_App()
{

}

Physics_Walkthrough_App::~Physics_Walkthrough_App()
{

}

bool Physics_Walkthrough_App::startup()
{
	m_scene = nullptr;
	m_sceneRenderer = nullptr;
	srand(time(NULL));
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	aie::Gizmos::create(100000, 100000, 100000, 100000);

	// create simple camera transforms
	m_camera = new Camera();
	m_camera->SetProjection(glm::radians(45.0f), (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	m_camera->SetPosition(glm::vec3(10, 10, 10));
	m_camera->Lookat(glm::vec3(0, 0, 0));
	
	// Setup Physics Scene
	//--------------------------------------------------
	

	SetupScene4();

	return true;
}

void Physics_Walkthrough_App::shutdown()
{
	delete m_sceneRenderer;
	delete m_scene;
	delete m_camera;
	aie::Gizmos::destroy();
}

////////////////////////////////////////////////////////////////////////////

void Physics_Walkthrough_App::SetupScene1() {
	m_sceneNum = 1;

	m_scene = new Physics::PhysicsScene();
	m_sceneRenderer = new Physics::PhysicsGizmosRenderer(m_sceneNum);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
			obj->SetPosition(glm::vec3(i - 5, rand() % 10 + 1, j - 5));
			obj->SetFriction((20.0f / (rand() % 100 + 1)));
			obj->SetCollider(new Physics::SphereCollider(0.25f));

			m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				1.f
			);

			m_scene->AttachObject(obj);
		}
	}

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
			obj->SetPosition(glm::vec3(k - 10, rand() % 10 + 1, l - 10));
			obj->SetFriction((20.0f / (rand() % 100 + 1)));
			obj->SetCollider(new Physics::AABBCollider());

			m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				1.f
			);

			m_scene->AttachObject(obj);
		}
	}
}

void Physics_Walkthrough_App::SetupScene2() {
	m_sceneNum = 2;

	m_scene = new Physics::PhysicsScene();
	m_sceneRenderer = new Physics::PhysicsGizmosRenderer(m_sceneNum);

	//Cube
	obj1 = new Physics::IPhysicsObject();
	obj1->SetPosition(glm::vec3(0, 0, 0));
	obj1->SetFriction((20.0f / (rand() % 100 + 1)));
	obj1->SetCollider(new Physics::AABBCollider());
	obj1->SetMass(1);

	m_sceneRenderer->GetRenderInfo(obj1)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	//Cube
	obj2 = new Physics::IPhysicsObject();
	obj2->SetPosition(glm::vec3(6, 0, 0));
	obj2->SetFriction((20.0f / (rand() % 100 + 1)));
	obj2->SetCollider(new Physics::AABBCollider());
	obj2->SetMass(1);

	m_sceneRenderer->GetRenderInfo(obj2)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	//Sphere
	Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
	obj->SetPosition(glm::vec3(-5, 0, 0));
	obj->SetFriction((20.0f / (rand() % 100 + 1)));
	obj->SetCollider(new Physics::SphereCollider(3));

	m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	m_scene->AttachObject(obj);

	m_scene->AttachObject(obj2);
	m_scene->AttachObject(obj1);
}

void Physics_Walkthrough_App::SetupScene3() {
	m_sceneNum = 3;

	delete m_scene;
	m_scene = new Physics::PhysicsScene();
	delete m_sceneRenderer;
	m_sceneRenderer = new Physics::PhysicsGizmosRenderer(m_sceneNum);

	Physics::IPhysicsObject *obj1 = new Physics::IPhysicsObject();
	Physics::IPhysicsObject *obj2 = new Physics::IPhysicsObject();
	Physics::IPhysicsObject *obj3 = new Physics::IPhysicsObject();
	Physics::IPhysicsObject *obj4 = new Physics::IPhysicsObject();

	obj1->SetPosition(glm::vec3(-1, 0, 1));
	obj2->SetPosition(glm::vec3(1, 0, 1));
	obj3->SetPosition(glm::vec3(1, 0, 0));
	obj4->SetPosition(glm::vec3(0, 1, 0));

	obj1->SetMass(m_mass);
	obj2->SetMass(m_mass);
	obj3->SetMass(m_mass);
	obj4->SetMass(m_mass);

	obj1->SetFriction(m_sphereFriction);
	obj2->SetFriction(m_sphereFriction);
	obj3->SetFriction(m_sphereFriction);
	obj4->SetFriction(m_sphereFriction);

	obj1->SetBounciness(m_bounciness);
	obj2->SetBounciness(m_bounciness);
	obj3->SetBounciness(m_bounciness);
	obj4->SetBounciness(m_bounciness);

	obj1->SetCollider(new Physics::SphereCollider(0.25f));
	obj2->SetCollider(new Physics::SphereCollider(0.25f));
	obj3->SetCollider(new Physics::SphereCollider(0.25f));
	obj4->SetCollider(new Physics::SphereCollider(0.25f));

	m_sceneRenderer->GetRenderInfo(obj1)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);
	m_sceneRenderer->GetRenderInfo(obj2)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);
	m_sceneRenderer->GetRenderInfo(obj3)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);
	m_sceneRenderer->GetRenderInfo(obj4)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	Physics::Spring *spring1 = new Physics::Spring(obj1, obj2, m_length, m_springFriction, m_stiffness);
	Physics::Spring *spring2 = new Physics::Spring(obj1, obj3, m_length, m_springFriction, m_stiffness);
	Physics::Spring *spring3 = new Physics::Spring(obj1, obj4, m_length, m_springFriction, m_stiffness);
	Physics::Spring *spring4 = new Physics::Spring(obj2, obj3, m_length, m_springFriction, m_stiffness);
	Physics::Spring *spring5 = new Physics::Spring(obj2, obj4, m_length, m_springFriction, m_stiffness);
	Physics::Spring *spring6 = new Physics::Spring(obj3, obj4, m_length, m_springFriction, m_stiffness);

	m_scene->AttachObject(obj1);
	m_scene->AttachObject(obj2);
	m_scene->AttachObject(obj3);
	m_scene->AttachObject(obj4);

	m_scene->AttachConstraint(spring1);
	m_scene->AttachConstraint(spring2);
	m_scene->AttachConstraint(spring3);
	m_scene->AttachConstraint(spring4);
	m_scene->AttachConstraint(spring5);
	m_scene->AttachConstraint(spring6);
}

void Physics_Walkthrough_App::SetupScene4() {
	m_sceneNum = 4;

	delete m_scene;
	m_scene = new Physics::PhysicsScene();
	delete m_sceneRenderer;
	m_sceneRenderer = new Physics::PhysicsGizmosRenderer(m_sceneNum);

	//for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++) {
	//	delete (*iter);
	//}
	//m_topRow.clear();

	///////////////

	auto getObject = [&](int x, int y, int z, std::vector<Physics::IPhysicsObject *> &objects) -> Physics::IPhysicsObject * {
		if (x < 0 || x >= m_xSize) return nullptr;
		if (y < 0 || y >= m_ySize) return nullptr;
		if (z < 0 || z >= m_zSize) return nullptr;

		return objects[(z * m_ySize * m_xSize) + (y * m_xSize) + x];
	};

	auto createSpring = [&](Physics::IPhysicsObject *objA, Physics::IPhysicsObject *objB) {
		if (objA == nullptr) return;
		if (objB == nullptr) return;

		m_scene->AttachConstraint(new Physics::Spring(objA, objB, glm::length(objA->GetPosition() - objB->GetPosition()), m_springFriction, m_stiffness));
	};

	////////////////

	int groupId = m_scene->GenerateGroupId();
	std::vector<Physics::IPhysicsObject*> objects;

	for (int z = 0; z < m_zSize; z++) {
		for (int y = 0; y < m_ySize; y++) {
			for (int x = 0; x < m_xSize; x++) {
				Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
				obj->SetPosition(glm::vec3(x*m_length, y*m_length + 20, z*m_length));
				obj->SetMass(m_mass);
				obj->SetFriction(m_sphereFriction);
				obj->SetBounciness(m_bounciness);
				obj->SetCollider(new Physics::SphereCollider(0.25f));
				m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
					rand() % 255 / 255.f,
					rand() % 255 / 255.f,
					rand() % 255 / 255.f,
					1.f
				);

				m_scene->AttachObject(obj, groupId);
				objects.push_back(obj);

				if (y == m_ySize - 1) {
					m_topRow.push_back(obj);
					//obj->SetStatic(true);
				}
			}
		}
	}

	for (int z = 0; z < m_zSize; z++) {
		for (int y = 0; y < m_ySize; y++) {
			for (int x = 0; x < m_xSize; x++) {
				Physics::IPhysicsObject *obj = getObject(x, y, z, objects);
				createSpring(obj, getObject(x - 1, y, z, objects));
				createSpring(obj, getObject(x, y - 1, z, objects));
				createSpring(obj, getObject(x + 1, y + 1, z, objects));
				createSpring(obj, getObject(x - 1, y + 1, z, objects));
				createSpring(obj, getObject(x, y, z - 1, objects));
				createSpring(obj, getObject(x, y - 1, z - 1, objects));
				createSpring(obj, getObject(x, y + 1, z - 1, objects));
				createSpring(obj, getObject(x - 1, y, z - 1, objects));
				createSpring(obj, getObject(x + 1, y, z - 1, objects));
			}
		}
	}

	Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
	obj->SetPosition(glm::vec3(3, 0, 3));
	obj->SetFriction(0);
	obj->SetMass(10000);
	obj->SetBounciness(0);
	obj->SetCollider(new Physics::AABBCollider(glm::vec3(2, 2, 2)));

	m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	m_scene->AttachObject(obj);
}

void Physics_Walkthrough_App::SetupScene5() {
	m_sceneNum = 5;

	m_scene = new Physics::PhysicsScene();
	m_sceneRenderer = new Physics::PhysicsGizmosRenderer(m_sceneNum);

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 4; l++) {
			Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
			if (l % 2 == 0) {
				obj->SetPosition(glm::vec3(k-1, l * 0.3f * 2, 0));
				//obj->SetFriction((20.0f / (rand() % 100 + 1)));
				obj->SetFriction(0);
				obj->SetBounciness(0);
				obj->SetCollider(new Physics::AABBCollider(glm::vec3(0.5f, 0.3f, 1.5f)));
			} else {
				obj->SetPosition(glm::vec3(0, l * 0.3f * 2, k - 1));
				//obj->SetFriction((20.0f / (rand() % 100 + 1)));
				obj->SetFriction(0);
				obj->SetBounciness(0);
				obj->SetCollider(new Physics::AABBCollider(glm::vec3(1.5f, 0.3f, 0.5f)));
			}
			m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				1.f
			);

			m_scene->AttachObject(obj);
		}
	}
}

////////////////////////////////////////////////////////////////////////////

void Physics_Walkthrough_App::update(float deltaTime) {
	m_camera->Update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) || input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
		//shootSphere();
		shootAABB();
	}

	if (m_sceneNum == 4) {
		if (input->isKeyDown(aie::INPUT_KEY_I)) 
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(0.f, 100.f, 0.f));
		if (input->isKeyDown(aie::INPUT_KEY_K)) 
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(0.f, -100.f, 0.f));
		if (input->isKeyDown(aie::INPUT_KEY_O)) 
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(50.f, 0.f, 0.f));
		if (input->isKeyDown(aie::INPUT_KEY_U)) 
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(-50.f, 0.f, 0.f));
		if (input->isKeyDown(aie::INPUT_KEY_J))
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(0.f, 0.f, -50.f));
		if (input->isKeyDown(aie::INPUT_KEY_L))
			for (auto iter = m_topRow.begin(); iter != m_topRow.end(); iter++)
				(*iter)->ApplyForce(glm::vec3(0.f, 0.f, 50.f));

		ImGui::Begin("Cloth / Jelly Cube");
		ImGui::SliderFloat("Sphere - Mass", &m_mass, 0.1f, 100);
		ImGui::SliderFloat("Sphere - Friction", &m_sphereFriction, 0.1f, 100);
		ImGui::SliderFloat("Sphere - Bounciness", &m_bounciness, 0.1f, 100);

		ImGui::SliderFloat("Spring - Length", &m_length, 0.1f, 100);
		ImGui::SliderFloat("Spring - Friction", &m_springFriction, 0.1f, 100);
		ImGui::SliderFloat("Spring - Stiffness", &m_stiffness, 0.1f, 1000);

		ImGui::SliderInt("xSize", &m_xSize, 1, 15);
		ImGui::SliderInt("ySize", &m_ySize, 1, 15);
		ImGui::SliderInt("zSize", &m_zSize, 1, 15);
		ImGui::End();
	} else if (m_sceneNum == 2) {
		if (input->isKeyDown(aie::INPUT_KEY_I))
			obj1->ApplyForce(glm::vec3(0.f, 0.f, -4.f));
		if (input->isKeyDown(aie::INPUT_KEY_K))
			obj1->ApplyForce(glm::vec3(0.f, 0.f, 4.f));
		if (input->isKeyDown(aie::INPUT_KEY_J))
			obj1->ApplyForce(glm::vec3(-4.f, 0.f, 0.f));
		if (input->isKeyDown(aie::INPUT_KEY_L))
			obj1->ApplyForce(glm::vec3(4.f, 0.f, 0.f));
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	///////////////////////////////////

	ImGui::Begin("Scenes");
	if (ImGui::Button("Reset Scene 1")) SetupScene1();
	if (ImGui::Button("Reset Scene 2")) SetupScene2();
	if (ImGui::Button("Reset Scene 3")) SetupScene3();
	if (ImGui::Button("Reset Scene 4")) SetupScene4();
	if (ImGui::Button("Reset Scene 5")) SetupScene5();
	ImGui::End();

	///////////////////////////////////

	m_scene->ApplyGlobalForce(glm::vec3(0, -9.8, 0));
	m_scene->Update(deltaTime);
}

void Physics_Walkthrough_App::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// wipe the gizmos clean for this frame
	aie::Gizmos::clear();
	RenderGizmosGrid();


	m_sceneRenderer->Draw(m_scene);

	//aie::Gizmos::addAABB(glm::vec3(0,0,0), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1, 0, 0, 1));

	//for (int i = 0; i < m_objs.size(); i++) {
	//	aie::Gizmos::addSphere(m_objs[i]->GetPosition(), 0.25, 8, 8, glm::vec4(1, 0, 0, 1));
	//}

	aie::Gizmos::draw(m_camera->GetProjectionView());
}

void Physics_Walkthrough_App::shootSphere() {
	glm::vec3 camPos = m_camera->GetPosition();

	Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
	obj->SetPosition(m_camera->GetPosition() + m_camera->GetFront());
	obj->SetFriction((1));
	obj->SetVelocity(m_camera->GetFront() * 20);
	obj->SetCollider(new Physics::SphereCollider(0.5f));
	m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	int groupId = m_scene->GenerateGroupId();
	m_scene->AttachObject(obj, groupId);
}

void Physics_Walkthrough_App::shootAABB() {
	glm::vec3 camPos = m_camera->GetPosition();

	Physics::IPhysicsObject *obj = new Physics::IPhysicsObject();
	obj->SetPosition(m_camera->GetPosition() + m_camera->GetFront());
	obj->SetFriction((1));
	obj->SetMass((1));
	obj->SetVelocity(m_camera->GetFront() * 20);
	obj->SetCollider(new Physics::AABBCollider());
	m_sceneRenderer->GetRenderInfo(obj)->color = glm::vec4(
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		rand() % 255 / 255.f,
		1.f
	);

	m_scene->AttachObject(obj);
}

void Physics_Walkthrough_App::RenderGizmosGrid() {
	// draw a simple grid with gizmos
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	aie::Gizmos::addTransform(glm::mat4());
}