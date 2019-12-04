#include "Coordinate.h"
#include "Utils/InputUtils.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

bool CompareCoordinates(const Coordinate& lhs, const Coordinate& rhs)
{
	std::uint32_t lhsDistance = lhs.ManhattanDistanceFromOrigin();
	std::uint32_t rhsDistance = rhs.ManhattanDistanceFromOrigin();

	if (lhsDistance != rhsDistance)
	{
		return lhsDistance < rhsDistance;
	}
	else
	{
		return lhs < rhs;
	}
}

bool AllSetsHaveMoreCoordinates(
	const std::vector<std::vector<Coordinate>>& coordinateSets,
	const std::vector<size_t>& indicesPerSet)
{
	for (size_t setIndex = 0; setIndex < coordinateSets.size(); setIndex++)
	{
		if (indicesPerSet[setIndex] >= coordinateSets[setIndex].size())
		{
			return false;
		}
	}

	return true;
}

bool AllSetsIntersectAtCurrentCoordinate(
	const std::vector<std::vector<Coordinate>>& coordinateSets,
	const std::vector<size_t>& indicesPerSet)
{
	const Coordinate& coordinateToMatch = coordinateSets[0][indicesPerSet[0]];
	for (size_t setIndex = 1; setIndex < coordinateSets.size(); setIndex++)
	{
		if (coordinateSets[setIndex][indicesPerSet[setIndex]] != coordinateToMatch)
		{
			return false;
		}
	}

	return true;
}

void IncrementIndexOfLeastCoordinate(
	const std::vector<std::vector<Coordinate>>& coordinateSets,
	std::vector<size_t>& indicesPerSet)
{
	size_t setIndexWithLeastCoordinate = 0;
	for (size_t setIndex = 1; setIndex < coordinateSets.size(); setIndex++)
	{
		if (coordinateSets[setIndex][indicesPerSet[setIndex]]
			< coordinateSets[setIndexWithLeastCoordinate][indicesPerSet[setIndexWithLeastCoordinate]])
		{
			setIndexWithLeastCoordinate = setIndex;
		}
	}

	indicesPerSet[setIndexWithLeastCoordinate]++;
}

int main()
{
	std::vector<std::vector<Coordinate>> intersectedCoordinateSets;

	std::string inputString = Utils::GetFileContentsAsString("input.txt");
	std::vector<std::string> inputLines = Utils::SplitStringByDelimiter(inputString, "\n");

	for (const std::string& line : inputLines)
	{
		intersectedCoordinateSets.emplace_back();
		Coordinate currentPosition{ 0, 0 };

		std::vector<std::string> lineTokens = Utils::SplitStringByDelimiter(line, ",");
		for (const std::string& token : lineTokens)
		{
			std::uint32_t distanceToMove = std::stoul(token.substr(1));

			switch (token[0])
			{
			case 'L':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.x--;
					intersectedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'R':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.x++;
					intersectedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'D':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.y--;
					intersectedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'U':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.y++;
					intersectedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			default:
				break;
			}
		}
	}

	for (auto& vector : intersectedCoordinateSets)
	{
		std::sort(vector.begin(), vector.end(), &CompareCoordinates);
		auto lastUniqueIter = std::unique(vector.begin(), vector.end());
		vector.erase(lastUniqueIter, vector.end());
	}

	std::vector<size_t> indicesPerSet(intersectedCoordinateSets.size(), 0);

	while (true)
	{
		if (!AllSetsHaveMoreCoordinates(intersectedCoordinateSets, indicesPerSet))
		{
			break;
		}

		if (AllSetsIntersectAtCurrentCoordinate(intersectedCoordinateSets, indicesPerSet))
		{
			const Coordinate& intersectionCoordinate = intersectedCoordinateSets[0][indicesPerSet[0]];
			std::cout
				<< "Intersection point nearest the origin is ("
				<< intersectionCoordinate.x
				<< ", "
				<< intersectionCoordinate.y
				<< ") at Manhattan distance "
				<< intersectionCoordinate.ManhattanDistanceFromOrigin()
				<< ".\n";
			break;
		}

		IncrementIndexOfLeastCoordinate(intersectedCoordinateSets, indicesPerSet);
	}
	
	return 0;
}