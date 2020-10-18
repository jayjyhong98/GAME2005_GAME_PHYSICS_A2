#include "Ball.h"
#include "Ramp.h"
#include "Util.h"
#include "TextureManager.h"
#include "EventManager.h"
using namespace std;

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/Box.png", "circle");
	
	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	initialPos = getTransform()->position = glm::vec2(275.0f, 460.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	getRigidBody()->isColliding = false;
	setType(BALL);

	GravityTime = 0.0f;
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Ball::update()
{
	rampMotion();
}

void Ball::clean()
{

}

void Ball::moveLeft() {
	m_direction.x = -1;
}

void Ball::moveRight() {
	m_direction.x = 1;
}

void Ball::moveUp() {
	m_direction.y = -1;
}

void Ball::moveDown() {
	m_direction.y = 1;
}

void Ball::stopMoving() {
	m_direction = glm::vec2(0.0f, 0.0f);
}

void Ball::projectileMotion()
{
	//GravityTime += deltaTime;
	if (!b_simulationStop)
	{
		getRigidBody()->velocity.y += GRAVITY * deltaTime;

		glm::vec2 pos = getTransform()->position;
		pos.x += getRigidBody()->velocity.x * deltaTime;
		pos.y += getRigidBody()->velocity.y * deltaTime;
		getTransform()->position = pos;

		if (pos.y >= 460)
		{
			getTransform()->position.y = 460.0f;
			b_simulationStop = true;
		}
	}
}

void Ball::rampMotion()
{
	getRigidBody()->velocity.y += getRigidBody()->acceleration.y;
	getRigidBody()->velocity.x += getRigidBody()->acceleration.x;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;
	getTransform()->position = pos;

	if (pos.y >= 470) // try to stop when reached ground level
	{
		getTransform()->position.y = 470.0f;
		setState(1);
	}

	if (getRigidBody()->velocity.x <= 0.0)  // stop moving. It should be stop at 1316m
	{
		setState(2);
	}
}

void Ball::setState(int x) // Here we can change current input data when new simulation is started
{
	state = x;
	if (state == 0) // in action
	{
		accelTotal = GRAVITY * sin(f_angle) - friction * GRAVITY * cos(f_angle);
		netForce = mass * GRAVITY * sin(f_angle) - friction * mass * GRAVITY * cos(f_angle);


		float accX, accY;
		accY = accelTotal * sin(f_angle);
		accX = accelTotal * cos(f_angle);

		getRigidBody()->acceleration = { accX , accY };
		getRigidBody()->velocity = { 0.0, 0.0 };
	}
	else if (state == 1) // when reached ground level
	{
		if (getTransform()->position.y == 470.0f)
		{
			//accel = -friction * GRAVITY
			//netForce = mass * -friction * GRAVITY

			accelGL = -friction * GRAVITY;
			netForceGL = mass * -friction * GRAVITY;

			float accXGL, accYGL;

			accXGL = accelGL;
			accYGL = 0.0f;
			getRigidBody()->acceleration = { accXGL , accYGL };
		}
	}
	else if (state == 2) //stop
	{
		getRigidBody()->acceleration = { 0.0, 0.0 };
		getRigidBody()->velocity = { 0.0, 0.0 };
	}

	b_simulationStop = false;
}

bool Ball::isColliding(GameObject* pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Ball::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}
