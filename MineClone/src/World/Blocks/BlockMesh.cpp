#include "BlockMesh.hpp"

glm::ivec3 getBlockFaceVec(BlockFace face)
{
	switch (face)
	{
	case BlockFace::North:
		return { 0, 0, -1 };
	case BlockFace::East:
		return { 1, 0, 0 };
	case BlockFace::South:
		return { 0, 0, 1 };
	case BlockFace::West:
		return { -1, 0, 0 };
	case BlockFace::Top:
		return { 0, 1, 0 };
	case BlockFace::Bottom:
		return { 0, -1, 0 };
	}

	return { 0, 0, 0 };
}
