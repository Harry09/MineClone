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

	std::unique_ptr<Block> _blocks[Size.x][Size.y][Size.z];

	Texture _texture;
	std::unique_ptr<TextureMap> _textureMap;

public:
	Chunk();
	~Chunk();

	void init();

	template<typename T>
	Block* placeBlock(const glm::ivec3& pos)
	{
		static_assert(std::is_base_of_v<Block, T>, "T must inherits Block!");

		auto block = std::make_unique<T>(pos);

		setupNeighbourhood(block.get(), pos);

		_blocks[pos.x][pos.y][pos.z] = std::move(block);

		return block.get();
	}

	void generateMesh();

	void draw(ShaderProgram& shaderProgram);

private:
	void setupNeighbourhood(Block* block, const glm::ivec3& pos);
};