#pragma once

#include <vector>
#include <memory>

#include "Blocks/Block.hpp"

#include "Graphics/VertexBuffer.hpp"

#include "TextureMap.hpp"

class FastNoise;

class Chunk
{
public:
	static constexpr glm::ivec3 Size = { 16, 16, 16 };

private:
	VertexBuffer _data{ 6 * 6 * Size.x * Size.y * Size.z + 1, PrimitiveType::Triangles };
	std::unique_ptr<Block> _blocks[Size.x][Size.y][Size.z];

public:
	Chunk(const glm::ivec3& pos, const std::vector<std::vector<int>>& heightMap, TextureMap& textureMap);
	~Chunk() = default;

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

		auto block = std::make_unique<T>(pos);

		setupNeighbourhood(block.get(), pos);

		_blocks[pos.x][pos.y][pos.z] = std::move(block);

		return block.get();
	}

	Block* getBlock(int x, int y, int z) const { return _blocks[x][y][z].get(); }

	void generateMesh(TextureMap& textureMap);

	void draw(ShaderProgram& shaderProgram);

private:
	void setupNeighbourhood(Block* block, const glm::ivec3& pos);
};