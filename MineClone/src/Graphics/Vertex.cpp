#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3& position)
	:
	position(position)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& color)
	:
	position(position),
	color(color)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	:
	position(position),
	texCoord(texCoord)
{
}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& color, const glm::vec2& texCoord)
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
