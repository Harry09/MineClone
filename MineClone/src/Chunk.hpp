#pragma once

#include <vector>
#include <memory>

#include "Blocks/Block.hpp"

#include "Graphics/VertexBuffer.hpp"

#include "Graphics/Texture.hpp"
#include "TextureMap.hpp"

class Chunk
{
public:
	static constexpr glm::ivec3 Size = { 16, 16, 16 };

private:
	std::unique_ptr<VertexBuffer> _data;

	std::vector<std::unique_ptr<Block>> _blocks;

	Texture _texture;
	std::unique_ptr<TextureMap> _textureMap;

public:
	Chunk();
	~Chunk();

	void init();

	void placeBlock(const Block& block);

	void draw(ShaderProgram& shaderProgram);
};