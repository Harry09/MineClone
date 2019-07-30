#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"
#include "TextureAtlas.hpp"

#include "ChunkManager.hpp"

class Camera;

class World
{
private:
	Camera& _camera;

	Texture _texture;
	TextureAtlas _textureAtlas;

	ChunkManager _chunkManager;

	glm::vec3 _boundingSpherePos{ 0.f };

public:
	World(Camera& camera);

	void init();

	Chunk* getChunk(const glm::ivec3& chunkPos) const;

	template<typename T>
	void placeBlock(const glm::ivec3& worldPos)
	{
		auto chunkPos = getChunkPos(worldPos);

		auto chunk = getChunk(chunkPos);

		if (chunk == nullptr)
			return;

		chunk->placeBlock<T>(getLocalPos(worldPos));
		chunk->generateMesh(_textureAtlas);

		tryUpdateNearChunks(worldPos, chunkPos);
	}

	void removeBlock(const glm::ivec3& worldPos);
	Block* getBlock(const glm::ivec3& worldPos) const;

	TextureAtlas& getTextureAtlas() { return _textureAtlas; }
	const TextureAtlas& getTextureAtlas() const { return _textureAtlas; }

	bool isPointInBoundingSphere(const glm::vec3& pos);

	void update();
	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);

public:
	static glm::ivec3 getChunkPos(const glm::ivec3& worldPos);
	static glm::ivec3 getLocalPos(const glm::ivec3& worldPos);
	static glm::ivec3 getWorldPos(const glm::ivec3& localPos, const glm::ivec3& chunkPos);

	void tryUpdateNearChunks(const glm::ivec3& worldPos, const glm::ivec3& chunkPos);
	std::vector<glm::ivec3> getNeighborIfOnBound(const glm::ivec3& worldPos);
};
