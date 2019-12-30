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
	static constexpr int BlockFaceCount = static_cast<int>(BlockFace::Size);

protected:
	ChunkSegment& _chunk;

	coords::LocalPos _localPos = { 0.f, 0.f, 0.f };

	Blocks _blockType;

	TextureId _faceTexture[BlockFaceCount] = { TextureId::None };

public:
	Block(ChunkSegment& chunk, const coords::LocalPos& localPos, Blocks blockType) noexcept;

	Block(const Block& other) noexcept;
	Block& operator=(const Block& other) noexcept;

	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;

	~Block() = default;

	const coords::LocalPos& getLocalPos() const { return _localPos; }
	coords::WorldPos getWorldPos() const;

	Block* getNeighbor(BlockFace face) const;

	bool hasNeighbor(BlockFace face) const { return getNeighbor(face) != nullptr; }

	template<BlockFace... Faces>
	const auto getVertices(TextureAtlas& textureAtlas) const
	{
		std::vector<Vertex> vertices;

		int offset = 0;

		((getVerticesImp<Faces>(vertices, offset, textureAtlas), offset++), ...);

		return vertices;
	}

protected:
	template<BlockFace... Faces>
	constexpr void setTexture(TextureId textureId)
	{
		((_faceTexture[static_cast<int>(Faces)] = textureId), ...);
	}

private:
	template<BlockFace Face>
	const void getVerticesImp(std::vector<Vertex>& vertices, int offset, TextureAtlas& textureAtlas) const
	{
		if (!hasNeighbor(Face))
		{
			unsigned faceValue = static_cast<unsigned>(Face);

			std::array<Vertex, 6> mesh = getSingleBlockMesh<Face>(_localPos, _faceTexture[faceValue], textureAtlas);

			vertices.reserve(vertices.size() + 6);

			vertices.insert(vertices.end(), mesh.begin(), mesh.end());
		}
	}
};
