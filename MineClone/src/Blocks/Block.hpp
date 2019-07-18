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

	~Block();

	const auto& getPosition() const { return _pos; }
	const auto getFlatPosition() const { return _flatPos; }

	void setNeighbor(Block* block, BlockSide side) { _neighbor[static_cast<int>(side)] = block; }
	Block* getNeighbor(BlockSide side) { return _neighbor[static_cast<int>(side)]; }
	bool hasNeighbor(BlockSide side) { return _neighbor[static_cast<int>(side)] != nullptr; }

	const std::array<Vertex, 2 * 3 * 6> getVertices(TextureMap & textureMap) const;

protected:
	constexpr void setTexture(BlockSide side, Textures textureId)
	{
		_sideTexture[static_cast<int>(side)] = textureId;
	}

	template<BlockSide Side>
	const void texture(std::array<Vertex, 2 * 3 * 6>& vertices, TextureMap& textureMap) const
	{
		unsigned sideValue = static_cast<unsigned>(Side);

		vertices[sideValue * 6 + 0].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftBottom);
		vertices[sideValue * 6 + 1].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
		vertices[sideValue * 6 + 2].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);

		vertices[sideValue * 6 + 3].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightBottom);
		vertices[sideValue * 6 + 4].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::RightTop);
		vertices[sideValue * 6 + 5].texCoord = textureMap.getTextureCoords(_sideTexture[sideValue], TextureMap::LeftTop);
	}

	constexpr auto getMesh() const
	{
		return std::array{
			// North
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },

			// East
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },

			// South
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + _pos },

			// West
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },
							    
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },

			// Top
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + _pos },

			// Bottom
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos },

			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos }
		};
	}
};
