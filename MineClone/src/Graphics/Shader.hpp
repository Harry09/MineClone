#pragma once
#include <glad/glad.h>
#include <string>

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
};

class Shader
{
private:
	uint32_t _shader;
	ShaderType _shaderType;

public:
	Shader(ShaderType shaderType, const std::string& shaderPath);

	Shader(Shader& other) noexcept;
	Shader& operator=(Shader& other) noexcept;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	~Shader();

	bool isValid() const;
	std::string getInfoLog() const;
	GLuint getNativeHandle() const;
};