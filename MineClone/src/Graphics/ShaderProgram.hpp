﻿#pragma once
#include <type_traits>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Shader.hpp"

class ShaderProgram
{
private:
	unsigned _shaderProgram;

	std::unordered_map<std::string, unsigned> _uniformLocations;

public:
	// remember to call create() method before linking shaders!
	ShaderProgram();

	ShaderProgram(const ShaderProgram& other) noexcept;
	ShaderProgram& operator=(const ShaderProgram& other) noexcept;

	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	template<typename... Ts>
	ShaderProgram(Ts... ts) : ShaderProgram()
	{
		create();
		linkShaders(ts...);
	}

	void create();

	void use();
	bool isValid();

	void setUniform(const char* name, bool value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, unsigned value);
	void setUniform(const char* name, float value);
	void setUniform(const char* name, const glm::vec2& value);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const glm::vec4& value);
	void setUniform(const char* name, const glm::mat4x4& value);

	template<typename... Ts>
	void linkShaders(Ts... ts)
	{
		static_assert((std::is_same_v<Shader, Ts> && ...), "All Ts must be exactly Shader");

		(glAttachShader(_shaderProgram, ts.getNativeHandle()), ...);

		glLinkProgram(_shaderProgram);

		(glDetachShader(_shaderProgram, ts.getNativeHandle()), ...);
	}

private:
	unsigned getUniformLocation(const char* name);
};
