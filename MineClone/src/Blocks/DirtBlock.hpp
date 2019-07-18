#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock() noexcept;
	DirtBlock(const glm::vec3& pos) noexcept;

	const std::array<Vertex, 2 * 3 * 6> getVertices(TextureMap& textureMap) const override;
};
