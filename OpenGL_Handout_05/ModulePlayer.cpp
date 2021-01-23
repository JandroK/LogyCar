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
	
	// Load Fx
	dead = App->audio->LoadFx("Assets/Fx/player_die2.wav");

	VehicleInfo car;
	color.Set(1.0f, 1.0f, 1.0f, 1.0f);
	camLoop.Set(-8.88, 62.38, 51.7);
// ----------------------------------------Vehicle chassis----//
	car.chassis_size.Set(1, 0.5f, 2);
	car.chassis_offset.Set(0, 0.125f, 0.05);

	car.chassis2_size.Set(0.90, 0.35, 1);
	car.chassis2_offset.Set(0, car.chassis_offset.y+0.35, car.chassis_offset.z -0.1);

	car.chassis3_size.Set(1.10, 0.10, 0.25);
	car.chassis3_offset.Set(0, car.chassis_offset.y + 0.50, car.chassis_offset.z- car.chassis_size.z/2.05f);

	car.chassis4_size.Set(0.1, 0.30, 0.1);
	car.chassis4_offset.Set(-0.25, car.chassis_offset.y + 0.70, car.chassis_offset.z-0.4);

	car.chassis5_size.Set(0.075, 0.60, 0.075);
	car.chassis5_offset.Set(-0.25, car.chassis_offset.y + 0.95, car.chassis_offset.z-0.4);
	
	
	//car.sensor_size.Set(1,1,1);
	//car.sensor_offset.Set(0,5, 0);

	// Car properties ----------------------------------------

	car.mass =130.0f;
	car.suspensionStiffness = 26.10f;
	car.suspensionCompression = 1.42f;
	car.suspensionDamping =2.35f;
	car.maxSuspensionTravelCm = 510;
	car.frictionSlip = 100.5;
	car.maxSuspensionForce = 1000.0f;


	// Wheel properties ---------------------------------------
	float connection_height = car.chassis_size.y- car.chassis_offset.z+0.75;
	float wheel_radius = 0.6f;
	float wheel_width = 0.75f;
	float suspensionRestLength = 1.25f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x+0.28f;

	float half_length = car.chassis_size.z*0.6f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.4f * wheel_width, connection_height, half_length - wheel_radius + 0.2 + car.chassis_offset.z);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius * 0.95;
	car.wheels[0].width = wheel_width * 0.9;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;



	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.4f * wheel_width, connection_height, half_length - wheel_radius + 0.2 + car.chassis_offset.z);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius*0.95;
	car.wheels[1].width = wheel_width * 0.9;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius-0.4 + car.chassis_offset.z);
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
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius-0.4 + car.chassis_offset.z);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	
	// Sensors
	{
		VehicleInfo sensorInf;

		sensorInf.chassis_size.Set(0.5f, 0.5f, 0.5f);
		sensorInf.chassis_offset.Set(0, 0.125f, 0.05);
		sensorInf.mass = 0.001f;

		sensorV = App->physics->AddVehicle(sensorInf);
		sensorV->body->setGravity({0,0,0});
		sensorV->collision_listeners.add(this);
		sensorV->SetAsSensor(true);
		sensorV->body->setUserPointer(sensorV);
		sensorV->body->setCollisionFlags(sensorV->body->getCollisionFlags() | btCollisionObject::CO_GHOST_OBJECT);


		cubeSensor.SetPos(0, 10, 0);
		cubeSensor.size = {0.25,0.25,0.25 };
		cubeSensor.color = White;
		bodySensor =App->physics->AddBody(cubeSensor, 0);
		
		//App->physics->world->addCollisionObject(bodySensor);

		bodySensor->collision_listeners.add(this);
		bodySensor->body->setUserPointer(bodySensor);
		bodySensor->SetAsSensor(true);
		bodySensor->body->setCollisionFlags(bodySensor->body->getCollisionFlags() | btCollisionObject::CO_GHOST_OBJECT);

		bodySensor->SetPos(0, 10, 0);


	}
	

	vehicle = App->physics->AddVehicle(car);

	vehicle->body->setFriction(1);
	vehicle->collision_listeners.add(this);
	vehicle->body->setUserPointer(vehicle);
	vec3 cam = App->scene_intro->checkopints.at(0).data->GetPos();
	float* pos = App->scene_intro->checkopints.at(0).data->transform.M;
	vehicle->SetTransform(pos);
	vehicle->SetPos(cam.x, cam.y, cam.z);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	//vehicle->body->~btRigidBody();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	positionCM = vehicle->body->getCenterOfMassPosition();
	brake = 2.5f;
	turn = acceleration = 0.0f;
	AssistDirection(90.0f);
	vehicle->vehicle->getChassisWorldTransform();
	{
		btQuaternion q = vehicle->vehicle->getChassisWorldTransform().getRotation();

		cubeSensor.SetPos(positionCM.getX(), positionCM.getY() - 0.75, positionCM.getZ());
		vehicle->vehicle->getChassisWorldTransform().getOpenGLMatrix(&cubeSensor.transform);
		btVector3 offset(0, -0.75, 0);
		offset = offset.rotate(q.getAxis(), q.getAngle());

		cubeSensor.transform.M[12] += offset.getX();
		cubeSensor.transform.M[13] += offset.getY();
		cubeSensor.transform.M[14] += offset.getZ();
		float* pos = cubeSensor.transform.M;
		bodySensor->SetTransform(pos);
		sensorV->SetTransform(pos);
		//sensorV->SetPos(cubeSensor.GetPos().x, cubeSensor.GetPos().y, cubeSensor.GetPos().z);
		//cubeSensor.Render();
	}
	
	if (vehicle->body->getCenterOfMassPosition().getY() < 0) falling = true;
	if (vehicle->body->getCenterOfMassPosition().getY() < -10) reset = true;
	if (falling)
	{
		App->audio->PlayFx(dead);
		falling = false;
	}

	CheckPoints();

	vehicle->SetColor( color);
	color.Set(1.0f, 1.0f, 1.0f, 1.0f);
	forwardVector = vehicle->vehicle->getForwardVector().normalize();
	//btVector3 per = { q.getAxis().getX() ,q.getAxis().getY() ,q.getAxis().getZ() };
	perpendicularVector = { -forwardVector.getZ(), forwardVector.getY(), forwardVector.getX() };

	if (App->physics->GetCollisions())
	{
		vehicle->state = State::IDLE;
		isJumped = false;
		//LOG("%d", vehicle->state);
	} 
	else
	{
		//vehicle->state = State::IN_AIR;
	}
	if(!App->GetDebugMode())PlayerControls();

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);
	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	CameraPlayer();

	return UPDATE_CONTINUE;
}

void ModulePlayer::PlayerControls()
{

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && vehicle->state != State::IN_AIR && !isJumped)
	{
		vehicle->state = State::IN_AIR;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,+30000,0 });
	}

	//if (!vehicle->state == State::IN_AIR) vehicle->state = IDLE;



	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT &&
		(vehicle->state != State::IN_AIR || vehicle->state == State::TURBO) &&
		App->input->GetKey(SDL_SCANCODE_S) != KEY_REPEAT)
	{
		vel = MAX_ACCELERATION * 2;
		vehicle->state = TURBO;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-99,0 });

		//vehicle->body->applyTorque(per * 80);

	}
	else
	{
		vel = MAX_ACCELERATION;
		if (vehicle->state != State::IN_AIR)vehicle->state = State::IDLE;

	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (vehicle->state != State::TURBO && vehicle->state != State::IN_AIR)vehicle->state = State::WALK;
		vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-70,0 });

		if (vehicle->vehicle->getCurrentSpeedKmHour() <= -1)
		{
			brake = BRAKE_POWER / 1.5f;
			color.Set(1.0f, 0.0f, 0.0f, 1.0f);
			vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-200,0 });
		}
		else
			acceleration = vel;
		vehicle->body->applyTorque(perpendicularVector * -40);

		//if (vehicle->body->getVelocityInLocalPoint(vehicle->body->getCenterOfMassPosition()).length() >150)
		//{
		//	vehicle->body->setLinearVelocity({0,0,0});

		//}
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (vehicle->state != State::TURBO && vehicle->state != State::IN_AIR)vehicle->state = State::WALK;

		if (vehicle->vehicle->getCurrentSpeedKmHour() > +1)
		{
			brake = BRAKE_POWER / 1.5f;
			color.Set(1.0f, 0.0f, 0.0f, 1.0f);
			vehicle->vehicle->getRigidBody()->applyCentralForce({ 0,-200,0 });
		}
		else
			acceleration = vel * -1;
		vehicle->body->applyTorque(perpendicularVector * 80);


	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += (TURN_DEGREES)-assistDirection;
		brake = 15;

		if (vehicle->state == State::IN_AIR)
		{
			vehicle->body->applyTorque(forwardVector * -45);
		}
		else
		{
			vehicle->body->applyTorque(forwardVector * -200);
			//	vehicle->vehicle->getRigidBody()->applyCentralForce({ 1000,0,0 });

		}

	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= (TURN_DEGREES)-assistDirection;
		brake = 15;

		if (vehicle->state == State::IN_AIR)
		{
			vehicle->body->applyTorque(forwardVector * 45);
		}
		else
		{
			vehicle->body->applyTorque(forwardVector * 200);
			//vehicle->vehicle->getRigidBody()->applyCentralForce({ -1000,0,0 });

		}
		//LOG("%d ", (int)vehicle->body->getTotalTorque().length());
	}
}

void ModulePlayer::CheckPoints()
{
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		vec3 cam = App->camera->Position;
		vehicle->SetPos(cam.x, cam.y - 5, cam.z);
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN|| reset) Teleport(0);
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) Teleport(1);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) Teleport(2);
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) Teleport(3);
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) Teleport(4);
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) Teleport(5);
	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) Teleport(6);
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) Teleport(7);
}

void ModulePlayer::Teleport(int num)
{
	reset = false;
	vehicle->body->setLinearVelocity({ 0,0,0 });
	vehicle->body->setAngularVelocity({ 0,0,0 });
	vec3 cam = App->scene_intro->checkopints.at(num).data->GetPos();
	float* pos = App->scene_intro->checkopints.at(num).data->transform.M;
	vehicle->SetTransform(pos);
	vehicle->SetPos(cam.x, cam.y, cam.z);
}

void ModulePlayer::CameraPlayer()
{
	if (!App->GetDebugMode())
	{
		vec3 myCamera;
		vec3 myCameraLook;
		float distanceCamara2CM = -12;


		if (((camLoop.x - 36) < positionCM.getX() && (camLoop.x + 36) > positionCM.getX()) 
			&& (((camLoop.y - 54) < positionCM.getY() && (camLoop.y + 54) > positionCM.getY())) 
			&& (((camLoop.z - 54) < positionCM.getZ() && (camLoop.z + 54) > positionCM.getZ())) )
		{
			myCamera = camLoop;
		}
		else
		{
			myCamera.x = positionCM.getX() + forwardVector.getX() * distanceCamara2CM;
			myCamera.y = positionCM.getY() + forwardVector.getY() + 6;
			myCamera.z = positionCM.getZ() + forwardVector.getZ() * distanceCamara2CM;
		}
	


		myCameraLook.x = vehicle->body->getCenterOfMassPosition().getX();
		myCameraLook.y = vehicle->body->getCenterOfMassPosition().getY() + 4;
		myCameraLook.z = vehicle->body->getCenterOfMassPosition().getZ();
		if(App->input->GetKey(SDL_SCANCODE_P)== KEY_DOWN)LOG("Position Player \n x: %f \t z: %f ", myCamera.x, myCamera.z);

		App->camera->Position = myCamera;
		App->camera->LookAt(myCameraLook);
	}
}

void ModulePlayer::AssistDirection(float hardness)
{
	float turnDegrees = (TURN_DEGREES / DEGTORAD);
	calculate = (vehicle->GetKmh() / 16) * (hardness/100.0f);
	if (calculate <= turnDegrees-5)
		assistDirection = calculate * DEGTORAD;
	else assistDirection = (turnDegrees-5) * DEGTORAD;

}
void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

	if ((body1 == sensorV || body2 == sensorV) && (body1 != vehicle && body2 != vehicle))
	{

	}

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



