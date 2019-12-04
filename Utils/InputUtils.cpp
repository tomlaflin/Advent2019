#include "InputUtils.h"

#include <fstream>
#include <iterator>

namespace Utils
{
	std::string GetFileContentsAsString(const std::string& filePath)
	{
		std::ifstream inputStream(filePath);
		return std::string(std::istreambuf_iterator<char>(inputStream), {});
	}

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
}