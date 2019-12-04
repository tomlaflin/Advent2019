#include "VisitedCoordinate.h"

#include <cmath>

bool operator==(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.stepsTaken == rhs.stepsTaken;
}
bool operator!=(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs)
{
	if (lhs.x != rhs.x)
	{
		return lhs.x < rhs.x;
	}
	else if (lhs.y != rhs.y)
	{
		return lhs.y < rhs.y;
	}
	else
	{
		return lhs.stepsTaken < rhs.stepsTaken;
	}
}