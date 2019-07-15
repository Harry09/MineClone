#include "Shader.hpp"

#include "FileSystem.hpp"

Shader::Shader(ShaderType shaderType, const std::string& shaderPath)
	: _shaderType(shaderType)
{
	_shader = glCreateShader(static_cast<GLenum>(shaderType));

	auto file = loadFileToString(shaderPath);

	auto source = file.c_str();

	glShaderSource(_shader, 1, &source, nullptr);
	glCompileShader(_shader);
}

Shader::Shader(Shader& other) noexcept
	: 
	_shader(other._shader),
	_shaderType(other._shaderType)
{
}

Shader& Shader::operator=(Shader& other) noexcept
{
	_shader = other._shader;
	_shaderType = other._shaderType;

	return *this;
}

Shader::Shader(Shader&& other) noexcept
	:
	_shader(std::move(other._shader)),
	_shaderType(std::move(other._shaderType))
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	_shader = std::move(other._shader);
	_shaderType = std::move(other._shaderType);

	return *this;
}

Shader::~Shader()
{
	glDeleteShader(_shader);
}

bool Shader::isValid() const
{
	int success;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	printf("Valid: %d\n", success);

	return success;
}

std::string Shader::getInfoLog() const
{
	char buffer[512];

	glGetShaderInfoLog(_shader, 512, nullptr, buffer);

	return std::string(buffer);
}

GLuint Shader::getNativeHandle() const
{
	return _shader;
}
