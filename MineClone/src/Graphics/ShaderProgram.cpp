#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
{
	_shaderProgram = glCreateProgram();
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
	glUniform1i(glGetUniformLocation(_shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(_shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, unsigned value)
{
	glUniform1ui(glGetUniformLocation(_shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(_shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(_shaderProgram, name), value.x, value.y);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(_shaderProgram, name), value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(_shaderProgram, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4x4& value)
{
	auto asdf = glGetUniformLocation(_shaderProgram, name);

	glUniformMatrix4fv(asdf, 1, false, glm::value_ptr(value));
}
