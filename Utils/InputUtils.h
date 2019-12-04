#pragma once

#include <string>
#include <vector>

namespace Utils
{
	std::string GetFileContentsAsString(const std::string& filePath);
	std::vector<std::string> SplitStringByDelimiter(const std::string& string, const std::string& delimiter);
}