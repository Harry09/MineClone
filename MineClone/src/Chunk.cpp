#include "Chunk.hpp"

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::init()
{
	_texture.loadFromFile("textures.jpg");

	_textureMap = std::make_unique<TextureMap>(_texture, 16);

	_data = std::make_unique<VertexBuffer>(6 * 6 * Size.x * Size.y * Size.z + 1, PrimitiveType::Triangles);
	_data->setTexture(_texture);
	
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				placeBlock<DirtBlock>(glm::ivec3{ x, y, z });
			}
		}
	}

	generateMesh();
}

void Chunk::generateMesh()
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
						Block::BlockSide::North, 
						Block::BlockSide::East, 
						Block::BlockSide::South, 
						Block::BlockSide::West, 
						Block::BlockSide::Top, 
						Block::BlockSide::Bottom>(*_textureMap);

					_data->setVertices(block->getFlatPosition(), vertices.data(), vertices.size());
				}
			}
		}
	}

	_data->update();
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	_data->draw(shaderProgram);
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
			neighbor->setNeighbor(block, Block::BlockSide::North);
			block->setNeighbor(neighbor, Block::BlockSide::South);
		}
	}

	// south
	if (pos.z > 0)
	{
		neighbor = _blocks[pos.x][pos.y][pos.z - 1].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, Block::BlockSide::South);
			block->setNeighbor(neighbor, Block::BlockSide::North);
		}
	}

	// east
	if (pos.x < 15)
	{
		neighbor = _blocks[pos.x + 1][pos.y][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, Block::BlockSide::West);
			block->setNeighbor(neighbor, Block::BlockSide::East);
		}

	}

	// west
	if (pos.x > 0)
	{
		neighbor = _blocks[pos.x - 1][pos.y][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, Block::BlockSide::East);
			block->setNeighbor(neighbor, Block::BlockSide::West);
		}
	}

	// top
	if (pos.y < 15)
	{
		neighbor = _blocks[pos.x][pos.y + 1][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, Block::BlockSide::Bottom);
			block->setNeighbor(neighbor, Block::BlockSide::Top);
		}
	}

	// bottom
	if (pos.y > 0)
	{
		neighbor = _blocks[pos.x][pos.y - 1][pos.z].get();

		if (neighbor != nullptr)
		{
			neighbor->setNeighbor(block, Block::BlockSide::Top);
			block->setNeighbor(neighbor, Block::BlockSide::Bottom);
		}
	}
}
