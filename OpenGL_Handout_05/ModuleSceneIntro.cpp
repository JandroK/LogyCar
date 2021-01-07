#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Big plane as ground
	{
		btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		btDefaultMotionState* myMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

		btRigidBody* body = new btRigidBody(rbInfo);
		App->physics->world->addRigidBody(body);
		
	}
	
	wall1.SetPos(-10,2,10);
	wall1.size = {4,3,60};
	wall1.color = Red;
	
	App->physics->AddBody(wall1,0);

	wall2.SetPos(10, 2, 10);
	wall2.size = { 4,3,80 };
	wall2.color = Red;

	App->physics->AddBody(wall2, 0);

	wall3.SetPos(-28, 2, 50);
	wall3.size = { 80,3,4 };
	wall3.color = Red;

	App->physics->AddBody(wall3, 0);

	wall4.SetPos(-40, 2, 40);
	wall4.size = { 80,3,4 };
	wall4.color = Red;

	App->physics->AddBody(wall4, 0);
	

	wall5.SetPos(-60, 2, 10);
	wall5.size = { 4,3,60 };
	wall5.color = Red;

	App->physics->AddBody(wall5, 0);

	wall6.SetPos(-80, 2, 10);
	wall6.SetRotation(30, { -80, 2, 10 });
	wall6.size = { 4,3,80 };
	wall6.color = Red;

	App->physics->AddBody(wall6, 0);

	//wall7.SetPos(-28, 2, 50);
	//wall7.size = { 60,3,4 };
	//wall7.color = Red;

	//App->physics->AddBody(wall7, 0);

	//wall8.SetPos(-40, 2, 40);
	//wall8.size = { 60,3,4 };
	//wall8.color = Red;

	//App->physics->AddBody(wall8, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	wall1.Render();
	wall2.Render();
	wall3.Render();
	wall4.Render();
	wall5.Render();
	wall6.Render();
	wall7.Render();
	wall8.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

