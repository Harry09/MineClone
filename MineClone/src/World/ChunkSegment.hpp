#pragma once

#include <vector>
#include <memory>

#include "Graphics/VertexBuffer.hpp"

#include "Blocks/Block.hpp"
#include "TextureAtlas.hpp"

class World;
class FastNoise;

class ChunkSegment
{
public:
	static constexpr int Size = 16;

private:
	using HeightMapType = std::array<std::array<int, Size>, Size>;

private:
	World& _world;

	coords::ChunkSegmentPos _chunkSegmentPos;

	VertexBuffer _data{ 0, PrimitiveType::Triangles, VertexBuffer::DrawType::Dynamic };
	std::unique_ptr<Block> _blocks[Size][Size][Size];

	VertexBuffer _outline{ 24, PrimitiveType::Lines };

	int _blockCount = 0;

public:
	ChunkSegment(World& world, const coords::ChunkSegmentPos& chunkSegmentPos, const HeightMapType& heightMap, TextureAtlas& textureAtlas);
	~ChunkSegment() = default;

	const coords::ChunkSegmentPos& getChunkSegmentPos() const { return _chunkSegmentPos; }

	template<typename T>
	Block* placeBlock(const coords::LocalPos& localPos)
	{
		if (outOfBound(localPos))
		{
			return nullptr;
		}

		static_assert(std::is_base_of_v<Block, T>, "T must inherits Block!");

		auto block = std::make_unique<T>(*this, localPos);

		auto blockPtr = block.get();

		_blocks[localPos.x][localPos.y][localPos.z] = std::move(block);

		_blockCount++;

		return blockPtr;
	}

	void removeBlock(const coords::LocalPos& localPos)
	{
		auto& block = _blocks[localPos.x][localPos.y][localPos.z];

		if (block != nullptr)
		{
			block.reset();
			_blockCount--; 
		}
	}

	Block* getBlock(const coords::LocalPos& localPos) { return _blocks[localPos.x][localPos.y][localPos.z].get(); }
	Block* getBlock(const coords::LocalPos& localPos) const { return _blocks[localPos.x][localPos.y][localPos.z].get(); }

	Block* getNeighborOfBlock(const Block* block, BlockSide side) const;

	void generateMesh(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);

private:
	static bool outOfBound(const coords::LocalPos& localPos);

	void initOutline();
};