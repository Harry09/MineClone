#pragma once

#include <memory>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/RenderState.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/ShaderProgram.hpp"

#include "Block.hpp"

class Texture;
struct GLFWwindow;

class Game
{
public:
	static constexpr unsigned ScreenWidth = 1024;
	static constexpr unsigned ScreenHeight = 768;

private:
	GLFWwindow* _window = nullptr;

	Camera _camera;

	std::unique_ptr<ShaderProgram> _shaderProgram;

	std::unique_ptr<Block> _block;

	glm::vec2 _lastCursorPos;

public:
	Game() = default;
	~Game();

	bool init();
	void run();

	Camera& getCamera() { return _camera; }
	const Camera& getCamera() const { return _camera; }

	glm::vec2 getCursorOffset(const glm::vec2& pos) 
	{ 
		glm::vec2 result;
		result.x = pos.x - _lastCursorPos.x;
		result.y = _lastCursorPos.y - pos.y;
		_lastCursorPos = pos; 

		return result;
	}

private:
	void update();
	void render();
};
