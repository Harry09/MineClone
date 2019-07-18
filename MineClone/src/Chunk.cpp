#include "Chunk.hpp"

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::init()
{
	_texture.loadFromFile("textures.jpg");

	_textureMap = std::make_unique<TextureMap>(_texture, 16);

	_data = std::make_unique<VertexBuffer>(6 * 6 * Size.x * Size.y * Size.z + 1, PrimitiveType::Triangles);
	_data->setTexture(_texture);
	
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				placeBlock(DirtBlock(glm::vec3{ x, y, z }));
			}
		}
	}

	_data->update();	
}

void Chunk::placeBlock(const Block& block)
{
	auto pos = glm::ivec3(block.getPosition());
	auto vertices = block.getVertices(*_textureMap);

	auto arrayPos = (pos.x + Size.x * (pos.y + Size.y * pos.z)) * 36;

	_data->setVertices(arrayPos, vertices.data(), vertices.size());
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	_data->draw(shaderProgram);
}
