#include "Vertex.hpp"

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

Vertex::Vertex(Vertex&& other) noexcept
	: 
	position(std::move(other.position)), 
	color(std::move(other.color)),
	texCoord(std::move(other.texCoord))
{
}

Vertex& Vertex::operator=(Vertex&& other) noexcept
{
	position = std::move(other.position);
	color = std::move(other.color);
	texCoord = std::move(other.texCoord);

	return *this;
}
