#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock() noexcept;
	DirtBlock(const glm::vec3& pos) noexcept;

	std::array<Vertex, 4 * 6> getVertices(TextureMap& textureMap) override;
};
