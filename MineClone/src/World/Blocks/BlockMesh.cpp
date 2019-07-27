#include "BlockMesh.hpp"

glm::ivec3 getBlockSideDirection(BlockSide side)
{
	switch (side)
	{
	case BlockSide::North:
		return { 0, 0, -1 };
	case BlockSide::East:
		return { 1, 0, 0 };
	case BlockSide::South:
		return { 0, 0, 1 };
	case BlockSide::West:
		return { -1, 0, 0 };
	case BlockSide::Top:
		return { 0, 1, 0 };
	case BlockSide::Bottom:
		return { 0, -1, 0 };
	}

	return { 0, 0, 0 };
}
