#pragma once

#include <cstdint>

struct Coordinate
{
	std::int32_t x = 0;
	std::int32_t y = 0;

	std::uint32_t ManhattanDistanceFromOrigin() const;
};

bool operator==(const Coordinate& lhs, const Coordinate& rhs);
bool operator!=(const Coordinate& lhs, const Coordinate& rhs);
bool operator<(const Coordinate& lhs, const Coordinate& rhs);