#pragma once
#ifndef __RAMP__
#define __RAMP__

#include "Sprite.h"
#include "Label.h"

class Ramp 
{
public:
	Ramp();
	~Ramp();

	void setPositionX(int x) { position.x = x; }
	glm::vec2 getPosition() { return position; }

	void setRun(int r) { run = r; endPoint = position.x + run; }
	int getEndPoint() { return endPoint; }

	void setRise(int r) { rise = r; }
	int getRise() { return rise; }

private:
	glm::vec2 position;
	int run, rise;
	int endPoint; // position of endpoint
};

#endif /* defined (__PLAYER__) */