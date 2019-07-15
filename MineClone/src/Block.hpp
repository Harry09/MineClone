#pragma once

#include "Graphics/VertexBuffer.hpp"
#include "Graphics/ShaderProgram.hpp"

class Block
{
private:
	Texture _texture;

	VertexBuffer _vertexBuffer;

public:
	Block();
	~Block() = default;
	
	void draw(ShaderProgram& shader);
};