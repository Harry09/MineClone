#pragma once

#include <vector>
#include <memory>

#include "Blocks/Block.hpp"

#include "Graphics/VertexBuffer.hpp"

#include "TextureAtlas.hpp"

class World;
class FastNoise;

class Chunk
{
public:
	static constexpr int Size = 16;

private:
	World& _world;

	glm::ivec3 _pos;

	VertexBuffer _data{ 0, PrimitiveType::Triangles, VertexBuffer::DrawType::Dynamic };
	std::unique_ptr<Block> _blocks[Size][Size][Size];

	VertexBuffer _outline{ 24, PrimitiveType::Lines };

	int _blockCount = 0;

public:
	Chunk(World& world, const glm::ivec3& pos, FastNoise& noise, TextureAtlas& textureAtlas);
	~Chunk() = default;

	const auto getPos() const { return _pos; }

	template<typename T>
	Block* placeBlock(const glm::ivec3& pos)
	{
		if (outOfBound(pos))
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

	void removeBlock(const glm::ivec3& pos) { _blocks[pos.x][pos.y][pos.z].reset(); _blockCount--; }

	Block* getBlock(const glm::ivec3& pos) { return _blocks[pos.x][pos.y][pos.z].get(); }
	Block* getBlock(const glm::ivec3& pos) const { return _blocks[pos.x][pos.y][pos.z].get(); }

	Block* getNeighborOfBlock(const Block* block, BlockSide side) const;

	void generateMesh(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);

private:
	static bool outOfBound(const glm::ivec3& pos);

	void initOutline();
};