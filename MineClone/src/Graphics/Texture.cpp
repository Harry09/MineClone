#include "Texture.hpp"

#include "stb_image.h"
#include <glad/glad.h>


Texture::Texture(const std::string& filePath) noexcept
{
	loadFromFile(filePath);
}

Texture::~Texture() noexcept
{
	if (_texture != 0)
	{
		glDeleteTextures(1, &_texture);
	}

	_texture = 0;
}

Texture::Texture(Texture& other) noexcept
	: _texture(other._texture)
{
}

Texture& Texture::operator=(Texture& other) noexcept
{
	_texture = other._texture;

	return *this;
}

Texture::Texture(Texture&& other) noexcept
	: _texture(std::move(other._texture))
{
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	_texture = std::move(other._texture);

	return *this;
}

void Texture::loadFromFile(const std::string& filePath)
{
	int width, height, channels;

	auto data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

	if (data == nullptr)
	{
		return;
	}

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}
