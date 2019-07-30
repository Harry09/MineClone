#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"

#include "TextureAtlas.hpp"
#include "ChunkManager.hpp"
#include "Maths/FrustumView.hpp"

class Camera;

class World
{
private:
	Camera& _camera;

	FrustumView _frustumView;

	Texture _texture;
	TextureAtlas _textureAtlas;

	ChunkManager _chunkManager;

	glm::vec3 _boundingSpherePos{ 0.f };

public:
	World(Camera& camera);

	void init();

	Chunk* getChunk(const coords::ChunkPos& chunkPos) const;
	ChunkSegment* getChunkSegment(const coords::ChunkSegmentPos& chunkSegmentPos) const;

	template<typename T>
	void placeBlock(const coords::WorldPos& worldPos)
	{
		auto chunkPos = getChunkSegmentPos(worldPos);

		auto chunk = getChunkSegment(chunkPos);

		if (chunk == nullptr)
			return;

		chunk->placeBlock<T>(getLocalPos(worldPos));
		chunk->generateMesh(_textureAtlas);

		tryUpdateNearChunks(worldPos, chunkPos);
	}

	void removeBlock(const coords::WorldPos& worldPos);
	Block* getBlock(const coords::WorldPos& worldPos) const;

	TextureAtlas& getTextureAtlas() { return _textureAtlas; }
	const TextureAtlas& getTextureAtlas() const { return _textureAtlas; }

	const FrustumView& getFrustumView() const { return _frustumView; }

	void update();
	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);

public:
	static coords::ChunkPos getChunkPos(const coords::WorldPos& worldPos);
	static coords::ChunkSegmentPos getChunkSegmentPos(const coords::WorldPos& worldPos);
	static coords::LocalPos getLocalPos(const coords::WorldPos& worldPos);
	static coords::WorldPos getWorldPos(const coords::LocalPos& localPos, const coords::ChunkSegmentPos& chunkSegmentPos);

	void tryUpdateNearChunks(const coords::WorldPos& worldPos, const coords::ChunkSegmentPos& chunkSegmentPos);
	std::vector<glm::ivec3> getNeighborIfOnBound(const coords::WorldPos& worldPos);
};
