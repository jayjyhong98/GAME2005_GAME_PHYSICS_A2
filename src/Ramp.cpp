#include "Ramp.h"

Ramp::Ramp()
{
	// original ramp dimensions
	position = { 150, 470 };
	run = 400;
	rise = 300;
	endPoint = position.x + run;
}

Ramp::~Ramp()
{
}
