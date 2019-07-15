#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
	glm::vec3 position { 0.f };
	glm::vec4 color { 1.f };
	glm::vec2 texCoord { 0.f };

	// constructor
	Vertex() noexcept = default;
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, const glm::vec4& color);
	Vertex(const glm::vec3& position, const glm::vec2& texCoord);
	Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord);

	// copy
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other) noexcept;

	// move
	Vertex(const Vertex&& other) noexcept;
	Vertex& operator=(const Vertex&& other) noexcept;
};