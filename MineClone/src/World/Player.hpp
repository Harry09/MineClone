#pragma once

#include "Graphics/VertexBuffer.hpp"

struct GLFWwindow;

class Camera;
class World;

class Player
{
private:
	enum BlockAction
	{
		None,
		Placing,
		Removing
	};

public:
	static constexpr float PlayerSpeed = 0.1f;

private:
	World& _world;
	Camera& _camera;

	bool _drawHighlighter = false;
	VertexBuffer _highlighter{ 24, PrimitiveType::Lines };

	BlockAction _blockAction = None;

public:
	Player(World& world, Camera& camera);

	void init();

	void update(GLFWwindow* window);

	void drawGrid(ShaderProgram& shaderProgram);
};