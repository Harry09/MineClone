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
	inline auto getMesh(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{

	}

	template<>
	inline auto getMesh<BlockSide::North>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::East>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::South>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockSide::West>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },

			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Top>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockSide::Bottom>(const glm::vec3& pos, Textures texture, TextureMap& textureMap)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureMap.getTextureCoords(texture, TextureMap::RightTop)    }
		};
	}
}

class Block
{
public:
	static constexpr int BlockSideSize = static_cast<int>(BlockSide::Size);

protected:
	glm::ivec3 _pos = { 0.f, 0.f, 0.f };

	uint64_t _flatPos = 0;

	Blocks _blockType;

	Block* _neighbor[BlockSideSize] = { nullptr };

	Textures _faceTexture[BlockSideSize];

public:
	Block(const glm::ivec3& pos, Blocks blockType) noexcept;

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
		((_faceTexture[static_cast<int>(Sides)] = textureId), ...);
	}

private:
	template<BlockSide Side>
	const void getVerticesImp(std::array<Vertex, 2 * 3 * 6>& vertices, int offset, TextureMap& textureMap) const
	{
		if (!hasNeighbor(Side))
		{
			unsigned sideValue = static_cast<unsigned>(Side);

			auto mesh = detail::getMesh<Side>(_pos, _faceTexture[sideValue], textureMap);

			std::copy(mesh.begin(), mesh.end(), vertices.begin() + (offset * 6));
		}
	}
};
