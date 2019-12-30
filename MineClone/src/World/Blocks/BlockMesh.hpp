#pragma once

#include <array>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "TextureAtlas.hpp"
#include "Graphics/Vertex.hpp"


enum class BlockFace : unsigned
{
	North = 0,
	East,
	South,
	West,
	Top,
	Bottom,
	Size
};

glm::ivec3 getBlockFaceVec(BlockFace Face);

namespace detail
{
	template<BlockFace Face>
	inline auto getMesh(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{

	}

	template<>
	inline auto getMesh<BlockFace::North>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockFace::East>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockFace::South>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockFace::West>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    }
		};
	}

	template<>
	inline auto getMesh<BlockFace::Top>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     }
		};
	}

	template<>
	inline auto getMesh<BlockFace::Bottom>(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftBottom)  },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightBottom) },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::LeftTop)     },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + pos, glm::vec3 { 1.f }, textureAtlas.getTextureCoords(textureId, TextureAtlas::RightTop)    }
		};
	}
}

template<BlockFace Face>
inline std::array<Vertex, 6> getSingleBlockMesh(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
{
	return detail::getMesh<Face>(pos, textureId, textureAtlas);
}

template<BlockFace Face>
inline void getBlockMeshImp(std::vector<Vertex>& data, const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
{
	auto mesh = detail::getMesh<Face>(pos, textureId, textureAtlas);

	data.insert(data.end(), mesh.begin(), mesh.end());
}

template<BlockFace... Faces>
inline std::vector<Vertex> getBlockMesh(const glm::vec3& pos, TextureId textureId, TextureAtlas& textureAtlas)
{
	std::vector<Vertex> result;

	constexpr auto argumentCount = sizeof...(Faces);

	result.reserve(argumentCount * 6);

	(getBlockMeshImp<Faces>(result, pos, textureId, textureAtlas), ...);

	return result;
}
