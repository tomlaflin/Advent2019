#include <fstream>
#include <iostream>

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

		std::cout << "Module mass: " << moduleMass;
		std::uint32_t requiredFuelForModule = moduleMass / 3 - 2;
		std::cout << ", Fuel required: " << requiredFuelForModule << "\n";
		totalRequiredFuel += requiredFuelForModule;
	}

	std::cout << "Total required fuel: " << totalRequiredFuel;
	return 0;
}