#pragma once

#include <array>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "TextureMap.hpp"
#include "Blocks.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/VertexBuffer.hpp"

class Block
{
public:
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
	constexpr void setTexture(BlockSide side, Textures textureId)
	{
		_sideTexture[static_cast<int>(side)] = textureId;
	}

private:
	template<BlockSide Side>
	const void getVerticesImp(std::array<Vertex, 2 * 3 * 6>& vertices, int offset, TextureMap& textureMap) const
	{
		if (!hasNeighbor(Side))
		{
			auto mesh = getMesh<Side>();

			texture<Side>(mesh, textureMap);

			std::copy(mesh.begin(), mesh.end(), vertices.begin() + (offset * 6));
		}
	}

	template<BlockSide Side>
	const void texture(std::array<Vertex, 6>& vertices, TextureMap& textureMap) const
	{
		unsigned sideValue = static_cast<unsigned>(Side);

		vertices[0].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftBottom);
		vertices[1].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
		vertices[2].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);

		vertices[3].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
		vertices[4].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightTop);
		vertices[5].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);
	}

	template<BlockSide Side>
	constexpr auto getMesh() const
	{

	}

	template<>
	constexpr auto getMesh<BlockSide::North>() const
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } +_pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } +_pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } +_pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } +_pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } +_pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } +_pos }
		};
	}

	template<>
	constexpr auto getMesh<BlockSide::East>() const
	{
		return std::array{
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos }
		};
	}

	template<>
	constexpr auto getMesh<BlockSide::South>() const
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + _pos }
		};
	}

	template<>
	constexpr auto getMesh<BlockSide::West>() const
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },
							    
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos }
		};
	}

	template<>
	constexpr auto getMesh<BlockSide::Top>() const
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + _pos }
		};
	}

	template<>
	constexpr auto getMesh<BlockSide::Bottom>() const
	{
		return std::array{
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos }
		};
	}
};
