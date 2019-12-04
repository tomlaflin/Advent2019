#include "Coordinate.h"

#include <cmath>

std::uint32_t Coordinate::ManhattanDistanceFromOrigin() const
{
	return std::labs(x) + std::labs(y);
}

bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Coordinate& lhs, const Coordinate& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Coordinate& lhs, const Coordinate& rhs)
{
	if (lhs.x != rhs.x)
	{
		return lhs.x < rhs.x;
	}
	else
	{
		return lhs.y < rhs.y;
	}
}