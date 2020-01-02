#pragma once

class World;
class Chunk;

class IWorldGenerator
{
public:
	IWorldGenerator()
	{

	}

	virtual void generateChunk(World& world, Chunk& chunk) = 0;
};
