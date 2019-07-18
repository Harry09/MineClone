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

	virtual std::array<Vertex, 2 * 3 * 6> getVertices(TextureMap & textureMap) = 0;

protected:
	template<TexturingSide Side>
	void texture(std::array<Vertex, 2 * 3 * 6>& vertices, Textures textureId, TextureMap& textureMap)
	{
		unsigned offset = static_cast<unsigned>(Side);

		vertices[offset * 6 + 0].texCoord = textureMap.getTextureCoords(textureId, TextureMap::LeftBottom);
		vertices[offset * 6 + 1].texCoord = textureMap.getTextureCoords(textureId, TextureMap::RightBottom);
		vertices[offset * 6 + 2].texCoord = textureMap.getTextureCoords(textureId, TextureMap::LeftTop);

		vertices[offset * 6 + 3].texCoord = textureMap.getTextureCoords(textureId, TextureMap::RightBottom);
		vertices[offset * 6 + 4].texCoord = textureMap.getTextureCoords(textureId, TextureMap::RightTop);
		vertices[offset * 6 + 5].texCoord = textureMap.getTextureCoords(textureId, TextureMap::LeftTop);
	}

	constexpr auto getMesh()
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
			Vertex{ glm::vec3 {  -0.5f, -0.5f, -0.5f } + _pos },
			Vertex{ glm::vec3 {  -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  -0.5f,  0.5f, -0.5f } + _pos },

			Vertex{ glm::vec3 {  -0.5f, -0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  -0.5f,  0.5f,  0.5f } + _pos },
			Vertex{ glm::vec3 {  -0.5f,  0.5f, -0.5f } + _pos },

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
