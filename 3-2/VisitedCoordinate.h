#pragma once

#include <cstdint>

struct VisitedCoordinate
{
	std::int32_t x = 0;
	std::int32_t y = 0;
	std::uint32_t stepsTaken = 0;
};

bool operator==(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs);
bool operator!=(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs);
bool operator<(const VisitedCoordinate& lhs, const VisitedCoordinate& rhs);