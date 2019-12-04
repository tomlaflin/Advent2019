#include "VisitedCoordinate.h"
#include "Utils/InputUtils.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

bool AllSetsHaveMoreCoordinates(
	const std::vector<std::vector<VisitedCoordinate>>& coordinateSets,
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
	const std::vector<std::vector<VisitedCoordinate>>& coordinateSets,
	const std::vector<size_t>& indicesPerSet)
{
	const VisitedCoordinate& coordinateToMatch = coordinateSets[0][indicesPerSet[0]];
	for (size_t setIndex = 1; setIndex < coordinateSets.size(); setIndex++)
	{
		const VisitedCoordinate& otherCoordinate = coordinateSets[setIndex][indicesPerSet[setIndex]];
		if (otherCoordinate.x != coordinateToMatch.x || otherCoordinate.y != coordinateToMatch.y)
		{
			return false;
		}
	}

	return true;
}

void IncrementIndexOfLeastCoordinate(
	const std::vector<std::vector<VisitedCoordinate>>& coordinateSets,
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

std::uint32_t TotalStepsTaken(const std::vector<VisitedCoordinate>& visits)
{
	std::uint32_t totalStepsTaken = 0;

	for (const auto& visit : visits)
	{
		totalStepsTaken += visit.stepsTaken;
	}

	return totalStepsTaken;
}

int main()
{
	std::vector<std::vector<VisitedCoordinate>> visitedCoordinateSets;

	std::string inputString = Utils::GetFileContentsAsString("input.txt");
	std::vector<std::string> inputLines = Utils::SplitStringByDelimiter(inputString, "\n");

	for (const std::string& line : inputLines)
	{
		visitedCoordinateSets.emplace_back();
		VisitedCoordinate currentPosition{ 0, 0, 0 };

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
					currentPosition.stepsTaken++;
					visitedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'R':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.x++;
					currentPosition.stepsTaken++;
					visitedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'D':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.y--;
					currentPosition.stepsTaken++;
					visitedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			case 'U':
				for (std::uint32_t moves = 0; moves < distanceToMove; moves++)
				{
					currentPosition.y++;
					currentPosition.stepsTaken++;
					visitedCoordinateSets.back().push_back(currentPosition);
				}
				break;
			default:
				break;
			}
		}
	}

	for (auto& vector : visitedCoordinateSets)
	{
		std::sort(vector.begin(), vector.end());
		auto lastUniqueIter = std::unique(
			vector.begin(),
			vector.end(),
			[](const VisitedCoordinate& lhs, const VisitedCoordinate& rhs)
			{
				return lhs.x == rhs.x && lhs.y == rhs.y;
			});

		vector.erase(lastUniqueIter, vector.end());
	}

	std::vector<size_t> indicesPerSet(visitedCoordinateSets.size(), 0);
	std::vector<std::vector<VisitedCoordinate>> intersectedCoordinates;

	while (true)
	{
		if (!AllSetsHaveMoreCoordinates(visitedCoordinateSets, indicesPerSet))
		{
			break;
		}

		if (AllSetsIntersectAtCurrentCoordinate(visitedCoordinateSets, indicesPerSet))
		{
			intersectedCoordinates.emplace_back();
			for (size_t setIndex = 0; setIndex < visitedCoordinateSets.size(); setIndex++)
			{
				intersectedCoordinates.back().push_back(visitedCoordinateSets[setIndex][indicesPerSet[setIndex]]);
			}

			const VisitedCoordinate& intersectionCoordinate = intersectedCoordinates.back()[0];
			std::cout
				<< "Intersection point found at ("
				<< intersectionCoordinate.x
				<< ", "
				<< intersectionCoordinate.y
				<< ")."
				<< std::endl;
		}

		IncrementIndexOfLeastCoordinate(visitedCoordinateSets, indicesPerSet);
	}

	if (!intersectedCoordinates.empty())
	{
		std::sort(
			intersectedCoordinates.begin(),
			intersectedCoordinates.end(),
			[](const std::vector<VisitedCoordinate>& lhs, const std::vector<VisitedCoordinate>& rhs)
			{
				return TotalStepsTaken(lhs) < TotalStepsTaken(rhs);
			});

		const VisitedCoordinate& intersectionCoordinate = intersectedCoordinates.front().front();
		std::cout
			<< "The point with the fewest total steps taken is ("
			<< intersectionCoordinate.x
			<< ", "
			<< intersectionCoordinate.y
			<< "), with "
			<< TotalStepsTaken(intersectedCoordinates.front())
			<< " steps taken."
			<< std::endl;
	}
	
	return 0;
}