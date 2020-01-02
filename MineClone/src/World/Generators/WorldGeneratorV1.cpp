#include "WorldGeneratorV1.hpp"

#include <memory>

#include "World/World.hpp"
#include "World/Chunk/Chunk.hpp"
#include "World/Chunk/ChunkSegment.hpp"

#include "World/Blocks/DirtBlock.hpp"
#include "World/Blocks/GrassBlock.hpp"
#include "World/Blocks/StoneBlock.hpp"

WorldGeneratorV1::WorldGeneratorV1(World& world)
	: IWorldGenerator(world)
{
	noise.SetNoiseType(FastNoise::NoiseType::Simplex);
	noise.SetFrequency(0.01f);
}

Chunk* WorldGeneratorV1::generateChunk(coords::ChunkPos&& chunkPos)
{
	Chunk* chunk = new Chunk(chunkPos);

	for (int i = 0; i < Chunk::Height; i++)
	{
		auto segment = std::make_unique<ChunkSegment>(_world, coords::ChunkSegmentPos{ chunkPos.x, i, chunkPos.y }, _world.getTextureAtlas());

		generateChunkSegment({ chunkPos.x, i, chunkPos.y }, *segment);

		chunk->addChunkSegment(std::move(segment));
	}

	return chunk;
}

void WorldGeneratorV1::generateChunkSegment(const coords::ChunkSegmentPos& segmentPos, ChunkSegment& segment)
{
	auto yy = segmentPos.y * ChunkSegment::Size;

	for (int x = 0; x < ChunkSegment::Size; x++)
	{
		for (int z = 0; z < ChunkSegment::Size; z++)
		{
			float blockPosX = static_cast<float>(x + segmentPos.x * ChunkSegment::Size);
			float blockPosZ = static_cast<float>(z + segmentPos.z * ChunkSegment::Size);

			const auto constHeight = static_cast<int>((noise.GetNoise(blockPosX, blockPosZ) + 0.8f) * 16);
			auto height = constHeight;

			// is under chunk
			if (constHeight < yy)
			{
				continue;
			}

			// is in chunk
			if (constHeight < yy + 16)
			{
				height = constHeight - yy;

				segment.placeBlock<GrassBlock>(coords::LocalPos{x, height, z});
			}
			else // is above chunk
			{
				height = 16;
			}

			// fill rest
			for (int y = 0; y < height; y++)
			{
				// if current block is at least 4 block beneath the top
				if (constHeight - (y + yy) > 4)
				{
					segment.placeBlock<StoneBlock>(coords::LocalPos{ x, y, z });
				}
				else
				{
					segment.placeBlock<DirtBlock>(coords::LocalPos{ x, y, z });
				}
			}
		}
	}
}
