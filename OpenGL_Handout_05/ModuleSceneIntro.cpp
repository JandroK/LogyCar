#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "Globals.h"

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
	offsetOfFloor = 1000;

	Cube* cube;
	timer = new Timer();

	//Musica
	App->audio->PlayMusic("Assets/Music/fall_guys.ogg");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Big plane as ground
	//{
	//	btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState();
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

	//	btRigidBody* rigidBbody = new btRigidBody(rbInfo);
	//	rigidBbody->activate();
	//	App->physics->world->addRigidBody(rigidBbody);
	//	
	//}


	//float height = 0.1f;
	//ground.SetPos(0, 0.4f, 0);
	//ground.size = { 400,height ,400 };
	//ground.color.Set(0.80f, 0.88f, 1.f, 1.f);
	//physBodyCubes.add(App->physics->AddBody(ground, 0));
	//physBodyCubes.getLast()->data->SetAsSensor(true);



	//// Limits
	//{
	//	float height = 10;
	//	cube = new Cube(400, height + 1, 2);
	//	cube->SetPos(0, height/2.0f, 200);
	//	cubes.add(cube);		
	//	physBodyCubes.add(App->physics->AddBody(*cube, 0));

	//	cube = new Cube(1,height+1,400 );
	//	cube->SetPos(200, height / 2.0f, 0);
	//	cube->color = Red;
	//	cubes.add(cube);		
	//	physBodyCubes.add(App->physics->AddBody(*cube, 0));


	//	cube = new Cube(1, height + 1, 400);
	//	cube->SetPos(-200, height / 2.0f, 0);
	//	cube->color = Red;
	//	cubes.add(cube); 		
	//	physBodyCubes.add(App->physics->AddBody(*cube, 0));

	//	cube = new Cube(400, height + 1, 1);
	//	cube->SetPos(0, height / 2.0f, -200);
	//	cubes.add(cube);		
	//	physBodyCubes.add(App->physics->AddBody(*cube, 0));

	//}

	// Platforms
	{
		// Done
		{
			// CheckPoint Reset
			cube = new Cube(35, 1, 15);
			cube->SetPos(-110, 0+offsetOfFloor, -86);
			cube->color = White;
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));
			platformsCheckpoints.add(physBodyCubes.getLast()->data);


			cube = new Cube(10, 1, 15);
			cube->SetPos(-90, 1.0f + offsetOfFloor, -86);
			cube->color = Red;
			cube->SetRotation(23, { 0,0,1 });
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			cube = new Cube(26, 1, 20);
			cube->SetPos(-55.5895, 4.162 + offsetOfFloor, -86);
			cube->color = White;
			cubes.add(cube); 
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			// segunda rampa
			cube = new Cube(8, 1, 20);
			cube->SetPos(-39, 5.5f + offsetOfFloor, -86.0f);
			cube->color = White;
			cube->SetRotation(20, { 0,0,1 });
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			// Cilindro
			CylinderWalls({ 14.5, 21 + offsetOfFloor, -85.5f });

			// plataforma con pared
			{
				//checkPoint 1
				angle = -20;
				cube = new Cube(20, 2, 20);
				cube->SetPos(40, 14 + offsetOfFloor, -81);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = Red;
				reference = *cube;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				platformsCheckpoints.add(physBodyCubes.getLast()->data);


				// pared de la plataforma 
				cube = new Cube(reference.size.y, 10, cube->size.z);
				cube->SetPos(reference.GetPos().x + 9 * cos(-angle * PI / 180), (reference.GetPos().y + (cube->size.y / 2)), reference.GetPos().z + 9 * sin(-angle * PI / 180));
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
			cube->SetPos(50.8, 14.5 + offsetOfFloor, -109.5);
			cube->SetRotation(angle, { 0,1,0 });
			cube->color = White;
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));


			angle = 0;
			cube = new Cube();
			cube->size = { 5,1,5 };
			cube->SetPos(51.8f, 14.5 + offsetOfFloor, -110.2);
			cube->SetRotation(angle, { 0,1,0 });
			cube->color = White;
			cubes.add(cube); 		
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			angle = -90;
			radi = 2.5f;
			// Plancha
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
			cubes.add(cube); 	
			physBodyCubes.add(App->physics->AddBody(*cube, 0));

			//curva anti horaria
			{
				// CheckPoint Curves
				cube = new Cube();
				cube->SetPos(71.07f, 14.5 + offsetOfFloor, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				platformsCheckpoints.add(physBodyCubes.getLast()->data);



				angle = 45;
				cube = new Cube();
				cube->SetPos(74.0f, 14.5 + offsetOfFloor, -82.2);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = 90;
				cube = new Cube();
				cube->SetPos(80.9f, 14.5 + offsetOfFloor, -79.25);
				cube->size = { 10,1,12 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = -45;
				cube = new Cube();
				cube->SetPos(87.9f, 14.5 + offsetOfFloor, -82.2);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				cube = new Cube();
				cube->SetPos(90.8f, 14.5 + offsetOfFloor, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

			}
			//curva horaria
			{
				angle = -45;
				cube = new Cube();
				cube->SetPos(93.73f, 14.5 + offsetOfFloor, -113.8f);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				;

				angle = 90;
				cube = new Cube();
				cube->SetPos(100.63f, 14.5 + offsetOfFloor, -116.75f);
				cube->size = { 10,1,12 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				angle = 45;
				cube = new Cube();
				cube->SetPos(107.63f , 14.5 + offsetOfFloor, -113.8f);
				cube->size = { 10,1,12.5 };
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				cube = new Cube();
				cube->SetPos(110.53f, 14.5 + offsetOfFloor, -98.0);
				cube->size = { 10,1,30 };
				cube->color = White;
				cubes.add(cube); 	
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				// Semicurva
				{

					angle = 45;
					cube = new Cube();
					cube->SetPos(93.73f + 19.73f, 14.5 + offsetOfFloor, -82.2);
					cube->size = { 10,1,12.5 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 90;
					cube = new Cube();
					cube->SetPos(100.63f + 19.73f, 14.5 + offsetOfFloor, -79.25);
					cube->size = { 10,1,12 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 45;
					cube = new Cube();
					cube->SetPos(107.63f + 19.73f, 14.5 + offsetOfFloor, -79.25 + 2.95f);
					cube->size = { 10,1,12.5 };
					cube->SetRotation(angle, { 0,1,0 });
					cube->color = White;
					cubes.add(cube); 
					physBodyCubes.add(App->physics->AddBody(*cube, 0));


					angle = 45;
					cube = new Cube(10,1,30 );
					cube->SetPos(130, 14.5 + offsetOfFloor, -60);
					cube->color = White;
					cubes.add(cube); 	
					physBodyCubes.add(App->physics->AddBody(*cube, 0));

				}
			}
			//	Obstacles to looping
			{
				float radio = 7;
				Ramp({ 130,14 + offsetOfFloor,-59.2 }, true, { radio,1.5,27 });
				Ramp({ 130,14 + offsetOfFloor,85 }, false, { radio,1.5,27 });

				//Ramp({ 100,14,109.2 }, true, { radio,1.5,27 });
				//MidRamp({ 20,14,185 }, false, { 27 ,1.5,radio });
				
				// CheckPoint WallRide
				cube = new Cube();
				cube->SetPos(121.5, 14 + offsetOfFloor, 89.7);
				cube->size = { 25,1,33 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				platformsCheckpoints.add(physBodyCubes.getLast()->data);


				angle = -20;
				cube = new Cube();
				cube->SetPos(122, 14 + offsetOfFloor, 128);
				cube->size = { 20,1,25 };
				cube->SetRotation(angle, { 1,0,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				cube = new Cube();
				cube->SetPos(120, 14 + offsetOfFloor, 160);
				cube->size = { 30,2,20 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				angle = -20;
				cube = new Cube();
				cube->SetPos(62.8, 24.8 + offsetOfFloor, 159.7);
				cube->size = { 60,2,20 };
				cube->SetRotation(angle, { 0,0,1 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				// CheckPoint PreLooping
				cube = new Cube();
				cube->SetPos(20, 35 + offsetOfFloor, 159.7);
				cube->size = { 30,2,20 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				platformsCheckpoints.add(physBodyCubes.getLast()->data);


				cube = new Cube();
				angle = -11.2;
				cube->SetPos(18, 24.7 + offsetOfFloor, 99);
				cube->size = { 19.5,1,104 };
				cube->SetRotation(angle, { 1,0,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				cube = new Cube();
				cube->SetPos(18, 15 + offsetOfFloor, 47);
				cube->size = { 19.5,1,6 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));


				//	Ramp({ 130,14,-59.2 }, true, { radio,1.5,27 });
				//radio = 5;
				//Ramp({ 0,0,100 }, { 10,1,radio });
			}

			Looping({ 18.0f, 14.5f + offsetOfFloor, 50.0 });

			// peralt
			{
				cube = new Cube();
				cube->SetPos(-25.5, 12 + offsetOfFloor, -25);
				cube->size = { 1.5,12,55 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				
				cube = new Cube();
				cube->SetPos(-100.5, 12 + offsetOfFloor, -25);
				cube->size = { 1.5,12,55 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				cube = new Cube();
				cube->SetPos(-63, 12 + offsetOfFloor, -52.5);
				cube->size = { 76.5,12,1.5 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				// check point peralt
				cube = new Cube();
				cube->SetPos(-35.8, 15.25 + offsetOfFloor, 30);
				cube->size = { 19.5,1,60 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				platformsCheckpoints.add(physBodyCubes.getLast()->data);

				angle = -20;
				cube = new Cube();
				cube->SetPos(-35.8, 11.15 + offsetOfFloor, -11.1);
				cube->size = { 19.5,1,24 };
				cube->SetRotation(angle, { 1,0,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				angle = 22;
				cube = new Cube();
				cube->SetPos(-35.5, 11 + offsetOfFloor, -25);
				cube->size = { 22,1,55 };
				cube->SetRotation(angle, { 0,0,1 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				angle = 22;
				cube = new Cube();
				cube->SetPos(-63, 11 + offsetOfFloor, -42.5);
				cube->size = { 75,1,22 };
				cube->SetRotation(angle, { 1,0,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				angle = -22;
				cube = new Cube();
				cube->SetPos(-90.5, 11 + offsetOfFloor, -25);
				cube->size = { 22,1,55 };
				cube->SetRotation(angle, { 0,0,1 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				angle = -20;
				cube = new Cube();
				cube->SetPos(-90.3, 11.15 + offsetOfFloor, -11.1);
				cube->size = { 19.5,1,24 };
				cube->SetRotation(angle, { 1,0,0 });
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				// Checkpoint postPeralt
				cube = new Cube();
				cube->SetPos(-90.3, 15.25 + offsetOfFloor, 32.5);
				cube->size = { 19.5,1,65 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				//physBodyCubes.getLast()->data->body->setUserPointer(physBodyCubes.getLast()->data->body);
				platformsCheckpoints.add(physBodyCubes.getLast()->data);

			}

			// Ramps
			{
				RampFlip({ -115.3, 15 + offsetOfFloor, 60.5 }, { 70,1,6 });

				cube = new Cube();
				cube->SetPos(-140.3, 15.25 + offsetOfFloor, 50.5);
				cube->size = { 20,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				Ramp({ -175.3, 15 + offsetOfFloor, 40 }, { 90,1,6 });

				cube = new Cube();
				cube->SetPos(-210.3, 15.25 + offsetOfFloor, 50.5);
				cube->size = { 20,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				RampFlip({ -235.3, 15 + offsetOfFloor, 60.5 }, { 70,1,6 });

				// CheckPoint posRamps
				cube = new Cube();
				cube->SetPos(-260.3, 15.25 + offsetOfFloor, 50.5);
				cube->size = { 20,1,30 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				//physBodyCubes.getLast()->data->body->setUserPointer(physBodyCubes.getLast()->data->body);
				platformsCheckpoints.add(physBodyCubes.getLast()->data);

			}
			// Ice and move platform
			{
				cube = new Cube();
				cube->SetPos(-260.3, 15.25 + offsetOfFloor, 0.5);
				cube->size = { 10,1.5,80 };
				cube->color.Set(0.5f, 0.5f, 1.0f);
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				physBodyCubes.getLast()->data->body->setFriction(0.00f);



				cubeMove = new Cube();
				cubeMove->SetPos(-250.3, 15.25 + offsetOfFloor, -34.5);
				cubeMove->size = { 10,2,10 };
				cubeMove->color.Set(0.5f, 1.0f, 0.5f);
				cubeMovBody = App->physics->AddBody(*cubeMove, 0);

				cube = new Cube();
				cube->SetPos(-175.3, 90.25 + offsetOfFloor, -34.5);
				cube->size = { 139.9,2,10 };
				cube->color.Set(0.5f, 0.5f, 1.0f);
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));
				physBodyCubes.getLast()->data->body->setFriction(0.00f);
			}
			// Sensors
			{
				cube = new Cube();
				cube->SetPos(-100, 90.25 + offsetOfFloor, -34.5);
				cube->size = { 12,2,12 };
				cube->color = White;
				cubes.add(cube);
				physBodyCubes.add(App->physics->AddBody(*cube, 0));

				cubeSensor.SetPos(cube->GetPos().x, cube->GetPos().y + 1.1f, cube->GetPos().z);
				cubeSensor.size = { cube->size.x - 0.5f,0.45f,cube->size.z - 0.5f };
				cubeSensor.color = White;
				bodySensor = App->physics->AddBody(cubeSensor, 0);
				bodySensor->SetAsSensor(true);
				bodySensor->collision_listeners.add(this);
				bodySensor->body->setUserPointer(bodySensor);
			}


		}
		
		// Haciendo
		{
			// checkpoints
			{
				// Checkpoint Reset
				cube = new Cube(1,1,1);
				cube->SetPos(-110, 3 + offsetOfFloor, -86);
				cube->color = White;
				cube->SetRotation(90,{ 0,1,0 });
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };

				// Checkpoint post Cilynder
				angle = -200;
				cube = new Cube( 1,1,1 );
				cube->SetPos(40, 17 + offsetOfFloor, -81);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };

				// Checkpoint Curvas
				cube = new Cube( 1,1,1 );
				cube->SetPos(71.07f, 17.5 + offsetOfFloor, -98.0);
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };

				// Checkpoint WallRide
				cube = new Cube( 1,1,1 );
				cube->SetPos(121.5, 17 + offsetOfFloor, 89.7);
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };

				//Checkpoint PreLooping
				angle = 180;
				cube = new Cube( 1,1,1 );
				cube->SetPos(19, 39 + offsetOfFloor, 159.7);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };


				// CheckPoint Peralt
				angle = 180;
				cube = new Cube( 1,1,1 );
				cube->SetPos(-35.8, 19.25 + offsetOfFloor, 30);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };

				// CheckPoint postPeralt
				cube = new Cube( 1,1,1 );
				cube->SetPos(-90.3, 19.25 + offsetOfFloor, 32.5);
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };


				angle = 180;
				cube = new Cube(1, 1, 1);
				cube->SetPos(-260.3, 19.25 + offsetOfFloor, 50.5);
				cube->SetRotation(angle, { 0,1,0 });
				cube->color = White;
				checkopints.add(cube);
				physBodyCheckopints.add(App->physics->AddBody(*cube, 0));
				physBodyCheckopints.getLast()->data->SetAsSensor(true);
				cube->size = { 0,0,0 };


			}
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
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)App->SetDebugMode();

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	ground.Render();
	cubeSensor.Render();

	CubeMoveRender();

	ChangeColor();

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
		cubeWorld->data->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::CubeMoveRender()
{
	cubeMove->Render();
	cubeMove->color.Set(cX, cY, cZ);

	posMoveY = cubeMove->GetPos().y;
	if ((posMoveY<=90.25 + offsetOfFloor) && moveToUp)
	{
		posMoveY += 0.10;
		cubeMove->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
		cubeMovBody->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);

	}
	else if ((posMoveY >= 15+offsetOfFloor) && !moveToUp)
	{
		posMoveY -= 0.16;
		cubeMove->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
		cubeMovBody->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
	}
	else
	{
		if (!timerStarted)
		{
			timerStarted = true;
			timer->Start();
		}
		if (timer->Read() > 3000)
		{
			timerStarted = false;
			moveToUp = !moveToUp;
		}

	}
}

void ModuleSceneIntro::ChangeColor()
{
	if ((cX <= 1.1 || cY <= 1.1 || cZ <= 1.1) && changeColor)
	{
		cX += increment1;
		cY += increment2;
		cZ += increment3;
	}
	else if ((cX >= 0.4 && cY >= 0.4 && cZ >= 0.4) && !changeColor)
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
			aux = increment1;
			increment1 = increment2;
			increment2 = increment3;
			increment3 = aux;
		}

	}
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == bodySensor || body2 == bodySensor)&& !win)
	{
		win = true;
		App->audio->PlayMusic("Assets/Music/you_win.ogg");
		btVector3 vec = bodySensor->body->getCenterOfMassPosition();
		vec3 sizeCube= cubeSensor.size ;
	//	cubeSensor.SetPos(vec.getX(), vec.getY() - 0.25, vec.getZ());
		cubeSensor.color = Green;
		cubeSensor.size.y = 0.10f;
		bodySensor->SetPos(vec.getX(),vec.getY()-1,vec.getZ());
	}
	if ((physBodyCubes.find(body1) >= 0 || physBodyCubes.find(body2) >= 0))
	{
		LOG("En el suelo");
	}

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
		cube->color.Set(40 / posX + 1.65, 40 /( posY- offsetOfFloor), 40 / posZ);
		//LOG("Position Player \n x: %f \t y: %f \t z: %f ", posX + offset, posY, -posZ);


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

		cube = new Cube();
		cube->SetPos(posX+ size.x +offset, posY,-posZ);
		cube->size = size;
		cube->color = Red;
		cube->SetRotation(alpha-8.5 , { 1,0,0 });
		cilinderWall.add(cube);
		physBodyCubes.add(App->physics->AddBody(*cube, 0));

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
			cube->size = { size.x,size.y,size.z +(i*5.5f)+(10-((posY - offsetOfFloor) /10))};
		else
		cube->size = { size.x,size.y,size.z +(i*4)+(10-((posY - offsetOfFloor) /10))};;
		cube->color = White;
		cube->color.Set(40 / posX + 1.65, 40 / (posY - offsetOfFloor), 40 / posZ);

		cube->SetRotation(alpha + (auxAngle/2), { 0,0,1 });


		looping.add(cube);
		physBodyCubes.add(App->physics->AddBody(*cube, 0));

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
	float numCubes = 10;
	float alpha = 0;
	float auxAngle = 90.0f / numCubes;
	float offset = 0;
	float rad = 0;
	float radio = size.z;
	//vec3 size = size;

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
		cube->size.Set(size.x,size.y,size.z + 0.25);
		cube->color = White;

		cube->SetRotation(alpha + (auxAngle / 2), { 1,0,0 });
		cube->color.Set(40 / posX + 1.65, 40 / posY, 40 / posZ);


		looping.add(cube);
		physBodyCubes.add( App->physics->AddBody(*cube, 0));

		//posZ += size.z / numCubes;
	}

}
void ModuleSceneIntro::RampFlip(vec3 position, vec3 size)
{
	Cube* cube;
	float numCubes = 10;
	float alpha = 0;
	float auxAngle = 90.0f / numCubes;
	float offset =0 ;
	float rad = 0;
	float radio = size.z;

	float posX = position.x;
	float posY = position.y;
	float posZ = -position.z;




	for (int i = 0; i < numCubes; i++)
	{

		alpha += auxAngle;

		rad = alpha * PI / 180;

		//posZ = axis.z * cos(alpha) - axis.y * sin(alpha);
		//posY = axis.z * cos(alpha) + axis.y * sin(alpha);

		posZ -= radio * cos(rad);
		posY += radio * sin(rad);

		cube = new Cube();
		cube->SetPos(posX+offset, posY, -posZ);
		cube->size.Set(size.x, size.y, size.z + 0.25);
		cube->color = White;

		cube->SetRotation(-alpha - (auxAngle / 2), { 1,0,0 });
		cube->color.Set(40 / posX + 1.65, 40 / (posY - offsetOfFloor), 40 / posZ);


		looping.add(cube);
		physBodyCubes.add( App->physics->AddBody(*cube, 0));



		//posZ += size.z / numCubes;
	}

}
