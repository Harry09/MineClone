#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock() noexcept;
	GrassBlock(const glm::vec3& pos) noexcept;

	const std::array<Vertex, 2 * 3 * 6> getVertices(TextureMap& textureMap) const override;

};