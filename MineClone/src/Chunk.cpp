#include "Chunk.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

Chunk::Chunk(const glm::ivec3& pos, TextureMap& textureMap)
{
	auto mat = _data.getMatrix();
	mat = glm::translate(mat, glm::vec3(pos * Chunk::Size));
	_data.setMatrix(mat);

	_data.setTexture(textureMap.getTexture());

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				if (y < 10)
				{
					placeBlock<StoneBlock>(glm::ivec3{ x, y, z });
				}
				else if (y < 15)
				{
					placeBlock<DirtBlock>(glm::ivec3{ x, y, z });
				}
				else
				{
					placeBlock<GrassBlock>(glm::ivec3{ x, y, z });
				}

			}
		}
	}

	generateMesh(textureMap);
}

void Chunk::generateMesh(TextureMap& textureMap)
{
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

					_data.setVertices(block->getFlatPosition(), vertices.data(), vertices.size());
				}
			}
		}
	}

	_data.update();
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	_data.draw(shaderProgram);
}

void Chunk::setupNeighbourhood(Block* block, const glm::ivec3& pos)
{
	Block* neighbor = nullptr;

	// north
	if (pos.z < 15)
	{
		neighbor = _blocks[pos.x][pos.y][pos.z + 1].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::North);
			block->setNeighbor(neighbor, BlockSide::South);
		}
	}

	// south
	if (pos.z > 0)
	{
		neighbor = _blocks[pos.x][pos.y][pos.z - 1].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::South);
			block->setNeighbor(neighbor, BlockSide::North);
		}
	}

	// east
	if (pos.x < 15)
	{
		neighbor = _blocks[pos.x + 1][pos.y][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::West);
			block->setNeighbor(neighbor, BlockSide::East);
		}

	}

	// west
	if (pos.x > 0)
	{
		neighbor = _blocks[pos.x - 1][pos.y][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::East);
			block->setNeighbor(neighbor, BlockSide::West);
		}
	}

	// top
	if (pos.y < 15)
	{
		neighbor = _blocks[pos.x][pos.y + 1][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::Bottom);
			block->setNeighbor(neighbor, BlockSide::Top);
		}
	}

	// bottom
	if (pos.y > 0)
	{
		neighbor = _blocks[pos.x][pos.y - 1][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, BlockSide::Top);
			block->setNeighbor(neighbor, BlockSide::Bottom);
		}
	}
}
