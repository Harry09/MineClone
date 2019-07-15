#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3& position)
	:
	position(position),
	color(1.f, 1.f, 1.f, 1.f),
	texCoord(0.f, 0.f)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec4& color)
	:
	position(position),
	color(color),
	texCoord(0.f, 0.f)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	:
	position(position),
	color(1.f, 1.f, 1.f, 1.f),
	texCoord(texCoord)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord)
	: 
	position(position),
	color(color),
	texCoord(texCoord)
{
}

Vertex::Vertex(const Vertex& other)
	: 
	position(other.position), 
	color(other.color),
	texCoord(other.texCoord)
{
}

Vertex& Vertex::operator=(const Vertex& other) noexcept
{
	position = other.position;
	color = other.color;
	texCoord = other.texCoord;

	return *this;
}

Vertex::Vertex(const Vertex&& other) noexcept
	: 
	position(std::move(other.position)), 
	color(std::move(other.color)),
	texCoord(std::move(other.texCoord))
{
}

Vertex& Vertex::operator=(const Vertex&& other) noexcept
{
	position = std::move(other.position);
	color = std::move(other.color);
	texCoord = std::move(other.texCoord);

	return *this;
}
