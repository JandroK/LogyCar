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
	void PlayerControls();
	void CheckPoints();
	void Teleport(int num);
	void CameraPlayer(float dt);
	void CameraWin(float dt);
	void AssistDirection(float hardness);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	//btVector3 Norm(btVector3 vec);

public:

	PhysVehicle3D* vehicle;
	PhysVehicle3D* sensorV;
	float turn;
	float acceleration;
	float brake;
	bool isJumped=false;

	Cube cubeSensor;
	PhysBody3D* bodySensor;

private:

	Timer* jumpTime;

	btVector3 forwardVector;
	btVector3 perpendicularVector;
	int vel;
	float assistDirection;
	float calculate;
	vec3 camLoop;
	btVector3 positionCM;
	bool CPactive = false;
	bool reset = false;
	bool falling = false;
	Color color;
	//Fx
	uint dead;

	float angle = 0;
};