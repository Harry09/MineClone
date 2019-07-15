#pragma once
#include <cstdint>
#include <string>

#include <glm/vec2.hpp>

class Texture
{
private:
	uint32_t _texture = 0;

	glm::uvec2 _size{ 0.f };

public:
	Texture() noexcept = default;
	Texture(const std::string& filePath) noexcept;
	~Texture() noexcept;
	
	Texture(Texture& other) noexcept;
	Texture& operator=(Texture& othe) noexcept;

	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void loadFromFile(const std::string& filePath);

	const glm::uvec2& getSize() const { return _size; }

	bool isValid() const { return _texture != 0; }

	uint32_t getNativeHandle() const { return _texture; }
};