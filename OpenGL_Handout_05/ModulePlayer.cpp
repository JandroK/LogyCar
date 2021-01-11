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
	car.chassis_offset.Set(0, 0.225f, -0.05);

	car.chassis2_size.Set(0.90, 0.35, 1);
	car.chassis2_offset.Set(0, car.chassis_offset.y+0.35, car.chassis_offset.z -0.1);

	car.chassis3_size.Set(1.10, 0.10, 0.20);
	car.chassis3_offset.Set(0, car.chassis_offset.y + 0.40, car.chassis_offset.z- car.chassis_size.z/2.05f);

	car.chassis4_size.Set(0.075, 0.20, 0.075);
	car.chassis4_offset.Set(-0.25, car.chassis_offset.y + 0.60, car.chassis_offset.z-0.4);

	car.chassis5_size.Set(0.05, 0.50, 0.05);
	car.chassis5_offset.Set(-0.25, car.chassis_offset.y + 0.85, car.chassis_offset.z-0.4);
	
	// Car properties ----------------------------------------


	car.mass =130.0f;
	car.suspensionStiffness = 4.30f;
	car.suspensionCompression = 0.42f;
	car.suspensionDamping =0.35f;
	car.maxSuspensionTravelCm = 110;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 1000.0f;


	// Wheel properties ---------------------------------------
	float connection_height = car.chassis_size.y- car.chassis_offset.z+0.5;
	float wheel_radius = 0.6f;
	float wheel_width = 0.83f;
	float suspensionRestLength = 1.25f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x+0.28f;
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
	//vehicle->state = IDLE;
	brake = 5.0f;
	turn = acceleration = 0.0f;
	AssistDirection(90.0f);
	forwardVector = vehicle->vehicle->getForwardVector();
	btVector3 per = { -forwardVector.getZ(),forwardVector.getY(),forwardVector.getX() };

	aux.setValue(forwardVector.getZ(), forwardVector.getY(), forwardVector.getX());

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
	{
		const float matrix[3] = { 0,1,0 };
		//vehicle->SetTransform(matrix);
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)vehicle->SetPos(-50.0f, 6.0f, -150.0f);
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)vehicle->SetPos(40, 14, -90);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)vehicle->SetPos(40, 20, 15);
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)vehicle->SetPos(-110, 12, -10);

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && (vehicle->state == State::WALK || vehicle->state == State::TURBO))
	{
		vel = MAX_ACCELERATION * 2;
		vehicle->state = TURBO;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-69,0 });
	}
	else
	{
		vel = MAX_ACCELERATION;
		vehicle->state = State::IDLE;

	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if(vehicle->state != State::TURBO)vehicle->state = State::WALK;

		if (vehicle->vehicle->getCurrentSpeedKmHour() <= -1) 
			brake = BRAKE_POWER/1.5f;
		else 
			acceleration = vel;
		vehicle->body->applyTorque(per *-80);
	}
	
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (vehicle->state != State::TURBO)vehicle->state = State::WALK;

		if (vehicle->vehicle->getCurrentSpeedKmHour() > +1) 
			brake = BRAKE_POWER / 1.5f;
		else 
			acceleration = vel * -1;
		vehicle->body->applyTorque(per *80);
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn += (TURN_DEGREES) - assistDirection;
		vehicle->body->applyTorque(forwardVector * -45);
		brake = 15;

	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES) 
			turn -= (TURN_DEGREES)- assistDirection;
		brake = 15;

		vehicle->body->applyTorque(forwardVector * 45);
		LOG("%d ", (int)vehicle->body->getTotalTorque().length());
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN )
	{
		isJumped = true;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,+69999,0 });
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
	float turnDegrees = (TURN_DEGREES / DEGTORAD);
	calculate = (vehicle->GetKmh() / 15) * (hardness/100.0f);
	if (calculate <= turnDegrees)
		assistDirection = calculate * DEGTORAD;
	else assistDirection = (turnDegrees-1) * DEGTORAD;

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



