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

	void refresh(); // update details about ramp

	void setPositionX(int x) { position.x = x; }
	glm::vec2 getPosition() { return position; }

	void setRun(int r) { run = r; }
	int getRun() { return run; }

	int getEndPoint() { return endPoint; } // point position in world space

	void setRise(int r) { rise = r; }
	int getRise() { return rise; }

	float getHyp() { return hyp; }
	float getAngle() { return angle; }

private:
	glm::vec2 position;
	int run, rise;
	float hyp;
	int endPoint; // position of endpoint
	float angle;
};

#endif /* defined (__PLAYER__) */