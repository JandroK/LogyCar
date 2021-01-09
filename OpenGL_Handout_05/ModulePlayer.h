#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 450.0f
#define TURN_DEGREES 18.0f * DEGTORAD
#define BRAKE_POWER 150.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void AssistDirection(float hardness);
	bool CleanUp();
	btVector3 Norm(btVector3 vec);

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool isJumped=false;

private:

	btVector3 forwardVector;
	btVector3 aux;
	int vel;
	float assistDirection;
	float calculate;
	bool CPactive = false;
};