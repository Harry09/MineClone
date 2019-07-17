#pragma once

#include <memory>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/ShaderProgram.hpp"

#include "Chunk.hpp"
#include "Player.hpp"

class Texture;
struct GLFWwindow;

class Game
{
public:
	static constexpr unsigned ScreenWidth = 1024;
	static constexpr unsigned ScreenHeight = 768;

private:
	static Game* _inst;

	GLFWwindow* _window = nullptr;

	Camera _camera;
	Player _player;

	std::unique_ptr<ShaderProgram> _shaderProgram;

	Chunk _chunk;

	glm::vec2 _lastCursorPos;

public:
	Game();
	~Game();

	bool init();
	void run();

	Camera& getCamera() { return _camera; }
	const Camera& getCamera() const { return _camera; }

	GLFWwindow* getWindow() { return _window; }
	const GLFWwindow* getWindow() const { return _window; }

	glm::vec2 getCursorOffset(const glm::vec2& pos) 
	{ 
		glm::vec2 result;
		result.x = pos.x - _lastCursorPos.x;
		result.y = _lastCursorPos.y - pos.y;
		_lastCursorPos = pos; 

		return result;
	}

	static Game* get()
	{
		return _inst;
	}

private:
	void update();
	void render();
};
