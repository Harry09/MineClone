#include <array>
#include <World/World.hpp>
#include <gtest/gtest.h>
#include "Game.hpp"

TEST(World, ChunkPos) {
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			glm::ivec3 chunkPos = { i, i, i };
			glm::ivec3 localPos = { j, j, j };
			glm::ivec3 worldPos = World::getWorldPos(localPos, chunkPos);

			auto newChunkPos = World::getChunkPos(worldPos);
			auto newLocalPos = World::getLocalPos(worldPos);

			EXPECT_EQ(chunkPos.x, newChunkPos.x);
			EXPECT_EQ(chunkPos.y, newChunkPos.y);
			EXPECT_EQ(chunkPos.z, newChunkPos.z);

			EXPECT_EQ(localPos.x, newLocalPos.x);
			EXPECT_EQ(localPos.y, newLocalPos.y);
			EXPECT_EQ(localPos.z, newLocalPos.z);
		}

	}
}
