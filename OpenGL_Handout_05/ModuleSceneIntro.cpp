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

	Cube* cube;


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
	physBodyCubes.add(App->physics->AddBody(ground, 0));




	// Limits
	{
		float height = 10;
		cube = new Cube(400, height + 1, 2);
		cube->SetPos(0, height/2.0f, 200);
		cubes.add(cube);		physBodyCubes.add(App->physics->AddBody(*cube, 0));

		cube = new Cube(1,height+1,400 );
		cube->SetPos(200, height / 2.0f, 0);
		cube->color = Red;
		cubes.add(cube);		physBodyCubes.add(App->physics->AddBody(*cube, 0));


		cube = new Cube(1, height + 1, 400);
		cube->SetPos(-200, height / 2.0f, 0);
		cube->color = Red;
		cubes.add(cube); 		physBodyCubes.add(App->physics->AddBody(*cube, 0));

		cube = new Cube(400, height + 1, 1);
		cube->SetPos(0, height / 2.0f, -200);
cubes.add(cube);		physBodyCubes.add(App->physics->AddBody(*cube, 0));

	}

	// Platforms
	{
		// Done
		{
			cube = new Cube(10, 1, 15);
			cube->SetPos(-90, 1.0f, -86);
			cube->color = Red;
			cube->SetRotation(23, { 0,0,1 });
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			cube = new Cube(26, 1, 20);
			cube->SetPos(-55.5895, 4.162, -86);
			cube->color = White;
			cubes.add(cube); 
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			// segunda rampa
			cube = new Cube(8, 1, 20);
			cube->SetPos(-39, 5.5f, -86.0f);
			cube->color = White;
			cube->SetRotation(20, { 0,0,1 });
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			// Cilindro
			CylinderWalls({ 14.5, 21, -85.5f });

			// plataforma con pared
			{
				angle = -20;
				cube = new Cube(20, 2, 20);
				cube->SetPos(40, 14, -81);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				reference = *cube;
				cubes.add(cube); 		
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				// pared de la plataforma 
				cube = new Cube(reference.size.y, 10, cube->size.z);
				cube->SetPos(reference.GetPos().x + 9 * cos(-angle * PI / 180), reference.GetPos().y + (cube->size.y / 2), reference.GetPos().z + 9 * sin(-angle * PI / 180));
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 		
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

			}
			angle =-20 ;
			radi = 2.5f;

			// Plancha
			cube = new Cube( 1.3,0.5,20 );
			cube->SetPos(45.7, (reference.GetPos().y + ((reference.size.y/2) - (cube->size.y))), -99.1);
			cube->color = White;
			cube->SetRotation(angle, { 0,1,0 });
			reference = *cube;
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			cube = new Cube( 1.3,0.5,20);
			cube->SetPos(reference.GetPos().x + radi * cos(-angle * DEG_TO_RAD), reference.GetPos().y, reference.GetPos().z + +radi * sin(-angle * DEG_TO_RAD));
			cube->color = White;
			cube->SetRotation(angle, { 0,1,0 });
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));



			angle = -20;
			cube = new Cube();
			cube->size = { 5,1,5 };
			cube->SetPos(50.8, 14.5, -109.5);
			cube->SetRotation(angle, { 0,1,0 });
			cube->color = White;
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));


			angle = 0;
			cube = new Cube();
			cube->size = { 5,1,5 };
			cube->SetPos(51.8f, 14.5, -110.2);
			cube->SetRotation(angle, { 0,1,0 });
			cube->color = White;
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			angle = -90;
			radi = 2.5f;
			// Plancha
			//wall8.SetPos((wall6.GetPos().x- wall6.size.x) + radi * cos(-angle * DEG_TO_RAD), wall6.GetPos().y, (wall6.GetPos().z- wall6.size.z) + radi * sin(-angle * DEG_TO_RAD));
			cube = new Cube();
			cube->size = { 1.3,0.5,20 };
			cube->SetPos(63, reference.GetPos().y, -111.50);
			cube->color = White;
			cube->SetRotation(angle, { 0,1,0 });
			cubes.add(cube); 	
			reference = *cube;
			physBodyCubes.add(App->physics->AddBody(*cube, 0));


			// 
			cube = new Cube();
			cube->size = { 1.3,0.5,20 };
			cube->SetPos(reference.GetPos().x + radi * cos(-angle * DEG_TO_RAD), reference.GetPos().y, reference.GetPos().z + radi * sin(-angle * DEG_TO_RAD));
			cube->color = White;
			cube->SetRotation(angle, { 0,1,0 });
			cubes.add(cube); 		physBodyCubes.add(App->physics->AddBody(*cube, 0));
			;

			//curva anti horaria
			{
				cube = new Cube();
				cube->SetPos(71.07f, 14.5, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = 45;
				cube = new Cube();
				cube->SetPos(74.0f, 14.5, -82.2);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = 90;
				cube = new Cube();
				cube->SetPos(80.9f, 14.5, -79.25);
				cube->size = { 10,1,12 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = -45;
				cube = new Cube();
				cube->SetPos(87.9f, 14.5, -82.2);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				cube = new Cube();
				cube->SetPos(90.8f, 14.5, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

			}

			//curva horaria
			{
				angle = -45;
				cube = new Cube();
				cube->SetPos(93.73f, 14.5, -113.8f);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				;

				angle = 90;
				cube = new Cube();
				cube->SetPos(100.63f, 14.5, -116.75f);
				cube->size = { 10,1,12 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = 45;
				cube = new Cube();
				cube->SetPos(107.63f , 14.5, -113.8f);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				cube = new Cube();
				cube->SetPos(110.53f, 14.5, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				// Semicurva
				{

					angle = 45;
					cube = new Cube();
					cube->SetPos(93.73f + 19.73f, 14.5, -82.2);
					cube->size = { 10,1,12.5 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 90;
					cube = new Cube();
					cube->SetPos(100.63f + 19.73f, 14.5, -79.25);
					cube->size = { 10,1,12 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 45;
					cube = new Cube();
					cube->SetPos(107.63f + 19.73f, 14.5, -79.25 + 2.95f);
					cube->size = { 10,1,12.5 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 45;
					cube = new Cube();
					Cube cube1(10,1,12.5 );
					cube->SetPos(137, 14.5, -84);
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));

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

			cube = new Cube();
			cube->SetPos(121.5, 14, 89.7);
			cube->size = { 25,1,33 };
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			angle = -20;
			cube = new Cube();
			cube->SetPos(122, 14, 128);
			cube->size = { 20,1,25 };
			cube->SetRotation(angle, { 1,0,0 });
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));


			cube = new Cube();
			cube->SetPos(120, 14, 160);
			cube->size = { 30,2,20 };
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			angle = -20;
			cube = new Cube();
			cube->SetPos(62.8, 24.8, 159.7);
			cube->size = { 60,2,20 };
			cube->SetRotation(angle, { 0,0,1 });
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			cube = new Cube();
			cube->SetPos(20, 35, 159.7);
			cube->size = { 30,2,20 };
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			cube = new Cube();
			angle = -11.2;
			cube->SetPos(18, 24.7, 99);
			cube->size = { 19.5,1,104 };
			cube->SetRotation(angle, {1,0,0});
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));


		//	Ramp({ 130,14,-59.2 }, true, { radio,1.5,27 });
			radio = 5;
			//Ramp({ 0,0,100 }, { 10,1,radio });

		}



		Looping({ 18.0f, 14.5, 50.0 });

		cube = new Cube();
		cube->SetPos(-70, 10, -10);
		cube->size = { 60,2,7 };
		cube->color.Set(0.5f,0.5f,1.0f);
		cubes.add(cube); 
		physBodyCubes.add(App->physics->AddBody(*cube, 0));
		physBodyCubes.getLast()->data->body->setFriction(0.00f);

		
	}

	// Sensors
	{
		cube = new Cube();
		cube->SetPos(-110, 10, -10);
		cube->size = { 20,2,20 };
		cube->color = White;
		cubes.add(cube); 	
		physBodyCubes.add(App->physics->AddBody(*cube, 0));

		cubeSensor.SetPos(-110, 11.1f, -10);
		cubeSensor.size = { 19.5f,0.45f,19.5f };
		cubeSensor.color = White;
		bodySensor = App->physics->AddBody(cubeSensor, 0);
		bodySensor->SetAsSensor(true);
		bodySensor->collision_listeners.add(this);
		bodySensor->body->setUserPointer(bodySensor);
	}
	

	{
		/*p2List_item<tdata>* lissener = physBodyCubes.getFirst();
		for (int i = 0; i < physBodyCubes.count(); i++)
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
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)App->SetDebugMode();

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	ground.Render();
	cubeSensor.Render();

	if ((cX <= 1.1 || cY <= 1.1 || cZ <= 1.1 ) && changeColor)
	{
		cX += increment1;
		cY += increment2;
		cZ += increment3;
	}
	else if ((cX >= 0.4 && cY >= 0.4 && cZ >= 0.4) &&!changeColor)
	{
		cX -= increment1;
		cY -= increment2;
		cZ -= increment3;
	}
	else
	{
		changeColor = !changeColor;
		if (!changeColor) 
		{
			aux= increment1;
			increment1 = increment2;
			increment2 = increment3;
			increment3 = aux;
		}

	}

	for (p2List_item<Cube*>* cube = looping.getFirst(); cube; cube = cube->next)
	{
		cube->data->Render();
	}
	for (p2List_item<Cube*>* cube = cilinderWall.getFirst(); cube; cube = cube->next)
	{
		cube->data->Render();
	}
	for (p2List_item<Cube*>* cubeWorld = cubes.getFirst(); cubeWorld; cubeWorld = cubeWorld->next)
	{
		cubeWorld->data->color.Set(cX, cY, cZ);
		cubeWorld->data->Render();
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
	if ( (physBodyCubes.find(body1) >= 0 || physBodyCubes.find(body2) >= 0))
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
		physBodyCubes.add(App->physics->AddBody(*cube, 0));
	
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
		physBodyCubes.add(App->physics->AddBody(*cube, 0));
		physBodyCubes.getLast()->data->collision_listeners.add(this);

		cube = new Cube();
		cube->SetPos(posX+ size.x +offset, posY,-posZ);
		cube->size = size;
		cube->color = Red;
		cube->SetRotation(alpha-8.5 , { 1,0,0 });
		cilinderWall.add(cube);
		physBodyCubes.add(App->physics->AddBody(*cube, 0));
		physBodyCubes.getLast()->data->collision_listeners.add(this);

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
		physBodyCubes.add(App->physics->AddBody(*cube, 0));
		physBodyCubes.getLast()->data->collision_listeners.add(this);

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
		physBodyCubes.add(App->physics->AddBody(*cube, 0));

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
		physBodyCubes.add( App->physics->AddBody(*cube, 0));
		physBodyCubes.getLast()->data->collision_listeners.add(this);



		//posZ += size.z / numCubes;
	}

}
