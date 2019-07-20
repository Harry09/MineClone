#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"
#include "TextureMap.hpp"

#include "Chunk.hpp"

class World
{
private:
	Texture _texture;
	std::unique_ptr<TextureMap> _textureMap;

	std::vector<std::unique_ptr<Chunk>> _chunks;

public:
	World();

	void init();

	Chunk* getChunk(const glm::ivec3& pos) const;

	void draw(ShaderProgram& shaderProgram);
};
