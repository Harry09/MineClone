#include "ChunkSegment.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <FastNoise.h>

#include "World/Blocks/DirtBlock.hpp"
#include "World/Blocks/GrassBlock.hpp"
#include "World/Blocks/StoneBlock.hpp"

#include "World/World.hpp"

ChunkSegment::ChunkSegment(World& world, const coords::ChunkSegmentPos& chunkSegmentPos, TextureAtlas& textureAtlas)
	: _world(world), _chunkSegmentPos(chunkSegmentPos), _textureAtlas(textureAtlas.getTexture())
{
	_mesh.move(glm::vec3(chunkSegmentPos * ChunkSegment::Size));

	initOutline();
}

Block* ChunkSegment::getNeighborOfBlock(const Block* block, BlockFace face) const
{
	auto facingDirection = getBlockFaceVec(face);

	auto localPos = block->getLocalPos() + facingDirection;

	//printf("Current: %d %d %d \n", _pos.x, _pos.y, _pos.z);

	if (outOfBound(localPos))
	{
		auto worldPos = block->getWorldPos() + facingDirection;

		return _world.getBlock(worldPos);
	}

	return getBlock(localPos);
}

void ChunkSegment::generateMesh(TextureAtlas& textureAtlas)
{
	if (!_meshNeedUpdate)
		return;

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
						BlockFace::North, 
						BlockFace::East, 
						BlockFace::South, 
						BlockFace::West, 
						BlockFace::Top, 
						BlockFace::Bottom>(textureAtlas);

					data.insert(data.end(), vertices.begin(), vertices.end());
				}
			}
		}
	}

	printf("Predicted size: %lld, Used size: %lld\n", data.capacity(), data.size());

	_mesh.resize(data.size());
	_mesh.setVertices(0, data.data(), data.size());

	_meshNeedUpdate = false;
}

void ChunkSegment::drawChunks(ShaderProgram& shaderProgram)
{
	_mesh.draw(_textureAtlas, shaderProgram);
}

void ChunkSegment::drawGrid(ShaderProgram& shaderProgram)
{
	_outline.draw(shaderProgram);
}

bool ChunkSegment::outOfBound(const coords::LocalPos& localPos)
{
	if (localPos.x < 0 ||
		localPos.x > Size - 1 ||
		localPos.y < 0 ||
		localPos.y > Size - 1 ||
		localPos.z < 0 ||
		localPos.z > Size - 1)
	{
		return true;
	}

	return false;
}

void ChunkSegment::initOutline()
{
	auto mat = _outline.getMatrix();
	mat = glm::translate(mat, glm::vec3(ChunkSegment::Size * _chunkSegmentPos));
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
