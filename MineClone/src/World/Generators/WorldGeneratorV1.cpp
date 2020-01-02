#include "WorldGeneratorV1.hpp"

#include <memory>

#include "World/World.hpp"
#include "World/Chunk/Chunk.hpp"
#include "World/Chunk/ChunkSegment.hpp"

#include "World/Blocks/DirtBlock.hpp"
#include "World/Blocks/GrassBlock.hpp"
#include "World/Blocks/StoneBlock.hpp"

WorldGeneratorV1::WorldGeneratorV1()
{
	noise.SetNoiseType(FastNoise::NoiseType::Simplex);
	noise.SetFrequency(0.01f);
}

void WorldGeneratorV1::generateChunk(World& world, Chunk& chunk)
{
	auto chunkPos = chunk.getChunkPos();

	for (int i = 0; i < Chunk::Height; i++)
	{
		auto segment = std::make_unique<ChunkSegment>(world, coords::ChunkSegmentPos{ chunkPos.x, i, chunkPos.y }, world.getTextureAtlas());

		generateChunkSegment(chunkPos, *segment);

		chunk.addChunkSegment(std::move(segment));


	}
}

void WorldGeneratorV1::generateChunkSegment(const coords::ChunkPos& chunkPos, ChunkSegment& segment)
{
	auto yy = chunkPos.y * ChunkSegment::Size;

	for (int x = 0; x < ChunkSegment::Size; x++)
	{
		for (int z = 0; z < ChunkSegment::Size; z++)
		{
			float xx = static_cast<float>(x + chunkPos.x * ChunkSegment::Size);
			float zz = static_cast<float>(z + chunkPos.y * ChunkSegment::Size);

			const auto constHeight = static_cast<int>((noise.GetNoise(xx, zz) + 0.8f) * 16);
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
