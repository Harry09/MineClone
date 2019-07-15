#pragma once
#include <cstdint>
#include <string>

class Texture
{
private:
	uint32_t _texture = 0;

public:
	Texture() noexcept = default;
	Texture(const std::string& filePath) noexcept;
	~Texture() noexcept;
	
	Texture(Texture& other) noexcept;
	Texture& operator=(Texture& othe) noexcept;

	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;


	void loadFromFile(const std::string& filePath);

	bool isValid() const { return _texture != 0; }

	uint32_t getNativeHandle() const { return _texture; }
};