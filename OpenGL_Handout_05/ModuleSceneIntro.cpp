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

			// 
			wall9.size = { 1.3,0.5,20 };
			wall9.SetPos(wall8.GetPos().x + radi * cos(-angle * DEG_TO_RAD), wall8.GetPos().y, wall8.GetPos().z + radi * sin(-angle * DEG_TO_RAD));
			wall9.color = White;

			wall9.SetRotation(angle, { 0,1,0 });
			lisseners.add(App->physics->AddBody(wall9, 0));
			lisseners.getLast()->data->collision_listeners.add(this);
			lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

			//curva anti horaria
			{
				rotationPlt2.SetPos(71.07f, 14.5, -98.0);
				rotationPlt2.size = { 10,1,30 };
				rotationPlt2.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt2, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

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


				rotationPlt6.SetPos(90.8f, 14.5, -98.0);
				rotationPlt6.size = { 10,1,30 };
				rotationPlt6.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt6, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
			}

			//curva horaria
			{
				angle = -45;
				rotationPlt7.SetPos(93.73f, 14.5, -113.8f);
				rotationPlt7.size = { 10,1,12.5 };
				rotationPlt7.SetRotation(angle, { 0,1,0 });
				rotationPlt7.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt7, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

				angle = 90;
				rotationPlt8.SetPos(100.63f, 14.5, -116.75f);
				rotationPlt8.size = { 10,1,12 };
				rotationPlt8.SetRotation(angle, { 0,1,0 });
				rotationPlt8.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt8, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

				angle = 45;
				rotationPlt9.SetPos(107.63f , 14.5, -113.8f);
				rotationPlt9.size = { 10,1,12.5 };
				rotationPlt9.SetRotation(angle, { 0,1,0 });
				rotationPlt9.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt9, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

				rotationPlt10.SetPos(110.53f, 14.5, -98.0);
				rotationPlt10.size = { 10,1,30 };
				rotationPlt10.color = White;
				lisseners.add(App->physics->AddBody(rotationPlt10, 0));
				lisseners.getLast()->data->collision_listeners.add(this);
				lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
				// Semicurva
				{

					angle = 45;
					rotationPlt11.SetPos(93.73f + 19.73f, 14.5, -82.2);
					rotationPlt11.size = { 10,1,12.5 };
					rotationPlt11.SetRotation(angle, { 0,1,0 });
					rotationPlt11.color = White;
					lisseners.add(App->physics->AddBody(rotationPlt11, 0));
					lisseners.getLast()->data->collision_listeners.add(this);
					lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

					angle = 90;
					rotationPlt12.SetPos(100.63f + 19.73f, 14.5, -79.25);
					rotationPlt12.size = { 10,1,12 };
					rotationPlt12.SetRotation(angle, { 0,1,0 });
					rotationPlt12.color = White;
					lisseners.add(App->physics->AddBody(rotationPlt12, 0));
					lisseners.getLast()->data->collision_listeners.add(this);
					lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);

					angle = 45;
					rotationPlt13.SetPos(107.63f + 19.73f, 14.5, -79.25 + 2.95f);
					rotationPlt13.size = { 10,1,12.5 };
					rotationPlt13.SetRotation(angle, { 0,1,0 });
					rotationPlt13.color = White;
					lisseners.add(App->physics->AddBody(rotationPlt13, 0));
					lisseners.getLast()->data->collision_listeners.add(this);
					lisseners.getLast()->data->body->setUserPointer(lisseners.getLast()->data);
				}
			}


		}
		
		// Haciendo
		{
			float radio = 7;
			Ramp({ 130,14,-59.2 }, true, { radio,1.5,27 });
			Ramp({ 130,14,85 }, false, { radio,1.5,27 });

			//Ramp({ 100,14,109.2 }, true, { radio,1.5,27 });
			//MidRamp({ 20,14,185 }, false, { 27 ,1.5,radio });

			angle = 30;
			wall14.SetPos(100, 14, 85);
			wall14.size = { 90,1,25 };
			
			wall14.color = White;
			lisseners.add(App->physics->AddBody(wall14, 0));


			angle = -10;
			wall15.SetPos(35.5, 16, 125);
			wall15.size = { 40,1.5,25 };
			wall15.SetRotation(angle, { 0,0,1 });
			lisseners.add(App->physics->AddBody(wall15, 0));
			wall15.color = White;



			Ramp({ 130,14,-59.2 }, true, { radio,1.5,27 });
			radio = 5;
			Ramp({ 0,0,100 }, { 10,1,radio });

		}



		Looping({ 18.0f, 14.5, 50.0 });

		wall10.SetPos(-70, 10, -10);
		wall10.size = { 60,2,7 };
		wall10.color.Set(0.5f,0.5f,1.0f);
		lisseners.add(App->physics->AddBody(wall10, 0));
		lisseners.getLast()->data->body->setFriction(0.00f);
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
		bodySensor = App->physics->AddBody(cubeSensor, 0);
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
		wall10.Render();
		wall11.Render();
		wall12.Render();
		wall13.Render();
		wall14.Render();
		wall15.Render();

		rotationPlt1.Render();
		rotationPlt2.Render();
		rotationPlt3.Render();
		rotationPlt4.Render();
		rotationPlt5.Render();
		rotationPlt6.Render();
		rotationPlt7.Render();
		rotationPlt8.Render();
		rotationPlt9.Render();
		rotationPlt10.Render();
		rotationPlt11.Render();
		rotationPlt12.Render();
		rotationPlt13.Render();

	

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
	
		offset -=(size.x*2.7 )/numCubes ;
	}

}

void ModuleSceneIntro::CylinderWalls(vec3 position)
{
#define PI 3.14159265358979323846
	Cube* cube;
	float numCubes = 84;
	float alpha = 0;
	float auxAngle = (360.0f * 4) / numCubes;
	float offset = 0;
	float radio = 2.5f;
	float rad = 0;
	float posX = position.x;
	float posY = position.y+radio * cos(rad);
	float posZ = -position.z+ radio * cos(rad);
	vec3 size = { 5.0f,0.75f,radio+0.15f  };
	vec3 axis = { size.x,size.z,size.z };

	for (int i = 0; i < numCubes; i++)
	{

		alpha -= auxAngle;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posY += radio * sin(rad);
		posZ += radio * cos(rad);

		cube = new Cube();
		cube->SetPos(posX+offset, posY,-posZ);
		cube->size = size;
		cube->color = White;
		cube->SetRotation(alpha- (auxAngle/2), { 1,0,0 });
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



void ModuleSceneIntro::Ramp(vec3 position,bool inverse,  vec3 size)
{
	Cube* cube;
	float numCubes = 12;
	float alpha = 0;
	float auxAngle = 90.0f / numCubes;
	float offset = 0;
	float rad = 0;
	float radio = size.x;
	//vec3 size = size.;
	float posX = position.x;
	float posY = position.y;
	float posZ = -position.z;
	vec3 axis = { size.x,size.z,size.z };


	for (int i = 0; i < numCubes; i++)
	{


		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posX += radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		if (alpha > 42.5)
			cube->SetPos(posX, posY, -posZ - (offset*1.15f));
		else	
			cube->SetPos(posX, posY, -posZ - offset);


		cube->size = size;
		if(alpha >42.5)
			cube->size = { size.x,size.y,size.z +(i*5.5f)+(10-(posY/10))};
		else
		cube->size = { size.x,size.y,size.z +(i*4)+(10-(posY/10))};;
		cube->color = White;

		cube->SetRotation(alpha + (auxAngle/2), { 0,0,1 });


		looping.add(cube);
		lisseners.add(App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);

		alpha += auxAngle;


		if(inverse)offset -= size.z*2 / numCubes;
		else offset += size.z * 2 / numCubes;
	}

}

void ModuleSceneIntro::MidRamp(vec3 position, bool inverse, vec3 size)
{
	Cube* cube;
	float numCubes = 12;
	float alpha = 0;
	float auxAngle = 90.0f / numCubes;
	float offset = 0;
	float rad = 0;
	float radio = size.z;
	//vec3 size = size.;
	float posX = position.x;
	float posY = position.y;
	float posZ = -position.z;
	vec3 axis = { size.x,size.z,size.z };


	for (int i = 0; i < numCubes; i++)
	{


		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ -= radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		if (alpha > 42.5)
			cube->SetPos(posX + (offset * 1.15f), posY, -posZ);
		else
			cube->SetPos(posX + offset, posY,-posZ);


		cube->size = size;
		if (alpha > 42.5)
			cube->size = { size.x+ (i * 5.5f) + (10 - (posY / 10)),size.y,size.z  };
		else
			cube->size = { size.x+ (i * 4) + (10 - (posY / 10)),size.y,size.z  };
		cube->color = White;

		cube->SetRotation(-alpha - (auxAngle / 2), { 1,0,0 });


		looping.add(cube);
		lisseners.add(App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);

		alpha += auxAngle;


		if (inverse)offset -= size.x * 2 / numCubes;
		else offset += size.x * 2 / numCubes;
	}

}

void ModuleSceneIntro::Ramp(vec3 position, vec3 size)
{
	Cube* cube;
	float numCubes = 8;
	float alpha = 0;
	float auxAngle = 90.0f / numCubes;
	float offset = 100;
	float rad = 0;
	float radio = size.z;
	//vec3 size = size;
	vec3 axis = { size.x,size.z,size.z };

	float posX = position.x;
	float posY = position.y;
	float posZ = -position.z;




	for (int i = 0; i < numCubes; i++)
	{

		alpha += auxAngle;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ += radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		cube->SetPos(posX+offset, posY, -posZ);
		cube->size = size;
		cube->color = White;

		cube->SetRotation(alpha + (auxAngle / 2), { 1,0,0 });
		

		looping.add(cube);
		lisseners.add( App->physics->AddBody(*cube, 0));
		lisseners.getLast()->data->collision_listeners.add(this);



		//posZ += size.z / numCubes;
	}

}
