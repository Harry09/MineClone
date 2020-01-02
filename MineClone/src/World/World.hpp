#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"

#include "TextureAtlas.hpp"
#include "Chunk/ChunkManager.hpp"
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
		auto chunkSegmentPos = coords::getChunkSegmentPos(worldPos);

		auto chunk = getChunkSegment(chunkSegmentPos);

		if (chunk == nullptr)
			return;

		chunk->placeBlock<T>(coords::getLocalPos(worldPos));
		chunk->generateMesh(_textureAtlas);

		tryUpdateNearbyChunks(worldPos, chunkSegmentPos);
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
	void tryUpdateNearbyChunks(const coords::WorldPos& worldPos, const coords::ChunkSegmentPos& chunkSegmentPos);
	std::vector<glm::ivec3> getNeighborIfOnBound(const coords::WorldPos& worldPos);
};
