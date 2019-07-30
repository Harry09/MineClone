#include "Coords.hpp"

#include "World/ChunkSegment.hpp"

namespace coords
{

ChunkPos getChunkPos(const WorldPos& worldPos)
{
	ChunkPos chunkPos = { worldPos.x, worldPos.z };

	// x
	if (worldPos.x < 0)
		chunkPos.x = (chunkPos.x + 1) / (ChunkSegment::Size) - 1;
	else
		chunkPos.x /= ChunkSegment::Size;

	// z
	if (worldPos.z < 0)
		chunkPos.y = (chunkPos.y + 1) / (ChunkSegment::Size) - 1;
	else
		chunkPos.y /= ChunkSegment::Size;

	return chunkPos;
}

ChunkSegmentPos getChunkSegmentPos(const WorldPos& worldPos)
{
	ChunkSegmentPos chunkSegmentPos = worldPos;

	if (worldPos.x < 0)
		chunkSegmentPos.x = (chunkSegmentPos.x + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.x /= ChunkSegment::Size;

	if (worldPos.y < 0)
		chunkSegmentPos.y = (chunkSegmentPos.y + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.y /= ChunkSegment::Size;

	if (worldPos.z < 0)
		chunkSegmentPos.z = (chunkSegmentPos.z + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.z /= ChunkSegment::Size;

	return chunkSegmentPos;
}

LocalPos getLocalPos(const WorldPos& worldPos)
{
	auto localPos = glm::abs(worldPos);

	if (worldPos.x < 0)
		localPos.x = ChunkSegment::Size - ((localPos.x - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.x %= ChunkSegment::Size;

	if (worldPos.y < 0)
		localPos.y = ChunkSegment::Size - ((localPos.y - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.y %= ChunkSegment::Size;

	if (worldPos.z < 0)
		localPos.z = ChunkSegment::Size - ((localPos.z - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.z %= ChunkSegment::Size;

	return localPos;
}

WorldPos getWorldPos(const LocalPos& localPos, const ChunkSegmentPos& chunkSegmentPos)
{
	return chunkSegmentPos * ChunkSegment::Size + localPos;
}

}
