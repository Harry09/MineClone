#pragma once

#include <memory>

#include "Renderer.hpp"

#include "World/World.hpp"
#include "World/Player.hpp"

class Texture;

class Game
{
public:
	constexpr static int MaxChunkDrawDistance = 8;

private:
	static Game* _inst;

	Renderer _renderer;

	Player _player;
	World _world;

	// todo: move to other class
	Texture _cursorTex;
	VertexBuffer _cursor{ 4, PrimitiveType::Lines };
	glm::mat4 _hudViewMatrix{ 1.f };

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
	void initCursor();

	void update();

	void drawChunks(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void drawHud(const glm::mat4& projectionMatrix);
	void drawGrid(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
};
