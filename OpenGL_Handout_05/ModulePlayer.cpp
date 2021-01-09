#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	
// ----------------------------------------Vehicle chassis----//
	car.chassis_size.Set(1, 0.5f, 2);
	car.chassis_offset.Set(0, 0.5f, -0.25);

	car.chassis2_size.Set(0.90, 0.35, 1);
	car.chassis2_offset.Set(0, 0.85, car.chassis_offset.z -0.1);

	//car.chassis3_size.Set(1.10, 0.10, 0.50);
	//car.chassis3_offset.Set(0, 1.7, 3);
	// Car properties ----------------------------------------


	car.mass =120.0f;
	car.suspensionStiffness = 3.80f;
	car.suspensionCompression = 0.2f;
	car.suspensionDamping =1.0f;
	car.maxSuspensionTravelCm = 110;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 1000.0f;


	// Wheel properties ---------------------------------------
	float connection_height = car.chassis_size.y+0.75;
	float wheel_radius = 0.6f;
	float wheel_width = 0.85f;
	float suspensionRestLength = 1.25f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x+0.2f;
	float half_length = car.chassis_size.z*0.6f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius + 0.2 + car.chassis_offset.z);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;


	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius + 0.2 + car.chassis_offset.z);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius-0.2 + car.chassis_offset.z);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius-0.2 + car.chassis_offset.z);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(-50, 6, -150);
	
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{ 
	brake = 2.5f;
	turn = acceleration =0.0f;
	AssistDirection(99.0f);


	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
	{
		const float matrix[3] = { 0,1,0 };
		vehicle->SetTransform(matrix);
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)vehicle->SetPos(-50, 6, -150);
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)vehicle->SetPos(40, 14, -90);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)vehicle->SetPos(40, 20, 15);
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)vehicle->SetPos(-110, 12, -10);

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)vel = MAX_ACCELERATION * 2;
	else vel = MAX_ACCELERATION;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
			//vehicle->vehicle->getRigidBody()->applyCentralForce({0,-100,0});
			if (vehicle->vehicle->getCurrentSpeedKmHour() <= -1) 
				brake = BRAKE_POWER/1.5f;
			else 
				acceleration = vel;
	}
	
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		//vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-500,0 });
		if (vehicle->vehicle->getCurrentSpeedKmHour() > +1) 
			brake = BRAKE_POWER / 1.5f;
		else 
			acceleration = vel * -1;
		//LOG("%f", (float)vehicle->vehicle->getCurrentSpeedKmHour());
	}


	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn += (TURN_DEGREES) - assistDirection;
		vehicle->vehicle->getRigidBody()->applyTorque({ vehicle->body->getCenterOfMassPosition().getX() + vehicle->vehicle->getForwardVector().x() * -500,0,0 });
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES) 
			turn -= (TURN_DEGREES)- assistDirection;
		vehicle->vehicle->getRigidBody()->applyTorque({ vehicle->body->getCenterOfMassPosition().getX() + vehicle->vehicle->getForwardVector().x()*500,0,0 });
		vehicle->body->getCenterOfMassPosition().getX();

	}

	if( App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;

	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN )
	{
		isJumped = true;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,+70000,0 });

	}


	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	if (!App->GetDebugMode())
	{
		vec3 myCamera;
		vec3 myCameraLook;
		float distanceCamara2CM = -9;

		myCamera.x = vehicle->body->getCenterOfMassPosition().getX() + vehicle->vehicle->getForwardVector().x() * distanceCamara2CM;
		myCamera.y = vehicle->body->getCenterOfMassPosition().getY() + 6;
		myCamera.z = vehicle->body->getCenterOfMassPosition().getZ() + vehicle->vehicle->getForwardVector().z() * distanceCamara2CM;

		myCameraLook.x = vehicle->body->getCenterOfMassPosition().getX();
		myCameraLook.y = vehicle->body->getCenterOfMassPosition().getY() + 4;
		myCameraLook.z = vehicle->body->getCenterOfMassPosition().getZ();

		App->camera->Position = myCamera;
		App->camera->LookAt(myCameraLook);
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::AssistDirection(float hardness)
{

	calculate = (vehicle->GetKmh() / 15) * (hardness/100.0f);
	if (calculate <= 17.0f)
		assistDirection = calculate * DEGTORAD;
	else assistDirection = 17.0f * DEGTORAD;

}


//btVector3 ModulePlayer::Norm(btVector3 vec)
//{
//	btVector3 vecNorm = vec;
//
//	
//	vecNorm.x= vecNorm.x/(sqrt((vecNorm.x* vecNorm.x)+(vecNorm.y* vecNorm.y)+(vecNorm.z* vecNorm.z)));
//	vecNorm.y = vecNorm.y / (sqrt((vecNorm.x * vecNorm.x) + (vecNorm.y * vecNorm.y) + (vecNorm.z * vecNorm.z)));;
//	vecNorm.z = vecNorm.z / (sqrt((vecNorm.x * vecNorm.x) + (vecNorm.y * vecNorm.y) + (vecNorm.z * vecNorm.z)));;
//	return vecNorm;
//}



