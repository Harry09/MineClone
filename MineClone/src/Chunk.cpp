#include "Chunk.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <FastNoise.h>

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

#include "World.hpp"

Chunk::Chunk(World& world, const glm::ivec3& pos, const std::vector<std::vector<int>>& heightMap, TextureMap& textureMap)
	: _world(world), _pos(pos)
{
	auto mat = _data.getMatrix();
	mat = glm::translate(mat, glm::vec3(pos * Chunk::Size));
	_data.setMatrix(mat);

	_data.setTexture(textureMap.getTexture());

	auto yy = pos.y * Chunk::Size.y;

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			auto xx = x + pos.x * Chunk::Size.x;
			auto zz = z + pos.z * Chunk::Size.z;

			auto height = heightMap[xx][zz];
			auto height_ = height;

			// is under chunk
			if (height < yy)
			{
				continue;
			}

			// is in chunk
			if (height < yy + 16)
			{
				height_ = height - yy;

				placeBlock<GrassBlock>(glm::ivec3{ x, height_, z });
			}
			else // is above chunk
			{
				height_ = 16;
			}

			// fill rest
			for (int y = 0; y < height_; y++)
			{
				// if current block is at least 4 block beneath the top
				if (height - (y + yy) > 4)
				{
					placeBlock<StoneBlock>(glm::ivec3{ x, y, z });
				}
				else
				{
					placeBlock<DirtBlock>(glm::ivec3{ x, y, z });
				}
			}
		}
	}
}

Block* Chunk::getNeighbourOfBlock(const Block* block, BlockSide side) const
{
	auto& blockPos = block->getPosition();

	switch (side)
	{
		case BlockSide::North:
		{
			auto pos = blockPos + glm::ivec3{ 0, 0, -1 };

			if (pos.z < 0)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ 0, 0, -1 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ pos.x, pos.y, Size.z - 1 });
			}

			return getBlock(pos);
		} break;
		case BlockSide::East:
		{
			auto pos = blockPos + glm::ivec3{ 1, 0, 0 };

			if (pos.x >= Size.x)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ 1, 0, 0 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ 0, pos.y, pos.z });
			}

			return getBlock(pos);
		} break;
		case BlockSide::South:
		{
			auto pos = blockPos + glm::ivec3{ 0, 0, 1 };

			if (pos.z >= Size.z)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ 0, 0, 1 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ pos.x, pos.y, 0 });
			}

			return getBlock(pos);
		} break;
		case BlockSide::West:
		{
			auto pos = blockPos + glm::ivec3{ -1, 0, 0 };

			if (pos.x < 0)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ -1, 0, 0 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ Size.x - 1, pos.y, pos.z });
			}

			return getBlock(pos);
		} break;
		case BlockSide::Top:
		{
			auto pos = blockPos + glm::ivec3{ 0, 1, 0 };

			if (pos.y >= Size.y)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ 0, 1, 0 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ pos.x, 0, pos.z });
			}

			return getBlock(pos);
		} break;
		case BlockSide::Bottom:
		{
			auto pos = blockPos + glm::ivec3{ 0, -1, 0 };

			if (pos.y < 0)
			{
				auto neighbour = _world.getChunk(_pos + glm::ivec3{ 0, -1, 0 });

				if (neighbour == nullptr)
					return nullptr;

				return neighbour->getBlock({ pos.x, Size.y + 1, pos.z });
			}

			return getBlock(pos);
		} break;
	}

	return nullptr;
}

void Chunk::generateMesh(TextureMap& textureMap)
{
	std::vector<Vertex> data;
	data.reserve(36 * _blockCount);

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				auto block = _blocks[x][y][z].get();

				if (block != nullptr)
				{
					auto vertices = block->getVertices<
						BlockSide::North, 
						BlockSide::East, 
						BlockSide::South, 
						BlockSide::West, 
						BlockSide::Top, 
						BlockSide::Bottom>(textureMap);

					data.insert(data.end(), vertices.begin(), vertices.end());
				}
			}
		}
	}

	printf("Predicted size: %d, Real size: %lld\n", 36 * _blockCount, data.size());
	_data.resize(data.size());
	_data.setVertices(0, data.data(), data.size());
	_data.update();
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	_data.draw(shaderProgram);
}
