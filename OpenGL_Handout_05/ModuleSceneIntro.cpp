#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define PI 3.14159265359
#define DEG_TO_RAD (PI / 180)

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
		// Done
		{
			wall1.SetPos(-90, 1.0f, -86);
			wall1.size = { 10,1,15 };
			wall1.color = Red;
			wall1.SetRotation(23, { 0,0,1 });
			lisseners.add(App->physics->AddBody(wall1, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			wall2.SetPos(-55.5895, 4.162, -86);
			wall2.size = { 26,1,20 };
			wall2.color = White;
			lisseners.add(App->physics->AddBody(wall2, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			// segunda rampa
			wall12.SetPos(-39, 5.5f, -86.0f);
			wall12.size = { 8,1,20 };
			wall12.color = White;
			wall12.SetRotation(20, { 0,0,1 });
			lisseners.add(App->physics->AddBody(wall12, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			// Cilindro
			CylinderWalls({ 14.5, 21, -85.5f });

			// plataforma con pared
			{
				angle = -20;
				wall4.size = { 20,2,20 };
				wall4.SetPos(40, 14, -81);
				wall4.SetRotation(angle, { 0,1,0 });
				wall4.color = White;
				lisseners.add(App->physics->AddBody(wall4, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
				// pared de la plataforma 
				wall5.size = { wall4.size.y,10,wall4.size.z };
				wall5.SetPos(wall4.GetPos().x + 9 * cos(-angle * PI / 180), wall4.GetPos().y + (wall5.size.y / 2), wall4.GetPos().z + 9 * sin(-angle * PI / 180));
				wall5.SetRotation(angle, { 0,1,0 });
				wall5.color = White;
				lisseners.add(App->physics->AddBody(wall5, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
						angle =-20 ;
			}
			radi = 2.5f;

			// Plancha
			wall6.size = { 1.3,0.5,20 };
			wall6.SetPos(45.7, (wall4.GetPos().y + ((wall4.size.y/2) - (wall6.size.y ))), -99.1);
			wall6.color = White;

			wall6.SetRotation(angle, { 0,1,0 });
			lisseners.add(App->physics->AddBody(wall6, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			wall7.size = { 1.3,0.5,20 };
			wall7.SetPos(wall6.GetPos().x + radi * cos(-angle * DEG_TO_RAD), wall6.GetPos().y, wall6.GetPos().z + +radi * sin(-angle * DEG_TO_RAD));
			wall7.color = White;

			wall7.SetRotation(angle, { 0,1,0 });
			lisseners.add(App->physics->AddBody(wall7, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);


			angle = -20;
			wall13.size = { 5,1,5 };
			wall13.SetPos(50.8, 14.5, -109.5);
			wall13.SetRotation(angle, { 0,1,0 });
			wall13.color = White;
			lisseners.add(App->physics->AddBody(wall13, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);


			angle = 0;
			rotationPlt1.size = { 5,1,5 };
			rotationPlt1.SetPos(51.8f, 14.5, -110.2);
			rotationPlt1.SetRotation(angle, { 0,1,0 });
			rotationPlt1.color = White;
			lisseners.add(App->physics->AddBody(rotationPlt1, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			angle = -90;
			radi = 2.5f;
			// Plancha
			//wall8.SetPos((wall6.GetPos().x- wall6.size.x) + radi * cos(-angle * DEG_TO_RAD), wall6.GetPos().y, (wall6.GetPos().z- wall6.size.z) + radi * sin(-angle * DEG_TO_RAD));
			wall8.size = { 1.3,0.5,20 };
			wall8.SetPos(63, wall6.GetPos().y, -111.50);
			wall8.color = White;

			wall8.SetRotation(angle, { 0,1,0 });
			lisseners.add(App->physics->AddBody(wall8, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			// rampa peque�a salto
			wall9.size = { 1.3,0.5,20 };
			wall9.SetPos(wall8.GetPos().x + radi * cos(-angle * DEG_TO_RAD), wall8.GetPos().y, wall8.GetPos().z + radi * sin(-angle * DEG_TO_RAD));
			wall9.color = White;

			wall9.SetRotation(angle, { 0,1,0 });
			lisseners.add(App->physics->AddBody(wall9, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			rotationPlt2.SetPos(71.0f, 14.5, -98.0);
			rotationPlt2.size = { 10,1,30 };
			rotationPlt2.color = White;
			lisseners.add(App->physics->AddBody(rotationPlt2, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		}
		
		// Haciendo
		{
		angle = 45;
		rotationPlt3.SetPos(74.0f, 14.5, -82.2);
		rotationPlt3.size = { 10,1,12.5 };
		rotationPlt3.SetRotation(angle, { 0,1,0 });
		rotationPlt3.color = White;
		lisseners.add(App->physics->AddBody(rotationPlt3, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		angle = 90;
		rotationPlt4.SetPos(80.9f, 14.5, -79.25);
		rotationPlt4.size = { 10,1,12 };
		rotationPlt4.SetRotation(angle, { 0,1,0 });
		rotationPlt4.color = White;
		lisseners.add(App->physics->AddBody(rotationPlt4, 0));
		lisseners.getLast()->data->collision_listeners.add(this); 
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		angle = -45;
		rotationPlt5.SetPos(87.9f, 14.5, -82.2);
		rotationPlt5.size = { 10,1,12.5 };
		rotationPlt5.SetRotation(angle, { 0,1,0 });
		rotationPlt5.color = White;
		lisseners.add(App->physics->AddBody(rotationPlt5, 0));
		lisseners.getLast()->data->collision_listeners.add(this); 
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);


		Looping({ 18.0f, 14.5, 50.0 });

		}


		wall10.SetPos(-70, 10, -10);
		wall10.size = { 60,2,7 };
		wall10.color.Set(0.5f,0.5f,1.0f);
		lisseners.add(App->physics->AddBody(wall10, 0));
		lisseners.getLast()->data->body->setFriction(0.01f);
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

		
	}

	// Sensors
	{
		wall11.SetPos(-110, 10, -10);
		wall11.size = { 20,2,20 };
		wall11.color = White;
		lisseners.add(App->physics->AddBody(wall11, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
		lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
		cubeSensor.SetPos(-110, 11.1f, -10);
		cubeSensor.size = { 19.5f,0.45f,19.5f };
		cubeSensor.color = White;
		bodySensor =App->physics->AddBody(cubeSensor, 0);
		bodySensor->SetAsSensor(true);
		bodySensor->collision_listeners.add(this);
		bodySensor->body->setUserPointer(bodySensor);

	}

	{
		/*p2List_item<tdata>* lissener = lisseners.getFirst();
		for (int i = 0; i < lisseners.count(); i++)
		{
			lissener
		}*/
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
		rotationPlt3.Render();
		rotationPlt4.Render();
		rotationPlt5.Render();

		wall10.Render();
		wall11.Render();
		wall12.Render();
		wall13.Render();

		cubeSensor.Render();
		
	
		for (p2List_item<Cube*>* cube = looping.getFirst(); cube; cube= cube->next)
		{
			cube->data->Render();
		}
		for (p2List_item<Cube*>* cube = cilinderWall.getFirst(); cube; cube= cube->next)
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
	if ( (lisseners.find(body1) >= 0 || lisseners.find(body2) >= 0))
	{
		LOG("En el suelo");

	}

	int i;
}

void ModuleSceneIntro::Looping(vec3 position)
{
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
	float posZ = -position.z;
	vec3 size = { 20,1.25,radio };
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
		cube->color.Set(40 / posX+1.65, 40 / posY ,40 / posZ );

		cube->SetRotation(alpha+1.5f, { 1,0,0 });
		//cube->transform.rotate(alpha + 1.5f, { 1,0,0 });

		looping.add(cube);	
		lisseners.add(App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);
	
		offset +=(size.x*2.7 )/numCubes ;
	}

}

void ModuleSceneIntro::CylinderWalls(vec3 position)
{
#define PI 3.14159265358979323846
	Cube* cube;
	float numCubes = 84;
	float alpha = 0;
	float offset = 0;
	float radio = 2.5f;
	float rad = 0;
	float posX = position.x;
	float posY = position.y+radio * cos(rad);
	float posZ = -position.z+ radio * cos(rad);
	vec3 size = { 5.0f,0.75f,radio  };
	vec3 axis = { size.x,size.z,size.z };

	for (int i = 0; i < numCubes; i++)
	{

		alpha -= (360.0f*4)  / numCubes;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posY += radio * sin(rad);
		posZ += radio * cos(rad);

		cube = new Cube();
		cube->SetPos(posX+offset, posY,-posZ);
		cube->size = size;
		cube->color = White;
		cube->SetRotation(alpha-8.5 , { 1,0,0 });
		cilinderWall.add(cube);
		lisseners.add(App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);

		cube = new Cube();
		cube->SetPos(posX+ size.x +offset, posY,-posZ);
		cube->size = size;
		cube->color = Red;
		cube->SetRotation(alpha-8.5 , { 1,0,0 });
		cilinderWall.add(cube);
		lisseners.add(App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);

		offset -= size.x*8 / numCubes;
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
		lisseners.add( App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);



		//posZ += size.z / numCubes;
	}

}
