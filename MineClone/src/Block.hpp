#pragma once

#include "Graphics/VertexBuffer.hpp"
#include "Graphics/ShaderProgram.hpp"

#include "TextureMap.hpp"

class Block
{
private:
	Texture _texture;

	VertexBuffer _vertexBuffer{ 4, PrimitiveType::TriangleFan };

	TextureMap _textureMap;

public:
	Block();
	~Block() = default;
	
	void draw(ShaderProgram& shader);
	void update();
};