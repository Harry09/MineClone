#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(const ShaderProgram& other) noexcept
	: _shaderProgram(other._shaderProgram)
{
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other) noexcept
{
	_shaderProgram = other._shaderProgram;

	return *this;
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	: _shaderProgram(std::move(other._shaderProgram))
{
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	_shaderProgram = std::move(other._shaderProgram);

	return *this;
}

void ShaderProgram::create()
{
	_shaderProgram = glCreateProgram();
}

void ShaderProgram::use()
{
	glUseProgram(_shaderProgram);
}

bool ShaderProgram::isValid()
{
	int success;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

	return success != -1;
}

void ShaderProgram::setUniform(const char* name, bool value)
{
	glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const char* name, unsigned value)
{
	glUniform1ui(getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const char* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const char* name, const glm::vec2& value)
{
	glUniform2f(getUniformLocation(name), value.x, value.y);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& value)
{
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4x4& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, false, glm::value_ptr(value));
}

unsigned ShaderProgram::getUniformLocation(const char* name)
{
	auto location = _uniformLocations.find(name);

	if (location == _uniformLocations.end())
	{
		auto loc = glGetUniformLocation(_shaderProgram, name);

		_uniformLocations[name] = loc;

		return loc;
	}

	return (*location).second; 
}
