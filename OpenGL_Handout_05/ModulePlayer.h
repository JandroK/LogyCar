#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Color.h"


struct PhysVehicle3D;

#define MAX_ACCELERATION 400.0f
#define TURN_DEGREES 17.0f * DEGTORAD
#define BRAKE_POWER 50.0f



class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void CameraPlayer();
	void AssistDirection(float hardness);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	//btVector3 Norm(btVector3 vec);

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool isJumped=false;

	Cube cubeSensor;
	PhysBody3D* bodySensor;

private:

	btVector3 forwardVector;
	int vel;
	float assistDirection;
	float calculate;
	bool CPactive = false;
	Color color;
};