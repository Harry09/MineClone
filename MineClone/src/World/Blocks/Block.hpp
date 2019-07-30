#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "BlockMesh.hpp"
#include "Maths/Coords.hpp"

class ChunkSegment;

class Block
{
public:
	static constexpr int BlockSideSize = static_cast<int>(BlockSide::Size);

protected:
	ChunkSegment& _chunk;

	coords::LocalPos _localPos = { 0.f, 0.f, 0.f };

	Blocks _blockType;

	TextureId _faceTexture[BlockSideSize] = { TextureId::None };

public:
	Block(ChunkSegment& chunk, const coords::LocalPos& localPos, Blocks blockType) noexcept;

	Block(const Block& other) noexcept;
	Block& operator=(const Block& other) noexcept;

	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;

	~Block() = default;

	const coords::LocalPos& getLocalPos() const { return _localPos; }
	coords::WorldPos getWorldPos() const;

	Block* getNeighbor(BlockSide side) const;

	bool hasNeighbor(BlockSide side) const { return getNeighbor(side) != nullptr; }

	template<BlockSide... Sides>
	const auto getVertices(TextureAtlas& textureAtlas) const
	{
		std::vector<Vertex> vertices;

		int offset = 0;

		((getVerticesImp<Sides>(vertices, offset, textureAtlas), offset++), ...);

		return vertices;
	}

protected:
	template<BlockSide... Sides>
	constexpr void setTexture(TextureId textureId)
	{
		((_faceTexture[static_cast<int>(Sides)] = textureId), ...);
	}

private:
	template<BlockSide Side>
	const void getVerticesImp(std::vector<Vertex>& vertices, int offset, TextureAtlas& textureAtlas) const
	{
		if (!hasNeighbor(Side))
		{
			unsigned sideValue = static_cast<unsigned>(Side);

			std::array<Vertex, 6> mesh = getSingleBlockMesh<Side>(_localPos, _faceTexture[sideValue], textureAtlas);

			vertices.reserve(vertices.size() + 6);

			vertices.insert(vertices.end(), mesh.begin(), mesh.end());
		}
	}
};
