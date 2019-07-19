#pragma once

#include <array>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "TextureMap.hpp"
#include "Blocks.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/VertexBuffer.hpp"

enum class BlockSide : unsigned
{
	North = 0,
	East,
	South,
	West,
	Top,
	Bottom,
	Size
};

namespace detail
{
	template<BlockSide Side>
	inline auto getMesh(const glm::vec3& pos)
	{

	}

	template<>
	inline auto getMesh<BlockSide::North>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos }
		};
	}

	template<>
	inline auto getMesh<BlockSide::East>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos }
		};
	}

	template<>
	inline auto getMesh<BlockSide::South>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos }
		};
	}

	template<>
	inline auto getMesh<BlockSide::West>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos },

			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Top>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Bottom>(const glm::vec3& pos)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos }
		};
	}
}

class Block
{
public:
	static constexpr int BlockSideSize = static_cast<int>(BlockSide::Size);

protected:
	glm::vec3 _pos = { 0.f, 0.f, 0.f };

	uint64_t _flatPos = 0;

	Blocks _blockType;

	Block* _neighbor[BlockSideSize] = { nullptr };

	Textures _sideTexture[BlockSideSize];

public:
	Block(const glm::vec3& pos, Blocks blockType) noexcept;

	Block(const Block& other) noexcept;
	Block& operator=(const Block& other) noexcept;

	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;

	~Block() = default;

	const auto& getPosition() const { return _pos; }
	const auto getFlatPosition() const { return _flatPos; }

	void setNeighbor(Block* block, BlockSide side) { _neighbor[static_cast<int>(side)] = block; }
	Block* getNeighbor(BlockSide side) const { return _neighbor[static_cast<int>(side)]; }
	bool hasNeighbor(BlockSide side) const { return _neighbor[static_cast<int>(side)] != nullptr; }

	template<BlockSide... Sides>
	const auto getVertices(TextureMap& textureMap) const
	{
		std::array<Vertex, 2 * 3 * 6> vertices;

		int offset = 0;

		((getVerticesImp<Sides>(vertices, offset, textureMap), offset++), ...);

		return vertices;
	}

protected:
	template<BlockSide... Sides>
	constexpr void setTexture(Textures textureId)
	{
		((_sideTexture[static_cast<int>(Sides)] = textureId), ...);
	}

private:
	template<BlockSide Side>
	const void getVerticesImp(std::array<Vertex, 2 * 3 * 6>& vertices, int offset, TextureMap& textureMap) const
	{
		if (!hasNeighbor(Side))
		{
			auto mesh = detail::getMesh<Side>(_pos);

			unsigned sideValue = static_cast<unsigned>(Side);

			mesh[0].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftBottom);
			mesh[1].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
			mesh[2].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);

			mesh[3].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
			mesh[4].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightTop);
			mesh[5].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);

			std::copy(mesh.begin(), mesh.end(), vertices.begin() + (offset * 6));
		}
	}
};
