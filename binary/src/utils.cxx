
#include "utils.h"

#define NS LedsChat::Vector

NS NS::operator + (const Vector & o) const
{
	return Vector(x + o.x, y + o.y);
}

NS NS::operator += (const Vector & o)
{
	Vector & me = *this;

	me = me + o;
	return me;
}

bool NS::operator == (const Vector & o) const
{
	return x == o.x && y == o.y;
}

#undef NS

#define NS LedsChat::Directions

uint32_t NS::stringToDirection(const std::string & direction)
{
	if (direction == "up")    return 0;
	if (direction == "right") return 1;
	if (direction == "down")  return 2;
	if (direction == "left")  return 3;

	return 0;
}

float LedsChat::map(float value, float istart, float istop, float ostart, float ostop) 
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

#undef NS