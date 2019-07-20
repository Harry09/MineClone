#pragma once

#include <vector>
#include <memory>

#include "Blocks/Block.hpp"

#include "Graphics/VertexBuffer.hpp"

#include "TextureMap.hpp"

class World;

class Chunk
{
public:
	static constexpr glm::ivec3 Size = { 16, 16, 16 };

private:
	World& _world;

	glm::ivec3 _pos;

	VertexBuffer _data{ 0, PrimitiveType::Triangles };
	std::unique_ptr<Block> _blocks[Size.x][Size.y][Size.z];

	int _blockCount = 0;

public:
	Chunk(World& world, const glm::ivec3& pos, const std::vector<std::vector<int>>& heightMap, TextureMap& textureMap);
	~Chunk() = default;

	const auto getPos() const { return _pos; }

	template<typename T>
	Block* placeBlock(const glm::ivec3& pos)
	{
		if (pos.x < 0 ||
			pos.x > Size.x - 1 ||
			pos.y < 0 ||
			pos.y > Size.y - 1 ||
			pos.z < 0 ||
			pos.z > Size.z - 1)
		{
			return nullptr;
		}

		static_assert(std::is_base_of_v<Block, T>, "T must inherits Block!");

		auto block = std::make_unique<T>(*this, pos);

		auto blockPtr = block.get();

		_blocks[pos.x][pos.y][pos.z] = std::move(block);

		_blockCount++;

		return blockPtr;
	}

	Block* getBlock(const glm::ivec3& pos) const { return _blocks[pos.x][pos.y][pos.z].get(); }

	Block* getNeighbourOfBlock(const Block* block, BlockSide side) const;

	void generateMesh(TextureMap& textureMap);

	void draw(ShaderProgram& shaderProgram);
};