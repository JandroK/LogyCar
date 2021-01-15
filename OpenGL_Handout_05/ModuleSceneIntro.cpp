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

	

	//Musica
	//App->audio->PlayMusic("Assets/Sounds/enemy_airforce.ogg");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Big plane as ground
	{
		btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
		btDefaultMotionState* myMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

		btRigidBody* rigidBbody = new btRigidBody(rbInfo);
		rigidBbody->activate();
		App->physics->world->addRigidBody(rigidBbody);
		
	}


	float height = 0.1f;
	ground.SetPos(0, -0.1f, 0);
	ground.size = { 400,height ,400 };
	ground.color.Set(0.7f,1.9f,0.5f);

	//Limit1.color = Red;
	lisseners.add(App->physics->AddBody(ground, 0));
	lisseners.getLast()->data->collision_listeners.add(this);
	lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

	Looping({-106,10,+54});
	Ramp();

	// Limits
	{
		float height = 10;
		Limit1.SetPos(0, height/2.0f, 200);
		Limit1.size = { 400,height+1,2 };
		//Limit1.color = Red;
		App->physics->AddBody(Limit1, 0);

		Limit2.SetPos(200, height / 2.0f, 0);
		Limit2.size = { 1,height+1,400 };
		Limit2.color = Red;
		App->physics->AddBody(Limit2, 0);

		Limit3.SetPos(-200, height / 2.0f, 0);
		Limit3.size = { 1,height+1,400 };
		Limit3.color = Red;
		App->physics->AddBody(Limit3, 0);

		Limit4.SetPos(0, height / 2.0f, -200);
		Limit4.size = { 400,height+1,1 };
		App->physics->AddBody(Limit4, 0);

	}

	// Platforms
	{
		wall1.SetPos(-90, 1.0f, -86);
		wall1.size = { 10,1,15 };
		wall1.color = Red;
		wall1.SetRotation(23, { 0,0,1 });
		// TODO: estas 3 linies tienen que estar en todos con todos los AddBody de sceneIntro
		// para que el coche sepa que chocando con el suelo 
		lisseners.add(App->physics->AddBody(wall1, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall2.SetPos(-50, 4, -85);
		wall2.size = { 30,2,20 };
		wall2.color = White;
		lisseners.add(App->physics->AddBody(wall2, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
		// segunda rampa
		wall12.SetPos(-39, 5.0f, -86);
		wall12.size = { 8,1,15 };
		wall12.color = White;
		wall12.SetRotation(20, { 0,0,1 });

		lisseners.add(App->physics->AddBody(wall12, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
		// Cilindro
		CylinderWalls({0,0,0});

		/*cylinder1.SetPos(-10, 6.5f, -90);
		cylinder1.radius = 5;
		cylinder1.height = 50;
		cylinder1.color = White;
		cylinder1.SetRotation(15, { 0,0,1 });
		App->physics->AddBody(cylinder1, 0);*/

		// balanza
		wall3.SetPos(-3, 6.5f, -90);
		wall3.size = { 2,39,10 };
		wall3.color = White;
		wall3.SetRotation(90-15, { 0,0,-1 });
		lisseners.add(App->physics->AddBody(wall3, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall4.SetPos(40, 10, -90);
		wall4.size = { 20,2,15 };
		wall4.color = White;
		lisseners.add(App->physics->AddBody(wall4, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall5.SetPos(50, 12.5f, -90);
		wall5.size = { 2,5,15 };
		wall5.color = White;
		lisseners.add(App->physics->AddBody(wall5, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
		// Plancha
		wall6.SetPos(40, 20, -50);
		wall6.size = { 3.25,0.5,60 };
		wall6.color = White;
		wall6.SetRotation(20, { -1,0,0 });
		lisseners.add(App->physics->AddBody(wall6, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
		// rampa pequeña salto
		wall7.SetPos(40, 11, -84);
		wall7.size = { 5,1.5,5};
		wall7.color = White;
		wall7.SetRotation(20, { -1,0,0 });
		lisseners.add(App->physics->AddBody(wall7, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall8.SetPos(40, 18, 15);
		wall8.size = { 20,4,20};
		wall8.color = White;
		lisseners.add(App->physics->AddBody(wall8, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall9.SetPos(30, 20, 15);
		wall9.size = { 20,2,20};
		wall9.color = White;
		wall9.SetRotation(20, { 0,0,-1 });
		App->physics->AddBody(wall9, 0);

		rotationPlt1.SetPos(-10, 19, 15);
		rotationPlt1.size = { 20,2,20 };
		rotationPlt1.color = White;
		lisseners.add(App->physics->AddBody(rotationPlt1, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		rotationPlt2.SetPos(-30, 13, -10);
		rotationPlt2.size = { 20,2,20 };
		rotationPlt2.color = White;
		lisseners.add(App->physics->AddBody(rotationPlt2, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall10.SetPos(-70, 10, -10);
		wall10.size = { 60,2,7 };
		wall10.color.Set(0.5f,0.5f,1.0f);
		lisseners.add(App->physics->AddBody(wall10, 0));
		lisseners.getLast()->data->body->setFriction(0.01f);
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		wall11.SetPos(-110, 10, -10);
		wall11.size = { 20,2,20 };
		wall11.color = White;
		lisseners.add(App->physics->AddBody(wall11, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
	}

	// Sensors
	{
		cubeSensor.SetPos(-110, 11.1f, -10);
		cubeSensor.size = { 19.5f,0.45f,19.5f };
		cubeSensor.color = White;
		bodySensor =App->physics->AddBody(cubeSensor, 0);
		bodySensor->SetAsSensor(true);
		bodySensor->collision_listeners.add(this);
		bodySensor->body->setUserPointer(bodySensor);

	}

	{
		p2List_item<tdata>* lissener = lisseners.getFirst();
		for (int i = 0; i < lisseners.count(); i++)
		{
			lissener
		}
	}

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
	if (App->input->GetKey(SDL_SCANCODE_F1)==KEY_DOWN)App->SetDebugMode();

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	ground.Render();

	// Limits
	{
		Limit1.Render();
		Limit2.Render();
		Limit3.Render();
		Limit4.Render();
	}

	// Platforms
	{
		wall1.Render();
		wall2.Render();
		wall3.Render();
		wall4.Render();
		wall5.Render();
		wall6.Render();
		wall7.Render();
		wall8.Render();
		wall9.Render();
		rotationPlt1.Render();
		rotationPlt2.Render();

		wall10.Render();
		wall11.Render();
		wall12.Render();

		cubeSensor.Render();
		
	
		for (p2List_item<Cube*>* cube = looping.getFirst(); cube; cube= cube->next)
		{
			cube->data->Render();
		}

	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == bodySensor || body2 == bodySensor)&& !win)
	{
		win = true;
		btVector3 vec = bodySensor->body->getCenterOfMassPosition();
		vec3 sizeCube= cubeSensor.size ;
		cubeSensor.SetPos(-110, 11.1f, -10);
		cubeSensor.color = Green;
		cubeSensor.size.y = 0.10f;
		bodySensor->SetPos(vec.getX(),vec.getY()-1,vec.getZ());
	}
	if ( lisseners.find(body1) >= 0 || lisseners.find(body2) >= 0)
	{
		LOG("En el suelo");

	}

	int i;
}

void ModuleSceneIntro::Looping(vec3 position)
{
	#define PI 3.14159265359
	Cube* cube;
	//int numCubes = 118;
	int numCubes = 236;
	float alpha =0;
//	float radio = 5;
	float radio = 2.5f;
	float rad = 0;
	float offset = 0;
	float posX = position.x;
	float posY = position.y;
	float posZ = position.z;
	vec3 size = { 20,0.5,radio };
	vec3 axis = { size.x,size.z,size.z};


	for (int i = 0; i < numCubes; i++)
	{
		
		alpha += (360*2) / numCubes;
		
		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ += radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		cube->SetPos(posX+offset, posY, -posZ);
		cube->size = size;
		cube->color = White;

		cube->SetRotation(alpha+1.5f, { 1,0,0 });
		//cube->transform.rotate(alpha + 1.5f, { 1,0,0 });

		looping.add(cube);	
		App->physics->AddBody(*cube,0);

	
		offset +=(size.x*2.7 )/numCubes ;
	}

}

void ModuleSceneIntro::CylinderWalls(vec3 position)
{
#define PI 3.14159265358979323846
	Cube* cube;
	float numCubes = 16;
	float alpha = 0;
	float offset = 100;
	float radio = 5.00;
	float rad = 0;
	float posX = position.x;
	float posY = position.y;
	float posZ = position.z;
	vec3 size = { 100.0f,0.25f,radio  };
	vec3 axis = { size.x,size.z,size.z };

	for (int i = 0; i < numCubes; i++)
	{

		alpha += 360.0f  / numCubes;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ += radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		cube->SetPos(posX, posY,-posZ);
		cube->size = size;
		cube->color = White;

		cube->SetRotation(alpha+11.5f , { 1,0,0 });
		//cube->transform.rotate(alpha+10.5f , { 1,0,0 });
	//	cube->transform.rotate( 10.5f, { 0,1,0 });


		looping.add(cube);
		App->physics->AddBody(*cube, 0);


		//posZ += size.z / numCubes;
	}

}



void ModuleSceneIntro::Ramp()
{
#define PI 3.14159265358979323846
	Cube* cube;
	float numCubes = 8;
	float alpha = 0;
	float offset = 100;
	float radio = 5.00;
	float rad = 0;
	float posZ = -100;
	float posY = 0;
	vec3 size = {  100.0f,0.50f,radio };
	vec3 axis = { size.x,size.z,size.z };


	for (int i = 0; i < numCubes; i++)
	{

		alpha += 90.0f / numCubes;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ += radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		cube->SetPos(offset, posY, -posZ);
		cube->size = size;
		cube->color = White;

		cube->SetRotation(alpha + 6.0f, { 1,0,0 });

		looping.add(cube);
		App->physics->AddBody(*cube, 0);


		//posZ += size.z / numCubes;
	}

}
