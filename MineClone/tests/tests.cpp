#include <World/World.hpp>

#include <gtest/gtest.h>

#define EXPECT_EQ_IVEC3(p1, p2) \
	EXPECT_EQ(p1.x, p2.x); \
	EXPECT_EQ(p1.y, p2.y); \
	EXPECT_EQ(p1.z, p2.z);

void testValues(const glm::ivec3& localPos, const glm::ivec3& chunkPos, const glm::ivec3& worldPos)
{
	// g stands for generated
	auto gWorldPos = World::getWorldPos(localPos, chunkPos);

	EXPECT_EQ_IVEC3(worldPos, gWorldPos);

	auto gChunkPos = World::getChunkPos(gWorldPos);

	EXPECT_EQ_IVEC3(chunkPos, gChunkPos);

	auto gLocalPos = World::getLocalPos(gWorldPos);

	EXPECT_EQ_IVEC3(localPos, gLocalPos);
}

TEST(World, Minus2)
{
	auto worldPos = glm::ivec3{ -2, -2, -2 };
	auto localPos = glm::ivec3{ 14, 14, 14 };
	auto chunkPos = glm::ivec3{ -1, -1, -1 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus30)
{
	auto worldPos = glm::ivec3{ -30, -30, -30 };
	auto localPos = glm::ivec3{ 2, 2, 2 };
	auto chunkPos = glm::ivec3{ -2, -2, -2 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus31)
{
	auto worldPos = glm::ivec3{ -31, -31, -31 };
	auto localPos = glm::ivec3{ 1, 1, 1 };
	auto chunkPos = glm::ivec3{ -2, -2, -2 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus32)
{
	auto worldPos = glm::ivec3{ -32, -32, -32 };
	auto localPos = glm::ivec3{ 0, 0, 0 };
	auto chunkPos = glm::ivec3{ -2, -2, -2 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus33)
{
	auto worldPos = glm::ivec3{ -33, -33, -33 };
	auto localPos = glm::ivec3{ 15, 15, 15 };
	auto chunkPos = glm::ivec3{ -3, -3, -3 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus15)
{
	auto worldPos = glm::ivec3{ -15, -15, -15 };
	auto localPos = glm::ivec3{ 1, 1, 1 };
	auto chunkPos = glm::ivec3{ -1, -1, -1 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus16)
{
	auto worldPos = glm::ivec3{ -16, -16, -16 };
	auto localPos = glm::ivec3{ 0, 0, 0 };
	auto chunkPos = glm::ivec3{ -1, -1, -1 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus17)
{
	auto worldPos = glm::ivec3{ -17, -17, -17 };
	auto localPos = glm::ivec3{ 15, 15, 15 };
	auto chunkPos = glm::ivec3{ -2, -2, -2 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus128)
{
	auto worldPos = glm::ivec3{ -128, -128, -128 };
	auto localPos = glm::ivec3{ 0, 0, 0 };
	auto chunkPos = glm::ivec3{ -8, -8, -8 };

	testValues(localPos, chunkPos, worldPos);
}

TEST(World, Minus64)
{
	auto worldPos = glm::ivec3{ -64, -64, -64 };
	auto localPos = glm::ivec3{ 0, 0, 0 };
	auto chunkPos = glm::ivec3{ -4, -4, -4 };

	testValues(localPos, chunkPos, worldPos);
}


TEST(World, TestPosEquality)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			glm::ivec3 chunkPos = { i, i, i };
			glm::ivec3 localPos = { j, j, j };
			glm::ivec3 worldPos = World::getWorldPos(localPos, chunkPos);

			auto newChunkPos = World::getChunkPos(worldPos);
			auto newLocalPos = World::getLocalPos(worldPos);

			EXPECT_EQ_IVEC3(chunkPos, newChunkPos);
			EXPECT_EQ_IVEC3(localPos, newLocalPos);
		}
	}
}
