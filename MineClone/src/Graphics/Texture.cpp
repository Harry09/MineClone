#include "Texture.hpp"

#include "stb_image.h"
#include <glad/glad.h>


Texture::Texture(const std::string& filePath, bool transparent) noexcept
{
	loadFromFile(filePath, transparent);
}

Texture::~Texture() noexcept
{
	if (_texture != 0)
	{
		glDeleteTextures(1, &_texture);
	}

	_texture = 0;
}

Texture::Texture(const Texture& other) noexcept
	: 
	_texture(other._texture),
	_size(other._size)
{
}

Texture& Texture::operator=(const Texture& other) noexcept
{
	_texture = other._texture;
	_size = other._size;

	return *this;
}

Texture::Texture(Texture&& other) noexcept
	: 
	_texture(std::move(other._texture)),
	_size(std::move(other._size))
{
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	_texture = std::move(other._texture);
	_size = std::move(other._size);

	return *this;
}

void Texture::loadFromFile(const std::string& filePath, bool transparent)
{
	int width, height, channels;

	int desiredChannels = STBI_rgb;
	int format = GL_RGB;

	if (transparent)
	{
		desiredChannels = STBI_rgb_alpha;
		format = GL_RGBA;
	}

	auto data = stbi_load(filePath.c_str(), &width, &height, &channels, desiredChannels);

	if (data == nullptr)
	{
		return;
	}

	_size = { width, height };

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}
