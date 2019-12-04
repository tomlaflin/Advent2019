#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Utils/InputUtils.h"

void ProcessValues(std::vector<std::uint64_t>& values)
{
	for (size_t commandIndex = 0; ; commandIndex += 4)
	{
		size_t firstOperandIndex = values[commandIndex + 1];
		size_t secondOperandIndex = values[commandIndex + 2];
		size_t destinationIndex = values[commandIndex + 3];

		switch (values[commandIndex])
		{
		case 1:
			values[destinationIndex] = values[firstOperandIndex] + values[secondOperandIndex];
			break;
		case 2:
			values[destinationIndex] = values[firstOperandIndex] * values[secondOperandIndex];
			break;
		case 99:
			return;
		default:
			break;
		}
	}
}

int main()
{
	std::string inputString = Utils::GetFileContentsAsString("input.txt");
	std::vector<std::string> tokenizedInput = Utils::SplitStringByDelimiter(inputString, ",");
	std::vector<std::uint64_t> values;
	std::transform(
		tokenizedInput.begin(),
		tokenizedInput.end(),
		std::back_inserter(values),
		[](const std::string& string)
		{
			return std::stoull(string);
		});

	ProcessValues(values);
	
	for (const auto& value : values)
	{
		std::cout << value << std::endl;
	}

	return 0;
}