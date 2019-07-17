#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
	glm::vec3 position { 0.f };
	glm::vec3 color { 1.f };
	glm::vec2 texCoord { 0.f };

	// constructor
	constexpr Vertex() noexcept = default;
	constexpr Vertex(const glm::vec3& position)
		:
		position(position)
	{
	}

	constexpr Vertex(const glm::vec3& position, const glm::vec3& color)
		:
		position(position),
		color(color)
	{
	}


	constexpr Vertex(const glm::vec3& position, const glm::vec2& texCoord)
		:
		position(position),
		texCoord(texCoord)
	{
	}


	constexpr Vertex(const glm::vec3& position, const glm::vec3& color, const glm::vec2& texCoord)
		:
		position(position),
		color(color),
		texCoord(texCoord)
	{
	}

	// copy
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other) noexcept;

	// move
	Vertex(const Vertex&& other) noexcept;
	Vertex& operator=(const Vertex&& other) noexcept;
};