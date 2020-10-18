#include "Ramp.h"
#include "Util.h"

Ramp::Ramp()
{
	// original ramp dimensions
	position = { 10, 470 };
	run = 400;
	rise = 300;
	refresh();
}

Ramp::~Ramp() {}

void Ramp::refresh()
{
	hyp = sqrt(rise * rise + run * run);
	endPoint = position.x + run;
	angle = asin(rise / hyp);
}
