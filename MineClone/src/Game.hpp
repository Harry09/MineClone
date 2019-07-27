#pragma once

#include <memory>

#include "Renderer.hpp"

#include "World/World.hpp"
#include "World/Player.hpp"

class Texture;

class Game
{

private:
	static Game* _inst;

	Renderer _renderer;

	Player _player;
	World _world;

	glm::vec2 _lastCursorPos;

public:
	Game();
	~Game();

	bool init();
	void run();

	Renderer& getRenderer() { return _renderer; }

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

	void drawChunks();
};
