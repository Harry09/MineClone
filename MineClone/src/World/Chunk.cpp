#include "Chunk.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <FastNoise.h>

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

#include "World.hpp"

Chunk::Chunk(World& world, const glm::ivec3& pos, const std::vector<std::vector<int>>& heightMap, TextureAtlas& textureAtlas)
	: _world(world), _pos(pos)
{
	auto mat = _data.getMatrix();
	mat = glm::translate(mat, glm::vec3(pos * Chunk::Size));
	_data.setMatrix(mat);

	_data.setTexture(textureAtlas.getTexture());

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


Block* Chunk::getNeighborOfBlock(const Block* block, BlockSide side) const
{
	auto facingDirection = getBlockSideDirection(side);

	auto localPos = block->getPosition() + facingDirection;

	//printf("Current: %d %d %d \n", _pos.x, _pos.y, _pos.z);

	if (outOfBound(localPos))
	{
		auto worldPos = block->getWorldPosition() + facingDirection;

		return _world.getBlock(worldPos);
	}

	return getBlock(localPos);
}

void Chunk::generateMesh(TextureAtlas& textureAtlas)
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
						BlockSide::Bottom>(textureAtlas);

					data.insert(data.end(), vertices.begin(), vertices.end());
				}
			}
		}
	}

	printf("Predicted size: %lld, Used size: %lld\n", data.capacity(), data.size());

	_data.resize(data.size());
	_data.setVertices(0, data.data(), data.size());
	_data.update();
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	_data.draw(shaderProgram);
}

bool Chunk::outOfBound(const glm::ivec3& pos)
{
	if (pos.x < 0 ||
		pos.x > Size.x - 1 ||
		pos.y < 0 ||
		pos.y > Size.y - 1 ||
		pos.z < 0 ||
		pos.z > Size.z - 1)
	{
		return true;
	}

	return false;
}
