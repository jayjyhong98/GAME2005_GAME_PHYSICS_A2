#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"
#include "Label.h"

class Ramp;

class Ball final : public Sprite
{
public:
	Ball();
	~Ball();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();
	void projectileMotion();
	void rampMotion();
	void setState(int x);

	bool isGravityEnabled = false;
	bool isColliding(GameObject*);
	float getDistance(GameObject*);

	inline float getf_meter() { return f_meter; } // remove ; when if defined .h
	inline void setf_meter(float m) { f_meter = m; } // m = input from users

	inline void setf_initalVel(float v) { f_initialVel = v; }// v = input from users

	inline void setFriction(float f) { friction = f; }// coefficient of friction

	inline float getAccelTotal() { return accelTotal; }// total accel
	inline float getNetForce() { return netForce; }// net force

	inline float getInitialVel() { return initialVel; } // for label

	inline float getf_angle() { return f_angle; } // remove ; when if defined .h
	inline void setf_angle(float a) { f_angle = a; }// a = input from users

	inline float getDegAngle() { return degAngle; }

	inline void setMass(float w) { mass = w; }
	inline float getMass() { return mass; }

	glm::vec2 throwSpeed;

private:
	const float deltaTime = 1.0f / 60.f;

	int state = 0;
	
	const float SPEED = 100.0f;
	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;

	const float GRAVITY = 9.8f; // set const float gravity

	float currAngle; // to calculate in case of 485m and 95m/s
	float degAngle; // to display 
	glm::vec2 initialPos;
	float initialVel;
	float maxdistance;
	float GravityTime;

	float f_angle = 36.87f, f_result; // to calculate in case of input variables from users
	float f_meter = 485.0f, f_initialVel = 95.0f; // to change total meters and initial velocity(speed)
	float f_maxdistance;
	float f_friction;

	float mass, accelTotal, netForce, friction, accelGL, netForceGL, velGL;

	bool b_simulationStop = false;

	Ramp* m_Ramp;
};

#endif /* defined (__PLAYER__) */