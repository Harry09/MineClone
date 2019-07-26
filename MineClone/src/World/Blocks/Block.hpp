#pragma once

#include <array>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "TextureAtlas.hpp"
#include "Blocks.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/VertexBuffer.hpp"

class Chunk;

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

glm::ivec3 getBlockSideDirection(BlockSide side);

namespace detail
{
	template<BlockSide Side>
	inline auto getMesh(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{

	}

	template<>
	inline auto getMesh<BlockSide::North>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::East>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::South>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockSide::West>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Top>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Bottom>(const glm::vec3& pos, Textures texture, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(texture, TextureAtlas::RightTop)    }
		};
	}
}

class Block
{
public:
	static constexpr int BlockSideSize = static_cast<int>(BlockSide::Size);

protected:
	Chunk& _chunk;

	glm::ivec3 _pos = { 0.f, 0.f, 0.f };

	Blocks _blockType;

	Textures _faceTexture[BlockSideSize];

public:
	Block(Chunk& chunk, const glm::ivec3& pos, Blocks blockType) noexcept;

	Block(const Block& other) noexcept;
	Block& operator=(const Block& other) noexcept;

	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;

	~Block() = default;

	const auto& getPosition() const { return _pos; }
	glm::ivec3 getWorldPosition() const;

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
	constexpr void setTexture(Textures textureId)
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

			std::array<Vertex, 6> mesh = detail::getMesh<Side>(_pos, _faceTexture[sideValue], textureAtlas);

			vertices.reserve(vertices.size() + 6);

			vertices.insert(vertices.end(), mesh.begin(), mesh.end());
		}
	}
};
