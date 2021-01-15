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
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void Looping(vec3 position);
	void CylinderWalls(vec3 position);
	void Ramp();
public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/
	p2List<Cube*> looping;
	p2List<Cube*> cilinderWall;

	p2List<PhysBody3D*> lissen;
	p2List<PhysBody3D*> lisseners;


	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube ground;

	Cube Limit1;
	Cube Limit2;
	Cube Limit3;
	Cube Limit4;
	Cube wall1;
	Cube wall2;
	Cube wall3;
	Cube wall4;
	Cube wall5;
	Cube wall6;
	Cube wall7;
	Cube wall8;
	Cube wall9;
	Cube wall12;

	Cube rotationPlt1;
	Cube rotationPlt2;

	Cube wall10;
	Cube wall11;
	PhysBody3D* body;

	Cube cubeSensor;
	PhysBody3D* bodySensor;
	
	Cylinder cylinder1;


	bool win=false;

	// MapPrimitives
};
