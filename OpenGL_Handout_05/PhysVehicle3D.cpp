#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

	

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);
		if (i==3 || i == 2)wheel.color.Set(0.8f,0.4f,0,0.5f);
		else wheel.color = Blue;
		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	Cube chassis2(info.chassis2_size.x, info.chassis2_size.y, info.chassis2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis2.transform);
	btVector3 offset2(info.chassis2_offset.x, info.chassis2_offset.y, info.chassis2_offset.z);
	offset2 = offset2.rotate(q.getAxis(), q.getAngle());

	chassis2.transform.M[12] += offset2.getX();
	chassis2.transform.M[13] += offset2.getY();
	chassis2.transform.M[14] += offset2.getZ();

	Cube chassis3(info.chassis3_size.x, info.chassis3_size.y, info.chassis3_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis3.transform);
	btVector3 offset3(info.chassis3_offset.x, info.chassis3_offset.y, info.chassis3_offset.z);
	offset3 = offset3.rotate(q.getAxis(), q.getAngle());

	chassis3.transform.M[12] += offset3.getX();
	chassis3.transform.M[13] += offset3.getY();
	chassis3.transform.M[14] += offset3.getZ();


	chassis.Render();
	chassis2.Render();
	chassis3.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	//for(int i = 0; i < vehicle->getNumWheels(); ++i)
	//{
	//	if(info.wheels[i].drive == true)
	//	{
	//		vehicle->applyEngineForce(force, i);
	//	}
	//}
	vehicle->applyEngineForce(force, 2);
	vehicle->applyEngineForce(force, 3);

}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}