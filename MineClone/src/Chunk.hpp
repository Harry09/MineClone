#pragma once

#include <vector>
#include <memory>

#include "Blocks/Block.hpp"

#include "Graphics/VertexBuffer.hpp"

#include "Graphics/Texture.hpp"
#include "TextureMap.hpp"

class Chunk
{
	//VertexBuffer _data{ 4 * 6 * 16 * 16 * 16, PrimitiveType::Triangles };

	std::vector<std::unique_ptr<Block>> _blocks;

	Texture _texture;

public:
	Chunk();
	~Chunk();

	void init();

	void draw(ShaderProgram& shaderProgram);
};