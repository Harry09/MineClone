﻿#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock() noexcept;
	GrassBlock(const glm::vec3& pos) noexcept;

	std::array<Vertex, 4 * 6> getVertices(TextureMap& textureMap) override;

};