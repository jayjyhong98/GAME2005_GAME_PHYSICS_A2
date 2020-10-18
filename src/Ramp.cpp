#include "Ramp.h"
#include "Util.h"

Ramp::Ramp()
{
	// original ramp dimensions
	position = { 150, 470 };
	run = 400;
	rise = 300;
	refresh();
	std::cout << angle * Util::Rad2Deg;
}

Ramp::~Ramp()
{
}

void Ramp::refresh()
{
	hyp = sqrt(rise * rise + run * run);
	endPoint = position.x + run;
	angle = atan(rise / run);
}
