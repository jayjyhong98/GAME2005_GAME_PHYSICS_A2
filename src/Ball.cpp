#include "Ball.h"
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
	getRigidBody()->velocity.y += getRigidBody()->acceleration.y * GRAVITY * deltaTime;
	getRigidBody()->velocity.x += getRigidBody()->acceleration.x * GRAVITY * deltaTime;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;
	getTransform()->position = pos;

	if (pos.y >= 470) // stop when reached ground level
	{
		getTransform()->position.y = 470.0f;
		setState(1);
	}
}

void Ball::setState(int x) // Here we can change current input data when new simulation is started
{
	state = x;
	if (state == 0) // in action
	{
		float accX, accY;
		accY = weight * sin(f_angle);
		accX = weight * cos(f_angle);
		getRigidBody()->acceleration = { accY , accX };
		getRigidBody()->velocity = { 0.0, 0.0 };
	}
	else if (state == 1) // stop
	{
		getRigidBody()->acceleration = { 0.0, 0.0 };
		getRigidBody()->velocity = { 0.0, 0.0 };
	}

	getRigidBody()->velocity.x = initialVel * cos(currAngle); // x component of initial power, without wind resistance 'law of inertia' says it won't change :D

	getRigidBody()->velocity.y = -initialVel * sin(currAngle); // '-power' because we want to go 'up', add total of the y-forces

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
