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
protected:
	enum class TexturingSide : unsigned
	{
		North = 0,
		East,
		South,
		West,
		Top,
		Bottom
	};

protected:
	glm::vec3 _pos = { 0.f, 0.f, 0.f };

	Blocks _blockType;

	std::unique_ptr<VertexBuffer> _mesh;

public:
	Block(Blocks blockType) noexcept;
	Block(const glm::vec3& pos, Blocks blockType) noexcept;

	Block(const Block& other) noexcept;
	Block& operator=(const Block& other) noexcept;

	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;

	void create(TextureMap& map);

	void draw(ShaderProgram& shaderProgram);

	void setPosition(const glm::vec3& pos) { _pos = pos; }
	const auto& getPosition() { return _pos; }

	virtual std::array<Vertex, 4 * 6> getVertices(TextureMap & textureMap) = 0;

	static constexpr std::array<uint32_t, 6 * 6> getIndices()
	{
		return std::array<uint32_t, 6 * 6>{
			0, 1, 3,
			1, 2, 3,

			4, 5, 7,
			5, 6, 7,

			8, 9, 11,
			9, 10, 11,

			12, 13, 15,
			13, 14, 15,

			16, 17, 19,
			17, 18, 19,

			20, 21, 23,
			21, 22, 23
		};
	}

protected:
	template<TexturingSide Side>
	void texture(std::array<Vertex, 4 * 6>& vertices, Textures textureId, TextureMap& textureMap)
	{
		unsigned offset = static_cast<unsigned>(Side);

		vertices[offset * 4 + 0].texCoord = textureMap.getTextureCoords(textureId, TextureMap::LeftBottom);
		vertices[offset * 4 + 1].texCoord = textureMap.getTextureCoords(textureId, TextureMap::RightBottom);
		vertices[offset * 4 + 2].texCoord = textureMap.getTextureCoords(textureId, TextureMap::RightTop);
		vertices[offset * 4 + 3].texCoord = textureMap.getTextureCoords(textureId, TextureMap::LeftTop);
	}

	constexpr auto getMesh()
	{
		return std::array{
			// North
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },   // 12
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },   // 13
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },   // 14
			Vertex{ glm::vec3 { -0.5f,  0.5f, -0.5f } + _pos },   // 15

			// East
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },   // 4
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },   // 5
			Vertex{ glm::vec3 {  0.5f,  0.5f,  0.5f } + _pos },   // 6
			Vertex{ glm::vec3 {  0.5f,  0.5f, -0.5f } + _pos },   // 7

			// South
			Vertex{ glm::vec3 { -0.5f, -0.5f, 0.5f } + _pos },    // 0
			Vertex{ glm::vec3 {  0.5f, -0.5f, 0.5f } + _pos },    // 1
			Vertex{ glm::vec3 {  0.5f,  0.5f, 0.5f } + _pos },    // 2
			Vertex{ glm::vec3 { -0.5f,  0.5f, 0.5f } + _pos },    // 3

			// West
			Vertex{ glm::vec3 {  -0.5f, -0.5f, -0.5f } + _pos },  // 8
			Vertex{ glm::vec3 {  -0.5f, -0.5f,  0.5f } + _pos },  // 9
			Vertex{ glm::vec3 {  -0.5f,  0.5f,  0.5f } + _pos },  // 10
			Vertex{ glm::vec3 {  -0.5f,  0.5f, -0.5f } + _pos },  // 11

			// Top
			Vertex{ glm::vec3 { -0.5f, 0.5f, -0.5f } + _pos },    // 16
			Vertex{ glm::vec3 {  0.5f, 0.5f, -0.5f } + _pos },    // 17
			Vertex{ glm::vec3 {  0.5f, 0.5f,  0.5f } + _pos },    // 18
			Vertex{ glm::vec3 { -0.5f, 0.5f,  0.5f } + _pos },    // 19

			// Bottom
			Vertex{ glm::vec3 { -0.5f, -0.5f, -0.5f } + _pos },   // 20
			Vertex{ glm::vec3 {  0.5f, -0.5f, -0.5f } + _pos },   // 21
			Vertex{ glm::vec3 {  0.5f, -0.5f,  0.5f } + _pos },   // 22
			Vertex{ glm::vec3 { -0.5f, -0.5f,  0.5f } + _pos }    // 23
		};
	}
};