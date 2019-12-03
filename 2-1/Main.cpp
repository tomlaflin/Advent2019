#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::string> SplitStringByDelimiter(const std::string& string, const std::string& delimiter)
{
	std::vector<std::string> result;

	size_t tokenStartPosition = 0;
	while (tokenStartPosition < string.length())
	{
		size_t tokenEndPosition = string.find(delimiter, tokenStartPosition);
		std::string token = string.substr(tokenStartPosition, tokenEndPosition - tokenStartPosition);
		tokenStartPosition += token.length() + delimiter.length();
		result.push_back(std::move(token));
	}

	return result;
}

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
	std::ifstream inputStream("input.txt");
	std::string inputString(std::istreambuf_iterator<char>(inputStream), {});

	std::vector<std::string> tokenizedInput = SplitStringByDelimiter(inputString, ",");
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