#pragma once

#include "Maths/Coords.hpp"

class World;
class Chunk;

class IWorldGenerator
{
protected:
	World& _world;

public:
	IWorldGenerator(World& world)
		: _world(world)
	{

	}

	virtual Chunk* generateChunk(coords::ChunkPos&& chunkPos) = 0;
};
