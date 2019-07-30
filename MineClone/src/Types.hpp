#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace coords
{
	// x, z
	using ChunkPos = glm::ivec2;

	// Pos of single Chunk's segment
	using ChunkSegmentPos = glm::ivec3;

	// block's pos in chunk. Range: (0-15)
	using LocalPos = glm::ivec3;

	// Block's pos in world
	using WorldPos = glm::ivec3;
}
