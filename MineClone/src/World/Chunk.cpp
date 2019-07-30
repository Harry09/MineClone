#include "Chunk.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <FastNoise.h>

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

#include "World.hpp"

Chunk::Chunk(World& world, const glm::ivec3& pos, FastNoise& noise, TextureAtlas& textureAtlas)
	: _world(world), _pos(pos)
{
	_data.move(glm::vec3(pos * Chunk::Size));
	_data.setTexture(textureAtlas.getTexture());

	auto yy = pos.y * Chunk::Size;

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			auto worldPos = glm::vec3(World::getWorldPos({ x, 0, z }, _pos));
			auto height = static_cast<int>((noise.GetNoise(worldPos.x, worldPos.z) + 0.8f) * 16);
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

	initOutline();
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
}

void Chunk::drawChunks(ShaderProgram& shaderProgram)
{
	_data.draw(shaderProgram);
}

void Chunk::drawGrid(ShaderProgram& shaderProgram)
{
	_outline.draw(shaderProgram);
}

bool Chunk::outOfBound(const glm::ivec3& pos)
{
	if (pos.x < 0 ||
		pos.x > Size - 1 ||
		pos.y < 0 ||
		pos.y > Size - 1 ||
		pos.z < 0 ||
		pos.z > Size - 1)
	{
		return true;
	}

	return false;
}

void Chunk::initOutline()
{
	auto mat = _outline.getMatrix();
	mat = glm::translate(mat, glm::vec3(Chunk::Size * _pos));
	_outline.setMatrix(mat);

	// top
	_outline[0] =  Vertex{ { -0.5f, 15.5f, -0.5f } };
	_outline[1] =  Vertex{ { 15.5f, 15.5f, -0.5f } };
				   
	_outline[2] =  Vertex{ { 15.5f, 15.5f, -0.5f } };
	_outline[3] =  Vertex{ { 15.5f, 15.5f, 15.5f } };
				   
	_outline[4] =  Vertex{ { 15.5f, 15.5f, 15.5f } };
	_outline[5] =  Vertex{ { -0.5f, 15.5f, 15.5f } };
				   
	_outline[6] =  Vertex{ { -0.5f, 15.5f, 15.5f } };
	_outline[7] =  Vertex{ { -0.5f, 15.5f, -0.5f } };
				   
	// bottom
	_outline[8] =  Vertex{ { -0.5f, -0.5f, -0.5f } };
	_outline[9] =  Vertex{ { 15.5f, -0.5f, -0.5f } };

	_outline[10] = Vertex{ { 15.5f, -0.5f, -0.5f } };
	_outline[11] = Vertex{ { 15.5f, -0.5f, 15.5f } };

	_outline[12] = Vertex{ { 15.5f, -0.5f, 15.5f } };
	_outline[13] = Vertex{ { -0.5f, -0.5f, 15.5f } };

	_outline[14] = Vertex{ { -0.5f, -0.5f, 15.5f } };
	_outline[15] = Vertex{ { -0.5f, -0.5f, -0.5f } };

	// poles
	_outline[16] = Vertex{ { -0.5f, -0.5f, -0.5f } };
	_outline[17] = Vertex{ { -0.5f, 15.5f, -0.5f } };

	_outline[18] = Vertex{ { 15.5f, -0.5f, -0.5f } };
	_outline[19] = Vertex{ { 15.5f, 15.5f, -0.5f } };

	_outline[20] = Vertex{ { 15.5f, -0.5f, 15.5f } };
	_outline[21] = Vertex{ { 15.5f, 15.5f, 15.5f } };

	_outline[22] = Vertex{ { -0.5f, -0.5f, 15.5f } };
	_outline[23] = Vertex{ { -0.5f, 15.5f, 15.5f } };
}
