#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	void CubeMoveRender();
	void ChangeColor();
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void Looping(vec3 position);
	void CylinderWalls(vec3 position);
	void Ramp(vec3 position, vec3 size);
	void RampFlip(vec3 position, vec3 size);
	void Ramp(vec3 position,bool inverse, vec3 size);
	void MidRamp(vec3 position,bool inverse, vec3 size);
public:

	float angle;
	float radi;

	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/
	p2List<Cube*> looping;
	p2List<Cube*> cilinderWall;
	p2List<Cube*> cubes;
	p2List<PhysBody3D*> physBodyCubes;

	p2List<Cube*> checkopints;
	p2List<PhysBody3D*> physBodyCheckopints;

	p2List<PhysBody3D*> listeners;

	Cube reference; 
	Cube ground;

	Cube* cubeMove;
	PhysBody3D* cubeMovBody;
	float posMoveY;


	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	
	PhysBody3D* body;

	Cube cubeSensor;
	PhysBody3D* bodySensor;
	
	Cylinder cylinder1;

	float cX=1;
	float cY=1;
	float cZ=1;
	
	float aux;
	float increment1= 0.002f;
	float increment2 = 0.004f;
	float increment3 = 0.003f;

	bool changeColor=true;
	bool moveToUp=true;

	bool win=false;
	bool timerStarted;
	Timer* timer;

	// MapPrimitives
};
