#include "FileSystem.hpp"

#include <fstream>

std::string loadFileToString(const std::string& filePath) noexcept
{
	std::ifstream file(filePath);

	if (file.bad())
	{
		return "";
	}

	std::string buffer{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

	return buffer;
}