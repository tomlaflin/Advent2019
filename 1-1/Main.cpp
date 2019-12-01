#include <algorithm>
#include <fstream>
#include <iostream>

std::uint32_t getRequiredFuelForMass(std::uint32_t mass)
{
	std::int32_t requiredFuel = static_cast<std::int32_t>(mass / 3) - 2;
	return static_cast<std::uint32_t>(std::max(requiredFuel, 0));
}

int main()
{
	std::uint32_t totalRequiredFuel = 0;
	std::ifstream inputStream("input.txt");

	while (!inputStream.eof())
	{
		std::uint32_t moduleMass = 0;
		inputStream >> moduleMass;
		if (!inputStream.good())
		{
			continue;
		}

		std::uint32_t requiredFuel = getRequiredFuelForMass(moduleMass);
		do
		{
			totalRequiredFuel += requiredFuel;
			requiredFuel = getRequiredFuelForMass(requiredFuel);
		} while (requiredFuel > 0);
	}

	std::cout << "Total required fuel: " << totalRequiredFuel;
	return 0;
}